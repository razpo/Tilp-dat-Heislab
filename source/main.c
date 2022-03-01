#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "door.h"
#include "controller.h"

enum states {
    REST, 
    EXECUTING, 
    ARRIVED, 
    EMERGENCY
};

int main(){
    elevio_init();
    elevator_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int g_nextFloor = -1;
    int g_currFloor = elevio_floorSensor();
    int g_lastFloor = -1;
    int g_doorOpen = 0;
    enum states state = REST;
    time_t g_startTime = time(NULL);
    MotorDirection g_dir = DIRN_DOWN;
    /*
    g_dir = DIRN_DOWN;
    elevio_motorDirection(g_dir);
    */
   while (1) {
        g_currFloor = elevio_floorSensor();
        if (elevio_stopButton()) {
            elevator_setEmergency(g_currFloor, &g_doorOpen, &g_startTime, 1);
            state = EMERGENCY;
        } 
        for (int floor = 0; floor < N_FLOORS; floor++) {
            for (int buttonType = 0; buttonType < N_BUTTONS; buttonType++) {
                if (elevio_callButton(floor, buttonType)) {
                    controller_addFloorOrder(floor, buttonType);
                    elevio_buttonLamp(floor, buttonType, 1);
                }
            }
        }
        //state machine:
        switch (state) {
            case REST:
                printf("State: rest \n");
                g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                if (g_nextFloor != -1) {
                    state = EXECUTING;
                }
                break;
            case EXECUTING: {
                printf("State: executing \n");
                int arrived = elevator_moveToFloor(g_nextFloor);
                if (arrived) {
                    state = ARRIVED;
                }
                if (g_currFloor != -1 && g_currFloor != g_lastFloor) {
                    g_lastFloor = g_currFloor;
                    elevio_floorIndicator(g_lastFloor);
                }
                g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                break;
            }
            case ARRIVED:
                printf("State: Arrived \n");
                 if (!g_doorOpen) {
                    controller_removeFloorOrder(g_currFloor);
                    g_dir = DIRN_STOP;
                    for (int b = 0; b < N_BUTTONS; b++) {
                        elevio_buttonLamp(g_currFloor, b, 0);
                    }
                    door_openDoor(g_currFloor, &g_doorOpen, &g_startTime);
                } else {
                    if (elevio_obstruction()) {
                        g_startTime = time(NULL);
                        printf("Obstruction \n");
                    }
                    if (time(NULL) - g_startTime > 3) {
                        door_closeDoor(g_currFloor, &g_doorOpen);
                        //nextFloor = -1;
                        g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                        if(g_nextFloor == -1){
                            state = REST;
                        } else {
                            state = EXECUTING;
                        }
                    }
                }
                break;
            case EMERGENCY:
                printf("State: Emergency \n");
                if(!elevio_stopButton()) {
                    elevator_setEmergency(g_currFloor, &g_doorOpen, &g_startTime, 0);
                    state = REST;
                }
                break;
            default:
                break;
        }
        if (elevio_obstruction()) {
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
   }
   return 0;
}
   
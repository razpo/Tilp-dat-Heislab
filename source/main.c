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


    printf("=== ELEVATOR INIT ===\n");
    elevator_init();
    
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
        printf("floor: %d \n",g_currFloor);  
        if (elevio_stopButton()) {
            elevator_setEmergency(g_currFloor, &g_doorOpen, &g_startTime, 1);
            g_dir = DIRN_STOP;
            state = EMERGENCY;
        } 
        //state machine:
        switch (state) {
            case REST:
                printf("State: rest \n");
                printf("Kjører test\n");
                sleep(2);
                int k = elevator_moveToFloor(4, DIRN_STOP);
                sleep(2);
                printf("Børr være i etasje 4");
                g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                if (g_nextFloor != -1) {
                    state = EXECUTING;
                }
                break;
            case EXECUTING: {
                printf("State: executing \n");
                printf("destination: %d \n", g_nextFloor);
                if (g_currFloor != -1) {
                    g_lastFloor = g_currFloor;
                    elevio_floorIndicator(g_lastFloor);
                    if(controller_getDestination(g_dir, g_lastFloor) != -1){
                        g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                    }
                }
                int arrived = elevator_moveToFloor(g_nextFloor, &g_dir);
                if (arrived) {
                    state = ARRIVED;
                }
                break;
            }
            case ARRIVED:
                printf("State: Arrived \n");
                if (!g_doorOpen) {
                    controller_removeFloorOrder(g_currFloor);
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
        
        for (int floor = 0; floor < N_FLOORS; floor++) {
            for (int buttonType = 0; buttonType < N_BUTTONS; buttonType++) {
                if (elevio_callButton(floor, buttonType)) {
                    controller_addFloorOrder(floor, buttonType);
                    elevio_buttonLamp(floor, buttonType, 1);
                }
            }
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
   
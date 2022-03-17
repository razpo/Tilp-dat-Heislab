#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "door.h"
#include "controller.h"
#include "buttons.h"

enum states {
    INIT,
    REST, 
    EXECUTING, 
    EMERGENCY
};

int main(){
    elevio_init();
    printf("=== ELEVATOR INITIALIZING ===\n");
    elevator_init();
    
    int g_nextFloor = -1;
    int g_currFloor = elevio_floorSensor();
    int g_lastFloor = g_currFloor;
    int g_doorOpen = 0;
    enum states g_state = REST;
    enum states g_prev_state = INIT;
    time_t g_startTime = time(NULL);
    MotorDirection g_dir = DIRN_STOP;
    MotorDirection g_lastDir = DIRN_STOP;

    while (1) {
        g_currFloor = elevio_floorSensor();
        if (elevio_stopButton()) {
            g_state = EMERGENCY;
        } 

        switch (g_state) {
            case EXECUTING: 
                if (g_state != g_prev_state) {
                    printf("State: Executing \n");
                    g_prev_state = g_state;
                }
                elevator_moveToFloor(g_nextFloor, g_lastFloor, &g_dir, g_lastDir);
                if (elevator_checkArrived(g_nextFloor, &g_dir)) {
                    g_state = REST;
                }
                if (g_currFloor != -1 && g_currFloor != g_lastFloor) {
                    g_lastFloor = g_currFloor;
                    elevio_floorIndicator(g_lastFloor);
                    if (controller_getDestination(g_dir, g_lastFloor) == g_lastFloor) {
                        g_nextFloor = g_lastFloor;
                    }
                }
                break;
            case REST:
                if (g_state != g_prev_state) {
                    printf("State: Rest \n");
                    g_prev_state = g_state;
                    if (g_currFloor != -1 && g_nextFloor != -1) {
                        controller_removeFloorOrder(g_currFloor);
                        buttons_clearLights(g_currFloor);
                        door_openDoor(g_currFloor, &g_doorOpen);
                    }
                }
                g_nextFloor = controller_getDestination(g_dir, g_lastFloor);
                
                if (g_doorOpen) {
                    if (elevio_obstruction()) {
                        door_openDoor(g_currFloor, &g_doorOpen);
                    } else {
                        door_closeDoor(&g_doorOpen);
                    }
                } else {
                    if (g_nextFloor == -1) {
                        g_state = REST;
                    } else {
                        g_state = EXECUTING;
                    }
                }   
                break;
            case EMERGENCY:
                if (g_state != g_prev_state) {
                    printf("State: Emergency \n");
                    g_prev_state = g_state;
                    if (g_dir != DIRN_STOP) {
                        g_lastDir = g_dir;
                        g_dir = DIRN_STOP;
                    }
                }
                elevator_setEmergency(g_currFloor, &g_doorOpen, 1);
                if (!elevio_stopButton()) {
                    elevator_setEmergency(g_currFloor, &g_doorOpen, 0);
                    g_state = REST;
                }
                break;
            default:
                break;
        }
        buttons_registerButtonPresses();
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
   }
   return 0;
}

   
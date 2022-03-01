/**
 * @file elevator.c
 * @brief Implementation of the elevator-functions
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <time.h>

#include "elevator.h"
#include "driver/elevio.h"
#include "door.h"
#include "controller.h"



int elevator_moveToFloor(int destinationFloor) {
    int currentFloor = elevio_floorSensor();
    if (currentFloor != -1) {
        if (currentFloor != destinationFloor) {
            if (currentFloor < destinationFloor) {
                elevio_motorDirection(DIRN_UP);
            }
            if (currentFloor > destinationFloor) {
                elevio_motorDirection(DIRN_DOWN);
            }
            return 0;
        }
    }
    if (currentFloor == destinationFloor) {
        elevio_motorDirection(DIRN_STOP);
        return 1;
    }    
};
//should this be in main? or elevatorcontroller?
int checkEmergency(int floor, int *doorOpen, time_t *startTime){
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        controller_emptyFloorOrders();
        if ((floor != -1) && (!doorOpen)) {
            door_openDoor(floor, doorOpen, startTime);
        }
        printf("Emergency state \n");
        return 1;
    }
    else {
        elevio_stopLamp(0);
        return 0;    
    }
}







/**
 * @file elevator.c
 * @brief Implementation of the elevator-functions
 * @copyright Copyright (c) 2022
 * 
 */
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevator.h"
#include "driver/elevio.h"
#include "door.h"


int moveToFloor(int destinationFloor){
    int currentFloor = elevio_floorSensor();
    if(currentFloor != -1){
        if(currentFloor != destinationFloor){
            if (currentFloor < destinationFloor){
                elevio_motorDirection(DIRN_UP);
            }
            if (currentFloor > destinationFloor){
                elevio_motorDirection(DIRN_DOWN);
            }
            return 0;
        }
    }
    if (currentFloor == destinationFloor){
        elevio_motorDirection(DIRN_STOP);
        return 1;
    }    
};
//should this be in main? or elevatorcontroller?
int checkEmergency(int floor, int* doorOpen, time_t* startTime){
    if(elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        // heiskøen må slettes, for loop
        if ((floor != -1) && (doorOpen == 0)) {
            openDoor(floor, doorOpen, startTime);
        }
        printf("Emergency state \n");
        return 1;
    }
    else {
        elevio_stopLamp(0);
        return 0;    
    }
}








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

/**
 * @file elevator.c
 * @brief Implementation of the elevator-functions
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

int move_to_floor(int floor){
    int current_floor = elevio_floorSensor();
    if(current_floor != floor){
        if (current_floor < floor){
            elevio_motorDirection(DIRN_UP);
        }
        if (current_floor > floor){
            elevio_motorDirection(DIRN_DOWN);
        }
        return 0;
    }
    if (current_floor == floor){
        elevio_motorDirection(DIRN_STOP);
        return 1;
    }    
};

int CheckEmergency(void){
    int stopButton = elevio_stopButton();
    int current_floor = elevio_floorSensor();
    int doorOpen;
    time_t startTime;
    if(stopButton== 1) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        // heiskøen må slettes, for loop
        if ((current_floor != -1)&&(doorOpen == 0)){
            openDoor(current_floor,&doorOpen,&startTime);
        }
        return 1;
    }
    else {
        elevio_stopLamp(0);
                    if(elevio_obstruction()){
                        startTime = time(NULL);
                        printf("Obstruction \n");
                    }
                    if(time(NULL) - startTime > 3){
                        closeDoor(current_floor, &doorOpen);
                    }
        return 0;    
    }
}








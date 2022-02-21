/**
 * @file heismodul.c
 * @brief Implementation of functions for controlling the physical model
 * @version 0.1
 * @date 2022-02-21
 * 
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

#include "heismodul.h"
#include "driver/elevio.h"

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
    if(stopButton== 1) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        // heiskøen må slettes
        return 1;
    }
    else {
        return 0;
    }
}








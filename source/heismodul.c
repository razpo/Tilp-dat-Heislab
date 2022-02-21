#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "heismodul.h"
#include "driver/elevio.h"

void move_to_floor(int floor){
    int current_floor = elevio_floorSensor();
    if(current_floor != floor){
        if (current_floor < floor){
            elevio_motorDirection(DIRN_UP);
        }
        if (current_floor > floor){
            elevio_motorDirection(DIRN_DOWN);
        }
    }
    if (current_floor == floor){
        elevio_motorDirection(DIRN_STOP);
    }
    
};








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
    if(current_floor != floor && current_floor != -1){
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








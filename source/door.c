#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "door.h"

int arrivedDestinationFloor(int floor){
    time_t startTime = time(NULL);

    elevio_motorDirection(DIRN_STOP);
    elevio_floorIndicator(floor);
    elevio_doorOpenLamp(1);
    while(time(NULL) - startTime < 3){
        if(elevio_obstruction()){
            startTime = time(NULL);
        }
    }
    elevio_doorOpenLamp(0);
    return floor;
}
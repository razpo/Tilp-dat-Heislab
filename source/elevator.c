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
        }
    }
    if (currentFloor == destinationFloor) {
        elevio_motorDirection(DIRN_STOP);
    }    
}
//should this be in main? or elevatorcontroller?
void elevator_setEmergency(int floor, int *doorOpen, time_t *startTime, int activate) {
    if (activate) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        controller_emptyFloorOrders();
        if ((floor != -1) && (!doorOpen)) {
            door_openDoor(floor, doorOpen, startTime);
        }
    } else {
        elevio_stopLamp(1);
    }
    
}

void elevator_init() {
    time_t startTime = time(NULL);
    MotorDirection dir = DIRN_DOWN;
    int currFloor = elevio_floorSensor();

    // startup: move down until elevator reaches any floor.
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevio_buttonLamp(f, b, 0);
        }
    }
    while (currFloor == -1) {
        currFloor = elevio_floorSensor();
        elevio_motorDirection(dir);
    }
    dir = DIRN_STOP;
    elevio_motorDirection(dir);
    printf("Elevator ready, now sleep for two seconds just for testing\n");
    sleep(2);
}






/**
 * @file elevator.c
 * @brief Implementation of the elevator-functions
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <time.h>

#include "driver/elevio.h"
#include "door.h"
#include "controller.h"
#include "elevator.h"


int elevator_moveToFloor(int destinationFloor, int lastFloor, MotorDirection *dir, MotorDirection lastDir) {
    int currentFloor = elevio_floorSensor();
    if (currentFloor == -1 && *dir == DIRN_STOP && lastFloor == destinationFloor) {
        printf("Uh oh...");
        if (lastDir == DIRN_UP) {
            *dir = DIRN_DOWN;
        } else {
            *dir = DIRN_UP;
        }
        elevio_motorDirection(*dir);
    } else {
        if (currentFloor != destinationFloor) {
            if (lastFloor < destinationFloor) {
                *dir = DIRN_UP;
            } else if (lastFloor > destinationFloor) {
                *dir = DIRN_DOWN;
            } 
            elevio_motorDirection(*dir);
        } else {
            *dir = DIRN_STOP;
            elevio_motorDirection(*dir);
            return 1;
        }
    }
    return 0; 
}
//should this be in main? or elevatorcontroller?
void elevator_setEmergency(int floor, int *doorOpen, int activate) {
    if (activate) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        controller_emptyFloorOrders();
        printf("Floor is %d \n", floor);
        if (floor != -1) {
            door_openDoor(floor, doorOpen);
        }
    } else {
        elevio_stopLamp(0);
    }
}

void elevator_init() {
    MotorDirection dir = DIRN_DOWN;
    int currFloor = elevio_floorSensor();
    // startup: move down until elevator reaches any floor.
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevio_buttonLamp(f, b, 0);
        }
    }
    elevio_doorOpenLamp(0);
    while (currFloor == -1) {
        currFloor = elevio_floorSensor();
        elevio_motorDirection(dir);
    }
    dir = DIRN_STOP;
    elevio_motorDirection(dir);
    printf("Elevator ready, now sleep for two seconds just for testing\n");
    sleep(2);
}






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

void elevator_setEmergency(int floor, int *doorOpen, int activate) {
    if (activate) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        controller_emptyFloorOrders();
        if (floor != -1) {
            door_openDoor(floor, doorOpen);
        }
    } else {
        elevio_stopLamp(0);
    }
}

void elevator_init() {
    int currFloor = elevio_floorSensor();
    controller_emptyFloorOrders();
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
    while (currFloor == -1) {
        currFloor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
    printf("Elevator ready\n");
}






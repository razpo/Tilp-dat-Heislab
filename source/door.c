/**
 * @file door.c
 * @brief Implementation of the door-functions
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "driver/elevio.h"
#include "door.h"

void door_openDoor(int floor, int *doorOpen, time_t *startTime) {
    printf("Arrived at %d \n", floor);
    printf("Door opening \n");
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    *doorOpen = 1;
    *startTime = time(NULL);
}
int door_closeDoor(int floor, int* doorOpen) {
    elevio_doorOpenLamp(0);
    printf("Door closing \n");
    *doorOpen = 0;
    return floor;
}
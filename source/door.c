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

void door_openDoor(int floor, int *p_doorOpen) {
    if (floor != -1) {
        printf("Door opening \n");
        elevio_doorOpenLamp(1);
        *p_doorOpen = 1;
        m_startTime = time(NULL);
    }
}
void door_closeDoor(int* p_doorOpen) {
    if (time(NULL) - m_startTime >= 3){
        elevio_doorOpenLamp(0);
        printf("Door closing \n");
        *p_doorOpen = 0;
    }
}
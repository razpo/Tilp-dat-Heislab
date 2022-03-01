/**
 * @file elevator.h
 * @brief Functions for controlling the physical model
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

/**
 * @brief Decides whether elevator should move up or down to reach destination floor. Function is continuously called, until floor is reached. 
 * 
 * @param[in] destinationFloor Floor that elevator should move towards.
 * @return int 0 if elevator is not yet at destination, 1 if destination is reached. 
 */
int elevator_moveToFloor(int destinationFloor, MotorDirection *dir);

/**
 * @brief Sets elevator to emergency state. All parameters are used to open doors. 
 * @param[in] floor The floor the elevator currently is at.  
 * @param[in] doorOpen Integer value for whether or not doors are open.  
 * @param[in] startTime System time when doors opened, used to count to 3 seconds.  
 * @param[in] activate 1 if emergency should be set, 0 if emergency should be unset
 */
void elevator_setEmergency(int floor, int *doorOpen, time_t *startTime, int activate);

void elevator_init();
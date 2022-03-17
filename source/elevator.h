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
 * Checks whether elevator is above or below destination floor, and also whether or not elevator is coming out of \p emergency state. 
 * 
 * @param[in] destinationFloor Floor that elevator should move towards.
 * @param[in] lastFloor  Last defined floor elevator visited. 
 * @param[in, out] dir Elevators current direction, is used to set direction as well.
 * @param[in] lastDir Elevators previous direction, to figure out exact location if elevator is stopped between floors. 
 */
void elevator_moveToFloor(int destinationFloor, int lastFloor, MotorDirection *dir, MotorDirection lastDir);
/**
 * @brief Checks whether or not elevator has reached destination
 * 
 * @param[in] destinationFloor Floor that elevator should move towards.
 * @param[in, out] dir Elevators current direction, is used to stop elevator.
 * @return int 1 if destination reached, 0 if not.
 */
int elevator_checkArrived(int destinationFloor, MotorDirection *dir);
/**
 * @brief Sets elevator to \p emergency state. Most parameters are used to open doors. 
 * @param[in] floor The floor the elevator currently is at.  
 * @param[in] doorOpen Integer value for whether or not doors are open.  
 * @param[in] activate 1 if \p emergency should be set, 0 if emergency should be unset
 */
void elevator_setEmergency(int floor, int *doorOpen, int activate);
/**
 * @brief First function that runs, makes sure everything is in a defined state. 
 * If elevator is between floors, it is moved down until it reaches a defined floor. 
 * 
 */
void elevator_init();
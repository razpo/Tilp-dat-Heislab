/**
 * @file door.h
 * @brief Functions for opening and closing the doors. 
 * @version 0.1
 * @date 2022-02-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
/**
 * @brief Opens the doors, starts the timer, and sets doorOpen = 1. 
 * 
 * @param[in] floor The floor the elevator currently is at.  
 * @param[out] doorOpen Integer value for whether or not doors are open.  
 * @param[out] startTime System time when doors opened, used to count to 3 seconds.  
 */
void openDoor(int floor, int* doorOpen, time_t* startTime);
/**
 * @brief Closes the doors and sets doorOpen = 0.
 * 
 * @param[in] floor The floor the elevator currently is at.
 * @param[out] doorOpen nteger value for whether or not doors are open.  
 * @return floor, to set lastFloor equal to last floor visited.  
 */
int closeDoor(int floor, int* doorOpen);
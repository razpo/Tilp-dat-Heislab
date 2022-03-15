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

static time_t m_startTime;
/**
 * @brief Opens the doors, starts the timer, and sets \a doorOpen = 1. 
 * 
 * @param[in] floor The floor the elevator currently is at.  
 * @param[out] doorOpen Integer value for whether or not doors are open.   
 */
void door_openDoor(int floor, int *doorOpen);
/**
 * @brief Closes the doors and sets \a doorOpen = 0, if 3 seconds have passed since timer started. 
 * 
 * @param[in] floor The floor the elevator currently is at.
 * @param[out] doorOpen Integer value for whether or not doors are open.  
 */
void door_closeDoor( int* doorOpen);
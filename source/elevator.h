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
 * @brief Movement to given floor. 
 * @param[in] floor The floor the elevator is set to move to.  
 * @return motorDirection value
*/
int move_to_floor(int floor);

/**
 * @brief Sets elevator to emergency mode
 * @return emergencyValue
 */
int checkEmergency(void);
/**
 * @file buttons.h
 * @brief Functions for communicating with buttons. 
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
/**
 * @brief Turns off all the button lamps for the given floors.
 * 
 * @param[in] floor Floor where button lamps should be turned off
 */
void buttons_clearLights(int floor);
/**
 * @brief Checks every button for press, if a button is pressed the light is turned on, and signal is sent to the controller
 * 
 */
void buttons_getButtonPress();
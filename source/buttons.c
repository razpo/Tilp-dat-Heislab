/**
 * @file buttons.c
 * @brief Implementation of the button-functions. 
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>

#include "driver/elevio.h"
#include "buttons.h"
void buttons_clearLights(int floor) {
    for (int b = 0; b < N_BUTTONS; b++) {
        elevio_buttonLamp(floor, b, 0);
    }
}

void buttons_registerButtonPresses(){
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int buttonType = 0; buttonType < N_BUTTONS; buttonType++) {
            if (elevio_callButton(floor, buttonType)) {
                controller_addFloorOrder(floor, buttonType);
                elevio_buttonLamp(floor, buttonType, 1);
            }
        }
    }
}

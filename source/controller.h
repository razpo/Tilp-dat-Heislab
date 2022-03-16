/**
 * @file controller.h
 * @brief Function for managing the floor queue and sending floor destination to elevator
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

typedef enum{
    NO_ORDER = 0,
    HALL_UP = 1,
    HALL_DOWN = 2,
    HALL_UP_AND_DOWN = 3,
    CAB = 4
} OrderType; 


static OrderType m_floorOrders[N_FLOORS] = {NO_ORDER, NO_ORDER, NO_ORDER, NO_ORDER};


/**
 * @brief Returns the elevator destination based on elevators movement, position and order array.
 * The function has an array \a possibleDestinations[] where each element is 0 or 1, depending on whether the elevator should service the floor at the corresponding index.
 * This is determined by the elevators direction, and the direction of the orders at the floors.  
 *
 * @param[in] direction Direction of elevators movement.
 * @param[in] lastFloor Floor elevator last visited. 
 * 
 * @return Elevator's destination

 *
 */
int controller_getDestination(MotorDirection direction, int lastFloor);
/**
 * @brief Find the closest floor to elevators last visited floor. Is used to give the elevator the most optimal destination.
 * Example: \p possibleDestinations = [0 0 1 1], \p lastFloor = 1. Returns 2. 
 * Function biases upwards.
 * @param[in] possibleDestinations A list of destinations that elevator should visit. 
 * @param[in] lastFloor Floor elevator last visited. 
 * @return int The closest floor to the elevators last visited floor. 
 */
int controller_getClosestFloor(int possibleDestinations[], int lastFloor);
/**
 * @brief Adds an order to the array \a m_floorOrders, according to which button has been pressed. 
 * ButtonType \a CAB takes priority, so if the order in the array is \a CAB, it will not be changed. 
 * 
 * @param[in] requestedFloor The floor where a request was added. 
 * @param[in] btnType Which type of button was pressed. 
 */
void controller_addFloorOrder(int requestedFloor, ButtonType btnType);
/**
 * @brief Removes an order from the order array. Used when elevator has arrived
 * 
 * @param[in] floor The floor that has been servived. 
 */
void controller_removeFloorOrder(int floor);
/**
 * @brief Removes all orders from the \a m_floorOrders array. Used when emergency mode activates
 * 
 */
void controller_emptyFloorOrders();





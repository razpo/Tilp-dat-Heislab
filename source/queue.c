#include "queue.h"
#include <stdio.h>


void removeFloorOrder(int floor){
    floorOrders[floor] = NO_ORDER;  
}


void emptyFloorOrders(){
    for (int i = 0; i < N_FLOORS; i++)
    {
        floorOrders[i] = NO_ORDER;
    }
}

void addFloorOrder(int requestedFloor, ButtonType btnType){
    OrderType order = floorOrders[requestedFloor];
    if(order == NO_ORDER){
        switch (btnType){
            case BUTTON_HALL_UP:
                order = HALL_UP;
                break;
            case BUTTON_HALL_DOWN:
                order = HALL_DOWN;
                break;
            case BUTTON_CAB:
                order = CAB;
                break;
            default: 
                break;
        }
    } else if(order != CAB){
        switch (btnType){
            case BUTTON_HALL_UP:
                if(order != HALL_UP){
                    order = HALL_UP_AND_DOWN;
                }
                break;
            case BUTTON_HALL_DOWN:
                if(order != HALL_DOWN){
                    order = HALL_UP_AND_DOWN;
                }
                break;
            case BUTTON_CAB:
                order = CAB;
                break;
            default: 
                break;
        }
    }

    floorOrders[requestedFloor] = order;
    printf("Order: %d \n", (int)order);
}
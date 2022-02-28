#include "queue.h"

int getClosestFloor(int possibleDestinations[], int lastFloor){
    int closestDestination = -1;

    for (int i = 0; i < N_FLOORS; i++){
        if (possibleDestinations[i] == 1 && (abs(i - lastFloor) < abs(i - closestDestination))){
            closestDestination = i;
        } 
    }
    return closestDestination;
}

int getDestination(MotorDirection direction, int lastFloor){
    int possible_destinations[] = {1,1,1,1};

    for(int i = 0;i<N_FLOORS;i++){
        if ((floorOrders[i] == NO_ORDER) || (floorOrders[i] == HALL_UP && direction == DIRN_DOWN) || (floorOrders[i] == HALL_DOWN && direction == DIRN_UP)){
            possible_destinations[i] = 0;
        }
    };

    return getClosestFloor(possible_destinations, lastFloor);
}

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

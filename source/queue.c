#pragma once
#include <queue.h>
#include <elevio.h>

int getClosestFloor(int possibleDestinations[], int lastFloor){
    int closestDestination = -1;

    for (int i = 0; i < N_FLOORS; i++)
    {
        if (possibleDestinations[i] = 1 && (abs(i - lastFloor) < abs(i - closestDestination)))
        {
            closestDestination = i;
        } 
    }
    return closestDestination;
}

int getDestination(MotorDirection direction, int lastFloor){
    int possible_destinations[] = {1,1,1,1};

    for(int i = 0;i<N_FLOORS;i++){
        if ((floorOrders[i] == NO_ORDER) || (floorOrders[i] == HALL_UP && direction == DIRN_DOWN) || (floorOrders[i] == HALL_DOWN && direction == DIRN_UP))
        {
            possible_destinations[i] = 0;
        }
    };

    return getClosestFloor(possible_destinations, lastFloor);

}


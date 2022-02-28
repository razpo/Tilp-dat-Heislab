
#include "queue.h"
#include <stdio.h>
































































































void removeFloorOrder(int floor){
    floorOrders[floor-1] = NO_ORDER;  
}


void emptyFloorOrder(){
    floorOrders[0] = NO_ORDER;
    floorOrders[1] = NO_ORDER;
    floorOrders[2] = NO_ORDER;
    floorOrders[3] = NO_ORDER;
}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "heismodul.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    MotorDirection dir = DIRN_UP;

    int nextFloor = 1;
    int floor = elevio_floorSensor();
    int lastFloor = -1;
    int doorOpen = 0;
    time_t startTime = time(NULL);
    // startup: move down until elevator reaches any floor. 
    while(floor == -1){
        floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);
    } 
    elevio_motorDirection(DIRN_STOP);
    printf("Elevator ready, now sleep for two seconds just to testing\n");
    sleep(2);
    while(1){
        floor = elevio_floorSensor();
        printf("floor: %d \n",floor);  
        //test for arrivedDestination floor: when elevator reaches any floor, open door.
        if(floor != -1 && floor != lastFloor){
	        openDoor(floor, &doorOpen, &startTime);
            if(time(NULL) - startTime > 3){
                lastFloor = closeDoor(floor, &doorOpen);
            }
            if(!doorOpen){
                elevio_motorDirection(dir);
            }
        }
        //skeleton_project: make elevator go up and down (forever)
        if(!doorOpen){
            if(floor == 0){
                dir = DIRN_UP;
                elevio_motorDirection(dir);
            }
            if(floor == N_FLOORS-1){
                dir = DIRN_DOWN;
                elevio_motorDirection(dir);
            }
        }
        


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

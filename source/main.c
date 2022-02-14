#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <unistd.h> 



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);
    MotorDirection dir = DIRN_UP;
    int currFloor = -1;
    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor != -1 && floor != currFloor){
	    currFloor = floor;
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            sleep(3);
            elevio_doorOpenLamp(0);
            elevio_motorDirection(dir);
            elevio_floorIndicator(currFloor);
        }
        if(floor == 0){
            dir = DIRN_UP;
            elevio_motorDirection(dir);
        }
        if(floor == N_FLOORS-1){
	        dir = DIRN_DOWN;
            elevio_motorDirection(dir);
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

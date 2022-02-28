#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "door.h"
#include "queue.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int g_nextFloor = 1;
    int g_currFloor = elevio_floorSensor();
    int g_doorOpen = 0;
    time_t g_startTime = time(NULL);
    MotorDirection g_dir = DIRN_DOWN;
    // startup: move down until elevator reaches any floor. 
    while(g_currFloor == -1){
        g_currFloor = elevio_floorSensor();
        elevio_motorDirection(g_dir);
    } 
    elevio_motorDirection(DIRN_STOP);
    printf("Elevator ready, now sleep for two seconds just for testing\n");
    sleep(2);
    g_dir = DIRN_DOWN;
    elevio_motorDirection(g_dir);
    
    while(1){
        if (checkEmergency(g_currFloor, &g_doorOpen, &g_startTime)) {
            g_nextFloor = -1;
        } 
        g_currFloor = elevio_floorSensor();
        printf("floor: %d \n",g_currFloor);  


        //test for arrivedDestination floor: when elevator reaches any floor, open door.
        if(g_nextFloor != -1){
            int arrived = moveToFloor(g_nextFloor);
            if(arrived){
                if(!g_doorOpen){
                    openDoor(g_currFloor, &g_doorOpen, &g_startTime);
                } else {
                    if(elevio_obstruction()){
                        g_startTime = time(NULL);
                        printf("Obstruction \n");
                    }
                    if(time(NULL) - g_startTime > 3){
                        closeDoor(g_currFloor, &g_doorOpen);
                        //nextFloor = -1;
                        g_nextFloor = (g_nextFloor + 1) % (N_FLOORS);
                    }
                }
            }
        }

        //skeleton_project: make elevator go up and down (forever)
        
        if(g_currFloor == 0){
            g_dir = DIRN_UP;
        }
        if(g_currFloor == N_FLOORS-1){
            g_dir = DIRN_DOWN;
        }
        
        for(int floor = 0; floor < N_FLOORS; floor++){
            for(int buttonType = 0; buttonType < N_BUTTONS; buttonType++){
                if(elevio_callButton(floor, buttonType)){
                    printf("Button for floor %d pressed", floor);
                    printf("Button type: %d", buttonType);
                    addFloorOrder(floor, buttonType);
                }
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

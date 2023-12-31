/*
 * TacheADC.c
 *
 *  Created on: 30 nov. 2023
 *      Author: TP-EO-1
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>
#include <TacheADC/TacheADC.h>

#define TacheADC_TASK_PRIORITY 3
#define TacheADC_TASK_STACK_SIZE 1024

// Initialize a Task struct handler
Task_Struct TacheADC;

// Allocating 1024 octets on the stack
uint8_t TacheADCStack[TacheADC_TASK_STACK_SIZE];

// Define semaphore data structure + handling events
Semaphore_Struct semTacheADCStruct;
Semaphore_Handle semTacheADCHandle;

// Main function of the ADC Task : Well just a setup + endless while loop^
void TacheADC_taskFxn(UArg a0, UArg a1){
    // Declaration d�une structure clock_Params
    Clock_Params clockParams;
    // Initialisation de la structure
    Clock_Params_init(&clockParams);
    // Reglage de la periode a 10 ms
    clockParams.period = 10 * (1000/Clock_tickPeriod);
    // Initialisation du timer (Clock en RTOS)
    Clock_construct(&myClock, myClockSwiFxn, 0, &clockParams);
    //Lancement du timer
    Clock_start(Clock_handle(&myClock));
    for(;;){

    }
}

void TacheADC_CreateTask(void){
    Semaphore_Params semParams;
    Task_Params taskParams;
    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = TacheADCStack;
    taskParams.stackSize = TacheADC_TASK_STACK_SIZE;
    taskParams.priority = TacheADC_TASK_PRIORITY;
    Task_construct(&TacheADC, TacheADC_taskFxn, &taskParams, NULL);

    /* Construct a Semaphore object
    to be used as a resource lock, initial count 0 */
    Semaphore_Params_init(&semParams);
    Semaphore_construct(&semTacheADCStruct, 0, &semParams);
    /* Obtain instance handle */
    semTacheADCHandle = Semaphore_handle(&semTacheADCStruct);

    // Timer init
    static Clock_Struct myClock;
}

void myClockSwiFxn(uintptr_t arg0)
{
    Semaphore_post(semTacheADCHandle);
}

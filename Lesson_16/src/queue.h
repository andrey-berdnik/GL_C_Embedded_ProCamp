#ifndef H_QUEUE
#define H_QUEUE

#include "hal.h"

int QueueGetNexFlour(int current_floor); //tested
void QueueAppend(int floor);             //tested
void QueueDrop();                        //tested
void QueueRemove(int floor);             //tested

void QueueInit(H_HAL_trigger_CB rqp); //tested
#endif
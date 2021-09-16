#ifndef H_QUEUE
#define H_QUEUE

#include "hal.h"

int QueueGetNexFloor(int current_floor); 
void QueueAppend(int floor);             
void QueueDrop(void);                        
void QueueRemove(int floor);             

void QueueInit(H_HAL_trigger_CB rqp); 
#endif // H_QUEUE
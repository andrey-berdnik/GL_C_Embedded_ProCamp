#include "queue.h"
#include "stdbool.h"
#include "hal.h"

bool queue[4][2];

int QueueGetNexFlour(int current_floor)
{
    for (int i = current_floor; i <= 3; i++)
    {
        if (queue[i][1] == true || queue[i][0] == true)
        {
            return i;
        }
    }

    for (int i = current_floor; i >= 1; i--)
    {
        if (queue[i][1] == true || queue[i][0] == true)
        {
            return i;
        }
    }

    return 0;
}

void processKeysFloor3InCabin()
{
    queue[3][0] = true;
}
void processKeysFloor2InCabin()
{
    queue[2][0] = true;
}
void processKeysFloor1InCabin()
{
    queue[1][0] = true;
}

void processKeysFloor1OutCabin()
{
    queue[1][1] = true;
}
void processKeysFloor2OutCabin()
{
    queue[2][1] = true;
}
void processKeysFloor3OutCabin()
{
    queue[3][1] = true;
}

void QueueDrop()
{
    for (int i = 1; i <= 3; i++)
    {
        queue[i][0] = false;
        queue[i][1] = false;
    }
}

void QueueRemove(int floor)
{
    queue[floor][0] = false;
    queue[floor][1] = false;
}

void QueueInit()
{

    QueueDrop();
    HAL_KeysFloor3InCabin_CB_set(processKeysFloor3InCabin);
    HAL_KeysFloor2InCabin_CB_set(processKeysFloor2InCabin);
    HAL_KeysFloor1InCabin_CB_set(processKeysFloor1InCabin);
    
    HAL_KeysFloor1OutCabin_CB_set(processKeysFloor1OutCabin);
    HAL_KeysFloor2OutCabin_CB_set(processKeysFloor2OutCabin);
    HAL_KeysFloor3OutCabin_CB_set(processKeysFloor3OutCabin);
}

void QueueAppend(int floor) {
    queue[floor][0]=true;
    queue[floor][1]=true;
}
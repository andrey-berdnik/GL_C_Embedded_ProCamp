#include "queue.h"
#include "stdbool.h"
#include "hal.h"

bool queue[4][2];
H_HAL_trigger_CB run_queue_processing;

static void processKeysFloor3InCabin(void);
static void processKeysFloor2InCabin(void);
static void processKeysFloor1InCabin(void);
static void processKeysFloor1OutCabin(void);
static void processKeysFloor2OutCabin(void);
static void processKeysFloor3OutCabin(void);


int QueueGetNexFloor(int current_floor)
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

static void processKeysFloor3InCabin(void)
{
    queue[3][0] = true;
    run_queue_processing();
}
static void processKeysFloor2InCabin(void)
{
    queue[2][0] = true;
    run_queue_processing();
}
static void processKeysFloor1InCabin(void)
{
    queue[1][0] = true;
    run_queue_processing();
}

static void processKeysFloor1OutCabin(void)
{
    queue[1][1] = true;
    run_queue_processing();
}
static void processKeysFloor2OutCabin(void)
{
    queue[2][1] = true;
    run_queue_processing();
}
static void processKeysFloor3OutCabin(void)
{
    queue[3][1] = true;
    run_queue_processing();
}

void QueueDrop(void)
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

void QueueInit(H_HAL_trigger_CB rqp)
{
    run_queue_processing = rqp;
    QueueDrop();
    HAL_KeysFloor3InCabin_CB_set(processKeysFloor3InCabin);
    HAL_KeysFloor2InCabin_CB_set(processKeysFloor2InCabin);
    HAL_KeysFloor1InCabin_CB_set(processKeysFloor1InCabin);

    HAL_KeysFloor1OutCabin_CB_set(processKeysFloor1OutCabin);
    HAL_KeysFloor2OutCabin_CB_set(processKeysFloor2OutCabin);
    HAL_KeysFloor3OutCabin_CB_set(processKeysFloor3OutCabin);
}

void QueueAppend(int floor)
{
    queue[floor][0] = true;
    queue[floor][1] = true;
    run_queue_processing();
}
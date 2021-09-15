//#include "hal.h"
#include "stdio.h"
#include "stdbool.h"

#include "main.h"

#include "motor.h"
#include "door.h"
#include "queue.h"
#include "cabin.h"

void init()
{
    DoorInit();
    QueueInit();
    MotorInit();
    CabinInit();


    HAL_KeysStop_CB_set(processKeysStop);

    QueueDrop();
    DoorClose();
    MotorLowSpeedDown();
}



void processKeysStop()
{
    QueueDrop();
    MotorSpeedOff();
    CabinBrackeEnable();
    printf("Stop process initialized");
}

void loop()
{

    if (CabinGetCurrentFloor() == QueueGetNexFlour(CabinGetCurrentFloor()))
    {
        MotorSpeedOff();
        CabinBrackeEnable();
        DoorOpen();
        DoorClose();
        QueueRemove(CabinGetCurrentFloor());
        runMoveToTargetFloor();
    }
}



////////////////////

bool loopEnable = true;

void moveUp()
{
    DoorClose();
    CabinBrackeDisable();
    MotorLowSpeedUp();
}

void moveDown()
{
    DoorClose();
    CabinBrackeDisable();
    MotorLowSpeedDown();
}

void runMoveToTargetFloor()
{
    while (QueueGetNexFlour(CabinGetCurrentFloor()) != 0)
    {
        if ((CabinGetCurrentFloor - QueueGetNexFlour(CabinGetCurrentFloor())) > 0)
        { //need move up
            moveUp();
        }
        else if ((CabinGetCurrentFloor - QueueGetNexFlour(CabinGetCurrentFloor())) < 0)
        { //need move down
            moveDown();
        }
        else
        {
            DoorClose();
            CabinBrackeEnable();
            //do nothing, we already on floor
        }
    }
}

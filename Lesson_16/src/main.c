//#include "hal.h"
#include "stdio.h"
#include "stdbool.h"

#include "main.h"

#include "motor.h"
#include "door.h"
#include "queue.h"
#include "cabin.h"

void processKeysStop()
{
    QueueDrop();
    MotorSpeedOff();
    CabinBrackeEnable();
    printf("Stop process initialized");
}

void MainInit()
{
    DoorInit();
    MotorInit();
    CabinInit(MotorSpeedOff, MotorLowSpeedDown);
    CabinMaping();

    HAL_KeysStop_CB_set(processKeysStop);

    QueueDrop();
    DoorClose();

    QueueInit(MainRunMoveToTargetFloor);
}




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

void MainRunMoveToTargetFloor()
{

    while (QueueGetNexFlour(CabinGetCurrentFloor()) != 0)
    {
        if (MotorGetState() == e_MotorSpeedOff && CabinBrackeGetStatus()==e_CabinBrackeEnable) // if system do nothing
        {
            if (CabinGetCurrentFloor() < QueueGetNexFlour(CabinGetCurrentFloor()))
            { //need move up
                moveUp();
            }
            else if (CabinGetCurrentFloor() > QueueGetNexFlour(CabinGetCurrentFloor()))
            { //need move down
                moveDown();
            }
            else
            {
                DoorClose();
                CabinBrackeEnable();
                //do nothing, we already on required floor
            }
        }
    }
}

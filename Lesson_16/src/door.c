#include "door.h"
#include "hal.h"

static dState doorState = e_DoorUknow;


void DoorClose()
{
    if (doorState != e_DoorClosed)
    {
        doorState = e_DoorClosing;
        HAL_DoorActuatorsClosing();
    }
}

void processHAL_LimitSwitchesDoorClosed()
{
    doorState = e_DoorClosed;
    HAL_DoorActuatorsOff();
}

void DoorOpen()
{
    if (doorState != e_DoorOpened)
    {
        doorState = e_DoorOpening;
        HAL_DoorActuatorsOpening();
    }
}

void processHAL_LimitSwitchesDoorOpened()
{
    doorState = e_DoorOpened;
    HAL_DoorActuatorsOff();
}

dState DoorGetState()
{
    return doorState;
}

void DoorInit()
{
    doorState = e_DoorUknow;
    HAL_LimitSwitchesDoorOpened_CB_set(processHAL_LimitSwitchesDoorOpened);
    HAL_LimitSwitchesDoorClosed_CB_set(processHAL_LimitSwitchesDoorClosed);
}

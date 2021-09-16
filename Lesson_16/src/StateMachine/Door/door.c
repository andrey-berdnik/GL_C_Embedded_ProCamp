#include "door.h"
#include "hal.h"

static dState doorState = e_DoorUknow;
static void processHAL_LimitSwitchesDoorClosed(void);
static void processHAL_LimitSwitchesDoorOpened(void);

void DoorClose(void)
{
    if (doorState != e_DoorClosed)
    {
        doorState = e_DoorClosing;
        HAL_DoorActuatorsClosing();
    }
}

static void processHAL_LimitSwitchesDoorClosed(void)
{
    doorState = e_DoorClosed;
    HAL_DoorActuatorsOff();
}

void DoorOpen(void)
{
    if (doorState != e_DoorOpened)
    {
        doorState = e_DoorOpening;
        HAL_DoorActuatorsOpening();
    }
}

static void processHAL_LimitSwitchesDoorOpened(void)
{
    doorState = e_DoorOpened;
    HAL_DoorActuatorsOff();
}

dState DoorGetState(void)
{
    return doorState;
}

void DoorInit(void)
{
    doorState = e_DoorUknow;
    HAL_LimitSwitchesDoorOpened_CB_set(processHAL_LimitSwitchesDoorOpened);
    HAL_LimitSwitchesDoorClosed_CB_set(processHAL_LimitSwitchesDoorClosed);
}

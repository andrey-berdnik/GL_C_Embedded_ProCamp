#include "stdio.h"
#include "stdbool.h"

#include "main.h"

#include "StateMachine/Motor/motor.h"
#include "StateMachine/Door/door.h"
#include "StateMachine/Queue/queue.h"
#include "StateMachine/Cabin/cabin.h"

void floorChanged();
void stateChanged();

static int previos_floor = 0;
static positionType previosPosition = e_CabinPositionUknow;

typedef enum
{
    e_MainMovingUknow,
    e_MainMovingStop,
    e_MainMovingUp,
    e_MainMovingDown
} e_MainMovingDirection;

static e_MainMovingDirection MovingDirection = e_MainMovingUknow;

void processKeysStop()
{
    QueueDrop();
    MotorSpeedOff();
    CabinBrackeEnable();
    printf("Stop process initialized");
    MovingDirection = e_MainMovingStop;
}

void MainInit()
{
    DoorInit();
    MotorInit();
    CabinInit(MotorSpeedOff,
              MotorLowSpeedDown,
              MotorLowSpeedUp,
              floorChanged,
              stateChanged);
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
    MovingDirection = e_MainMovingUp;
}

void moveDown()
{
    DoorClose();
    CabinBrackeDisable();
    MotorLowSpeedDown();
    MovingDirection = e_MainMovingDown;
}

void MainRunMoveToTargetFloor()
{

    if (MotorGetState() == e_MotorSpeedOff && CabinBrackeGetStatus() == e_CabinBrackeEnable) // if system do nothing
    {
        int CurrentFloor = CabinGetCurrentFloor();
        int NextFloor = QueueGetNexFloor(CurrentFloor);
        if (NextFloor > 0)
        {
            if (CurrentFloor < NextFloor)
            { 
                moveUp();
            }
            else if (CurrentFloor > NextFloor)
            { 
                moveDown();
            }
            else
            {
                //do nothing, we already on required floor
            }
        }
    }
}

void floorChanged()
{
    positionType newPosition = CabinGetCurrenPosition();
    int current_floor = CabinGetCurrentFloor();
    int target_floor = QueueGetNexFloor(current_floor);
    if (current_floor == target_floor)
    {
        MotorSpeedOff();
        CabinBrackeEnable();
        DoorOpen();
        QueueRemove(current_floor);
    }
    previos_floor = current_floor;
}

void stateChanged()
{
    positionType newPosition = CabinGetCurrenPosition();
    int current_floor = CabinGetCurrentFloor();
    int taget_floor = QueueGetNexFloor(current_floor);

    if (newPosition != e_CabinPositionFloor)
    {
        if (MovingDirection == e_MainMovingUp)
        {
            if ((taget_floor - current_floor) > 1)
            {
                MotorHighSpeedUp();
            }
            else if (newPosition == e_CabinPositionLow)
            {
                MotorLowSpeedUp();
            }
        }

        if (MovingDirection == e_MainMovingDown)
        {
            if ((current_floor - taget_floor) > 1)
            {
                MotorHighSpeedDown();
            }
            else if (newPosition == e_CabinPositionHigh)
            {
                MotorLowSpeedDown();
            }
        }
    }

    previosPosition = newPosition;
}
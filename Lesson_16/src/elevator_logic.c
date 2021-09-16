#include "stdio.h"
#include "stdbool.h"

#include "elevator_logic.h"

#include "StateMachine/Motor/motor.h"
#include "StateMachine/Door/door.h"
#include "StateMachine/Queue/queue.h"
#include "StateMachine/Cabin/cabin.h"

typedef enum
{
    e_MainMovingUknow,
    e_MainMovingStop,
    e_MainMovingUp,
    e_MainMovingDown
} e_MainMovingDirection;

static int previos_floor = 0;
static positionType previosPosition = e_CabinPositionUknow;
static e_MainMovingDirection MovingDirection = e_MainMovingUknow;

static void floorChanged(void);
static void stateChanged(void);
static void processKeysStop(void);
static void moveUp(void);
static void moveDown(void);
static void floorChanged(void);
static void stateChanged(void);



static void processKeysStop(void)
{
    QueueDrop();
    MotorSpeedOff();
    CabinBrackeEnable();
    printf("Stop process initialized");
    MovingDirection = e_MainMovingStop;
}

void ElevatorLogicInit(void)
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

    QueueInit(ElevatorLogicRunMoveToTargetFloor);
}



static void moveUp(void)
{
    DoorClose();
    CabinBrackeDisable();
    MotorLowSpeedUp();
    MovingDirection = e_MainMovingUp;
}

static void moveDown(void)
{
    DoorClose();
    CabinBrackeDisable();
    MotorLowSpeedDown();
    MovingDirection = e_MainMovingDown;
}

void ElevatorLogicRunMoveToTargetFloor(void)
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

static void floorChanged(void)
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

static void stateChanged(void)
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
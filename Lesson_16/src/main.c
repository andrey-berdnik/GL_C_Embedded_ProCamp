//#include "hal.h"
#include "stdio.h"
#include "stdbool.h"

#include "main.h"

#include "motor.h"
#include "door.h"
#include "queue.h"
#include "cabin.h"

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
        int NextFloor = QueueGetNexFlour(CurrentFloor);
        if (NextFloor > 0)
        {
            if (CurrentFloor < NextFloor)
            { //need move up
                moveUp();
            }
            else if (CurrentFloor > NextFloor)
            { //need move down
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
    int target_floor = QueueGetNexFlour(current_floor);
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
    int taget_floor = QueueGetNexFlour(current_floor);

    //some logic for speed_up\speed_down

    previosPosition = newPosition;
}
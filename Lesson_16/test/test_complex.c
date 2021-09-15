#include "unity.h"
#include "main.h"

#include "motor.h"
#include "door.h"
#include "queue.h"
#include "cabin.h"

#include "mock_hal.h"

#include "setup_hal_cb.c"

void setUp(void)
{
    setUp_motor_hal();
    setUP_door_hal();
    setUp_queue_hal();
    setUP_cabin_hal();
    setUp_main_hal();

    HAL_MotorSpeedOff_Expect();
    HAL_CabinBrakesOn_Expect();
    HAL_MotorLowSpeedDown_Expect();

    HAL_DoorActuatorsClosing_Expect();

    MainInit();

    HAL_MotorSpeedOff_Expect();
    LimitSwitchesCabinMin();
}

void tearDown(void)
{
}

void test_0_to_2()
{
    HAL_DoorActuatorsClosing_Expect();
    HAL_CabinBrakesOff_Expect();
    HAL_MotorLowSpeedUp_Expect();
    KeysFloor2OutCabin();

    LimitSwitchesCabinFloorLow(); // 0 to 1
    LimitSwitchesCabinFloor();

    LimitSwitchesCabinFloorHigh(); //1 to 2

    LimitSwitchesCabinFloorLow();

    HAL_MotorSpeedOff_Expect();
    HAL_CabinBrakesOn_Expect();
    HAL_DoorActuatorsOpening_Expect();

    LimitSwitchesCabinFloor();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

}


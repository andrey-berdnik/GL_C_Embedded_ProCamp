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
}

void tearDown(void)
{
}

void test_1()
{
}
#include "StateMachine/Motor/motor.h"

#include "mock_hal.h"

#include  "support/setup_motor_cb.h"

void setUp(void)
{
    setUp_motor_hal();
    HAL_MotorSpeedOff_Expect();
    MotorInit();
}

void tearDown(void)
{
}

void test_MotorGetState()
{
    TEST_ASSERT(MotorGetState() == e_MotorSpeedOff);

    HAL_MotorLowSpeedUp_Expect();
    MotorLowSpeedUp();

    TEST_ASSERT(MotorGetState() == e_MotorLowSpeedUp);
}

void test_MotorLowSpeedUp()
{
    HAL_MotorLowSpeedUp_Expect();
    MotorLowSpeedUp();

    TEST_ASSERT(MotorGetState() == e_MotorLowSpeedUp);

    MotorLowSpeedUp();
}

void test_MotorHighSpeedUp()
{
    HAL_MotorHighSpeedUp_Expect();
    MotorHighSpeedUp();

    TEST_ASSERT(MotorGetState() == e_MotorHighSpeedUp);

    MotorHighSpeedUp();
}
void test_MotorLowSpeedDown()
{
    HAL_MotorLowSpeedDown_Expect();
    MotorLowSpeedDown();

    TEST_ASSERT(MotorGetState() == e_MotorLowSpeedDown);

    MotorLowSpeedDown();
}

void test_MotorHighSpeedDown()
{
    HAL_MotorHighSpeedDown_Expect();
    MotorHighSpeedDown();

    TEST_ASSERT(MotorGetState() == e_MotorHighSpeedDown);

    MotorHighSpeedDown();
}

void test_MotorSpeedOff()
{
    HAL_MotorHighSpeedDown_Expect();
    MotorHighSpeedDown();

    HAL_MotorSpeedOff_Expect();
    MotorSpeedOff();

    TEST_ASSERT(MotorGetState() == e_MotorSpeedOff);
}

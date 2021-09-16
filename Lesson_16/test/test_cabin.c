#include "StateMachine/Cabin/cabin.h"
#include "mock_hal.h"

#include "support/setup_cabin_cb.h"

static int motor_off_count = 0;
static int motor_low_down_count = 0;
static int motor_low_up_count = 0;
static int floor_changed_count = 0;
static int position_changed_count = 0;

static void motor_off(void)
{
    motor_off_count++;
}

static void motor_low_down(void)
{
    motor_low_down_count++;
}

static void motor_low_up(void)
{
    motor_low_up_count++;
}

static void floor_changed(void)
{
    floor_changed_count++;
}

static void position_changed(void)
{
    position_changed_count++;
}

void setUp(void)
{
    setUP_cabin_hal();
    HAL_CabinBrakesOn_Expect();
    CabinInit(motor_off, motor_low_down, motor_low_up, floor_changed, position_changed);
}

void tearDown(void)
{
    motor_off_count = 0;
    motor_low_down_count = 0;
    motor_low_up_count = 0;
    floor_changed_count = 0;
    position_changed_count = 0;
}

void test_CabinBrakes(void)
{
    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeEnable);

    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();

    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeDisable);

    HAL_CabinBrakesOn_Expect();
    CabinBrackeEnable();
    CabinBrackeEnable();
    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeEnable);

    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();
    CabinBrackeDisable();
    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeDisable);
}

void test_floor_counting(void)
{
    CabinSet(1, e_CabinPositionFloor);

    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(2, CabinGetCurrentFloor());

    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(3, CabinGetCurrentFloor());

    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(3, CabinGetCurrentFloor());

    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(2, CabinGetCurrentFloor());

    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(1, CabinGetCurrentFloor());

    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloor();
    TEST_ASSERT_EQUAL_INT(1, CabinGetCurrentFloor());
}

void test_cabin_maping(void)
{
    HAL_CabinBrakesOff_Expect();
    CabinMaping(); // start maping must run motor

    // for test case cabin was on 2 floor
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloor();
    LimitSwitchesCabinFloorLow();

    LimitSwitchesCabinMin();

    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionMin);

    LimitSwitchesCabinFloorLow();

    HAL_CabinBrakesOn_Expect();
    LimitSwitchesCabinFloor();
}

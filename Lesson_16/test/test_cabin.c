#include "unity.h"
#include "cabin.h"
#include "mock_hal.h"

#include "setup_hal_cb.c"

static int motor_off_count = 0;
static void motor_off()
{
    motor_off_count++;
}

static int motor_on_count = 0;
static void motor_on()
{
    motor_on_count++;
}


static int floor_changed_count = 0;
static void floor_changed()
{
    floor_changed_count++;
}

static int position_changed_count = 0;
static void position_changed()
{
    position_changed_count++;
}


void setUp(void)
{
    setUP_cabin_hal();
    HAL_CabinBrakesOn_Expect();
    CabinInit(motor_on, motor_off, floor_changed, position_changed);
}

void tearDown(void)
{
}

void test_CabinBrakes()
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

void test_floor_counting()
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

void test_cabin_maping()
{
    CabinMaping(); // start maping must run motor

    // for test case cabin was on 2 floor
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinFloorHigh();
    LimitSwitchesCabinFloor();
    LimitSwitchesCabinFloorLow();
    LimitSwitchesCabinMin();

    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionMin);
}

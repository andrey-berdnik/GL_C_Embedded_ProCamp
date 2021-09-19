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

void test_CabinBrackeEnable_1_unit()
{
    CabinBrackeEnable();
}

void test_CabinBrackeEnable_2_unit()
{
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();
    HAL_CabinBrakesOn_Expect();
    CabinBrackeEnable();
}

void test_CabinBrackeDisable_1_unit(void)
{
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();
}

void test_CabinBrackeDisable_2_unit(void)
{
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();
    CabinBrackeDisable();
}

void test_Cabin_set_unit(void)
{
    CabinSet(1, e_CabinPositionFloor);

    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionFloor);
    TEST_ASSERT(CabinGetCurrentFloor() == 1);

    CabinSet(2, e_CabinPositionHigh);

    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionHigh);
}

void test_CabinMaping_unit(void)
{
    HAL_CabinBrakesOff_Expect();
    CabinMaping();
    TEST_ASSERT(motor_low_down_count == 1);
}

void test_CabinGetCurrentFloor_unit(void)
{
    CabinSet(1, e_CabinPositionFloor);
    TEST_ASSERT(CabinGetCurrentFloor() == 1);
    CabinSet(3, e_CabinPositionFloor);
    TEST_ASSERT(CabinGetCurrentFloor() == 3);
}

void test_CabinBrackeGetStatus_unit(void)
{
    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeEnable);
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();
    TEST_ASSERT(CabinBrackeGetStatus() == e_CabinBrackeDisable);
}

void test_LimitSwitchesCabinFloorHigh_CB_unit(void)
{
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionUknow);
    LimitSwitchesCabinFloorHigh();
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionHigh);
}

void test_LimitSwitchesCabinFloor_CB_moving_up_unit(void)
{
    CabinSet(1, e_CabinPositionLow);
    LimitSwitchesCabinFloor();
    TEST_ASSERT(CabinGetCurrentFloor() == 2);
}

void test_LimitSwitchesCabinFloor_CB_moving_down_unit(void)
{
    CabinSet(2, e_CabinPositionHigh);
    LimitSwitchesCabinFloor();
    TEST_ASSERT(CabinGetCurrentFloor() == 1);
}

void test_LimitSwitchesCabinFloorLow_CB_unit(void)
{
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionUknow);
    LimitSwitchesCabinFloorLow();
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionLow);
}

void test_LimitSwitchesCabinMax_CB_unit(void)
{
    //setup state
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();

    //test
    HAL_CabinBrakesOn_Expect();
    LimitSwitchesCabinMax();
    TEST_ASSERT(CabinGetCurrentFloor() == 4);
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionMax);
}

void test_LimitSwitchesCabinMin_CB_unit(void)
{
    //setup state
    HAL_CabinBrakesOff_Expect();
    CabinBrackeDisable();

    //test
    LimitSwitchesCabinMin();
    TEST_ASSERT(CabinGetCurrentFloor() == 0);
    TEST_ASSERT(CabinGetCurrenPosition() == e_CabinPositionMin);
}

void test_CabinBrakes_functional(void)
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

void test_floor_counting_functional(void)
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

void test_cabin_maping_1_functional(void)
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

void test_cabin_maping_2_functional(void)
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

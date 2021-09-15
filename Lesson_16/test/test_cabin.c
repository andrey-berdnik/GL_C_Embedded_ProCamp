#include "unity.h"
#include "cabin.h"

#include "mock_hal.h"

H_HAL_trigger_CB LimitSwitchesCabinFloorHigh;
H_HAL_trigger_CB LimitSwitchesCabinFloor;
H_HAL_trigger_CB LimitSwitchesCabinFloorLow;

static void LimitSwitchesCabinFloorHigh_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesCabinFloorHigh = callback;
}

static void LimitSwitchesCabinFloor_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesCabinFloor = callback;
}

static void LimitSwitchesCabinFloorLow_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesCabinFloorLow = callback;
}

void setUp(void)
{
    HAL_LimitSwitchesCabinFloorHigh_set_StubWithCallback(LimitSwitchesCabinFloorHigh_CB_set);
    HAL_LimitSwitchesCabinFloor_CB_set_StubWithCallback(LimitSwitchesCabinFloor_CB_set);
    HAL_LimitSwitchesCabinFloorLow_CB_set_StubWithCallback(LimitSwitchesCabinFloorLow_CB_set);
    HAL_CabinBrakesOn_Expect();
    CabinInit();
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
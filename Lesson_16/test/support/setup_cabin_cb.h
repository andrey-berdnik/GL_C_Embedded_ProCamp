#include "mock_hal.h"

H_HAL_trigger_CB LimitSwitchesCabinFloorHigh;
H_HAL_trigger_CB LimitSwitchesCabinFloor;
H_HAL_trigger_CB LimitSwitchesCabinFloorLow;
H_HAL_trigger_CB LimitSwitchesCabinMax;
H_HAL_trigger_CB LimitSwitchesCabinMin;

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

static void LimitSwitchesCabinMax_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesCabinMax = callback;
}

static void LimitSwitchesCabinMin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesCabinMin = callback;
}

void setUP_cabin_hal()
{
    HAL_LimitSwitchesCabinFloorHigh_set_StubWithCallback(LimitSwitchesCabinFloorHigh_CB_set);
    HAL_LimitSwitchesCabinFloor_CB_set_StubWithCallback(LimitSwitchesCabinFloor_CB_set);
    HAL_LimitSwitchesCabinFloorLow_CB_set_StubWithCallback(LimitSwitchesCabinFloorLow_CB_set);

    HAL_LimitSwitchesCabinMax_CB_set_StubWithCallback(LimitSwitchesCabinMax_CB_set);
    HAL_LimitSwitchesCabinMin_CB_set_StubWithCallback(LimitSwitchesCabinMin_CB_set);
}

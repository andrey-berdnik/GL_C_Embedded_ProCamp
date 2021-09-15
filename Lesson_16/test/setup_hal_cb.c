#include "mock_hal.h"

static H_HAL_trigger_CB LimitSwitchesDoorOpened;
static void LimitSwitchesDoorOpened_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesDoorOpened = callback;
    //HAL_LimitSwitchesDoorOpened_CB_set
}

static H_HAL_trigger_CB LimitSwitchesDoorClosed;
static void LimitSwitchesDoorClosed_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesDoorClosed = callback;
    //HAL_LimitSwitchesDoorOpened_CB_set
}

void setUP_door_hal()
{
    HAL_LimitSwitchesDoorOpened_CB_set_StubWithCallback(LimitSwitchesDoorOpened_CB_set);
    HAL_LimitSwitchesDoorClosed_CB_set_StubWithCallback(LimitSwitchesDoorClosed_CB_set);
}

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

static H_HAL_trigger_CB KeysFloor3InCabin;
static H_HAL_trigger_CB KeysFloor2InCabin;
static H_HAL_trigger_CB KeysFloor1InCabin;
static H_HAL_trigger_CB KeysFloor1OutCabin;
static H_HAL_trigger_CB KeysFloor2OutCabin;
static H_HAL_trigger_CB KeysFloor3OutCabin;

static void KeysFloor3InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor3InCabin = callback;
}

static void KeysFloor2InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor2InCabin = callback;
}

static void KeysFloor1InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor1InCabin = callback;
}

static void KeysFloor3OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor3OutCabin = callback;
}

static void KeysFloor2OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor2OutCabin = callback;
}

static void KeysFloor1OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor1OutCabin = callback;
}

void setUp_queue_hal()
{
    HAL_KeysFloor3InCabin_CB_set_StubWithCallback(KeysFloor3InCabin_CB_set);
    HAL_KeysFloor2InCabin_CB_set_StubWithCallback(KeysFloor2InCabin_CB_set);
    HAL_KeysFloor1InCabin_CB_set_StubWithCallback(KeysFloor1InCabin_CB_set);

    HAL_KeysFloor3OutCabin_CB_set_StubWithCallback(KeysFloor3OutCabin_CB_set);
    HAL_KeysFloor2OutCabin_CB_set_StubWithCallback(KeysFloor2OutCabin_CB_set);
    HAL_KeysFloor1OutCabin_CB_set_StubWithCallback(KeysFloor1OutCabin_CB_set);
}

void setUp_motor_hal()
{
}

//Expect();

static H_HAL_trigger_CB KeysStop;

static void KeysStop_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysStop = callback;
}

void setUp_main_hal()
{
    HAL_KeysStop_CB_set_StubWithCallback(KeysStop_CB_set);
}
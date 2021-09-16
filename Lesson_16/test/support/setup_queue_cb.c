#include "mock_hal.h"

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

#include "mock_hal.h"


static H_HAL_trigger_CB KeysStop;

static void KeysStop_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysStop = callback;
}

void setUp_main_hal()
{
    HAL_KeysStop_CB_set_StubWithCallback(KeysStop_CB_set);
}
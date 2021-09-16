#include "mock_hal.h"

static H_HAL_trigger_CB LimitSwitchesDoorOpened;
static void LimitSwitchesDoorOpened_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesDoorOpened = callback;
}

static H_HAL_trigger_CB LimitSwitchesDoorClosed;
static void LimitSwitchesDoorClosed_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    LimitSwitchesDoorClosed = callback;
}

void setUP_door_hal()
{
    HAL_LimitSwitchesDoorOpened_CB_set_StubWithCallback(LimitSwitchesDoorOpened_CB_set);
    HAL_LimitSwitchesDoorClosed_CB_set_StubWithCallback(LimitSwitchesDoorClosed_CB_set);
}

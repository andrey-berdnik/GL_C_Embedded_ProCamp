#include "unity.h"
#include "door.h"
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

void setUp(void)
{
    HAL_LimitSwitchesDoorOpened_CB_set_StubWithCallback(LimitSwitchesDoorOpened_CB_set);
    HAL_LimitSwitchesDoorClosed_CB_set_StubWithCallback(LimitSwitchesDoorClosed_CB_set);
    DoorInit();
}

void tearDown(void)
{
}

void test_door_opening(void)
{
    TEST_ASSERT(DoorGetState()==e_DoorUknow);
    //Open door
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    TEST_ASSERT(DoorGetState()==e_DoorOpened);
}

void test_door_open_and_close_door(void)
{
    TEST_ASSERT(DoorGetState()==e_DoorUknow);
    //Open door
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    TEST_ASSERT(DoorGetState()==e_DoorOpened);

    //Close door
    HAL_DoorActuatorsClosing_Expect();
    DoorClose();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorClosed();

    TEST_ASSERT(DoorGetState()==e_DoorClosed);
}
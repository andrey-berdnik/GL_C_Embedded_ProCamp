#include "StateMachine/Door/door.h"
#include "mock_hal.h"

#include "support/setup_door_cb.h"

void setUp(void)
{
    setUP_door_hal();
    DoorInit();
}

void tearDown(void)
{
}

void test_DoorOpen_1_unit(void)
{

    HAL_DoorActuatorsOpening_Expect();
    DoorOpen(); // door openint
}

void test_DoorOpen_2_unit(void)
{
    //setup to set door opened
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    DoorOpen(); // do nothing
}

void test_DoorClose_1_unit(void)
{
    HAL_DoorActuatorsClosing_Expect();
    DoorClose();
}

void test_DoorClose_2_unit(void)
{
    //setup to set door closed
    HAL_DoorActuatorsClosing_Expect();
    DoorClose();
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorClosed();

    DoorClose(); //do nothing
}

void test_DoorGetState_1_unit(void)
{
    TEST_ASSERT(DoorGetState() == e_DoorUknow);
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();
    TEST_ASSERT(DoorGetState() == e_DoorOpened);
}

void test_DoorGetState_2_unit(void)
{
    TEST_ASSERT(DoorGetState() == e_DoorUknow);
    HAL_DoorActuatorsClosing_Expect();
    DoorClose();
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorClosed();
    TEST_ASSERT(DoorGetState() == e_DoorClosed);
}

/*

static H_HAL_trigger_CB LimitSwitchesDoorOpened;
static H_HAL_trigger_CB LimitSwitchesDoorClosed;
*/

void test_LimitSwitchesDoorOpened_CB_unit(void)
{
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();
    TEST_ASSERT(DoorGetState()==e_DoorOpened);
}

void test_LimitSwitchesDoorClosed_CB_unit(void)
{
    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorClosed();
    TEST_ASSERT(DoorGetState()==e_DoorClosed);
}

void test_door_opening_functional(void)
{
    TEST_ASSERT(DoorGetState() == e_DoorUknow);
    //Open door
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    TEST_ASSERT(DoorGetState() == e_DoorOpened);
}

void test_door_open_and_close_door_process_functional(void)
{
    TEST_ASSERT(DoorGetState() == e_DoorUknow);
    //Open door
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    TEST_ASSERT(DoorGetState() == e_DoorOpened);

    //Close door
    HAL_DoorActuatorsClosing_Expect();
    DoorClose();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorClosed();

    TEST_ASSERT(DoorGetState() == e_DoorClosed);
}
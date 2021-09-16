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

void test_door_opening_process(void)
{
    TEST_ASSERT(DoorGetState() == e_DoorUknow);
    //Open door
    HAL_DoorActuatorsOpening_Expect();
    DoorOpen();

    HAL_DoorActuatorsOff_Expect();
    LimitSwitchesDoorOpened();

    TEST_ASSERT(DoorGetState() == e_DoorOpened);
}

void test_door_open_and_close_door_process(void)
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
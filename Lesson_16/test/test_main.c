#include "main.h"

#include "support/setup_main_cb.c"

#include "mock_hal.h"
#include "mock_motor.h"
#include "mock_door.h"
#include "mock_queue.h"
#include "mock_cabin.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_no_quite(void)
{
    MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
    CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);

    // Determinate dirrection  (check to UP)
    CabinGetCurrentFloor_ExpectAndReturn(1); // get current for compare
    QueueGetNexFlour_ExpectAndReturn(1, 0);

    MainRunMoveToTargetFloor();
}

// I don't like the way I made the tests.
//But I like the way I made the code, so I won't adjust the code for tests.

void test_move_from_1_to_2(void)
{
    // Check that task not in progress
    MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
    CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);

    // Determinate dirrection  (now 1, need to 2, than UP)
    CabinGetCurrentFloor_ExpectAndReturn(1); // get current for compare
    QueueGetNexFlour_ExpectAndReturn(1, 2);

    //Start moving
    DoorClose_Expect();
    CabinBrackeDisable_Expect();
    MotorLowSpeedUp_Expect();

    MainRunMoveToTargetFloor();
}

void test_move_from_2_to_1(void)
{
    // Check that task not in progress
    MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
    CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);

    // Determinate dirrection  (now 2, need to 1, than Down)
    CabinGetCurrentFloor_ExpectAndReturn(2); // get current for compare
    QueueGetNexFlour_ExpectAndReturn(2, 1);

    //Start moving
    DoorClose_Expect();
    CabinBrackeDisable_Expect();
    MotorLowSpeedDown_Expect();

    MainRunMoveToTargetFloor();
}
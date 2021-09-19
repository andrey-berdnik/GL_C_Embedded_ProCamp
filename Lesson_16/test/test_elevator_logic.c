
#include "elevator_logic.h"

#include "mock_motor.h"
#include "mock_door.h"
#include "mock_queue.h"
#include "mock_cabin.h"

#include "mock_hal.h"

static H_HAL_trigger_CB KeysStop_CB;
static H_HAL_trigger_CB MotorSpeedOff_CB;
static H_HAL_trigger_CB MotorLowSpeedDown_CB;
static H_HAL_trigger_CB MotorLowSpeedUp_CB;
static H_HAL_trigger_CB floorChanged_CB;
static H_HAL_trigger_CB stateChanged_CB;
static H_HAL_trigger_CB ElevatorLogicRunMoveToTargetFloor_CB;

static void ElevatorLogicRunMoveToTargetFloor_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
  ElevatorLogicRunMoveToTargetFloor_CB = callback;
}

static void KeysStop_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
  KeysStop_CB = callback;
}

static void CabinInit_CB_set2(H_HAL_trigger_CB callback0,
                              H_HAL_trigger_CB callback1,
                              H_HAL_trigger_CB callback2,
                              H_HAL_trigger_CB callback3,
                              H_HAL_trigger_CB callback4,
                              int cmock_num_calls)
{
  MotorSpeedOff_CB = callback0;
  MotorLowSpeedDown_CB = callback1;
  MotorLowSpeedUp_CB = callback2;
  floorChanged_CB = callback3;
  stateChanged_CB = callback4;
}

void setUp(void)
{
  DoorInit_Expect();
  MotorInit_Expect();

  CabinInit_StubWithCallback(CabinInit_CB_set2);

  //CabinInit_Ignore();

  CabinMaping_Expect();
  HAL_KeysStop_CB_set_StubWithCallback(KeysStop_CB_set);

  QueueDrop_Expect();
  DoorClose_Expect();
  QueueInit_StubWithCallback(ElevatorLogicRunMoveToTargetFloor_CB_set);
  ElevatorLogicInit();
}

void tearDown(void)
{
}

void test_ElevatorLogicRunMoveToTargetFloor_1_unit()
{
  MotorGetState_ExpectAndReturn(e_MotorLowSpeedDown);
  ElevatorLogicRunMoveToTargetFloor();
}

void test_ElevatorLogicRunMoveToTargetFloor_2_unit()
{
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeDisable);
  ElevatorLogicRunMoveToTargetFloor();
}

void test_ElevatorLogicRunMoveToTargetFloor_Up_unit()
{
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 2);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedUp_Expect();
  ElevatorLogicRunMoveToTargetFloor();
}

void test_ElevatorLogicRunMoveToTargetFloor_Down_unit()
{
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(3);
  QueueGetNexFloor_ExpectAndReturn(3, 1);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedDown_Expect();
  ElevatorLogicRunMoveToTargetFloor();
}

void test_KeysStop_CB_unit(void)
{
  QueueDrop_Expect();
  MotorSpeedOff_Expect();
  CabinBrackeEnable_Expect();
  KeysStop_CB();
}

void test_MotorSpeedOff_CB_unit(void)
{
  MotorSpeedOff_Expect();
  MotorSpeedOff_CB();
}

void test_MotorLowSpeedDown_CB_unit(void)
{
  MotorLowSpeedDown_Expect();
  MotorLowSpeedDown_CB();
}

void test_MotorLowSpeedUp_CB_unit(void)
{
  MotorLowSpeedUp_Expect();
  MotorLowSpeedUp_CB();
}

/*
static H_HAL_trigger_CB stateChanged_CB;
*/

void test_floorChanged_CB_not_required_floor_unit(void)
{
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionFloor);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 2);
  floorChanged_CB();
}

void test_floorChanged_CB_required_floor_unit(void)
{
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionFloor);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 1);

  MotorSpeedOff_Expect();
  CabinBrackeEnable_Expect();
  DoorOpen_Expect();
  QueueRemove_Expect(1);
  floorChanged_CB();
}

void test_stateChanged_1_unit(void)
{
  //setup state
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionFloor);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 1);
  stateChanged_CB();
}

void test_stateChanged_slow_UP_unit(void)
{

  //setup state
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 2);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedUp_Expect();
  ElevatorLogicRunMoveToTargetFloor();

  //test
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionLow);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 1);

  MotorLowSpeedUp_Expect();
  stateChanged_CB();
}


void test_stateChanged_slow_down_unit(void)
{

  //setup state
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(3);
  QueueGetNexFloor_ExpectAndReturn(3, 2);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedDown_Expect();
  ElevatorLogicRunMoveToTargetFloor();

  //test
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionHigh);
  CabinGetCurrentFloor_ExpectAndReturn(3);
  QueueGetNexFloor_ExpectAndReturn(3, 2);

  MotorLowSpeedDown_Expect();
  stateChanged_CB();
}




void test_stateChanged_fast_down_unit(void)
{

  //setup state
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(3);
  QueueGetNexFloor_ExpectAndReturn(3, 2);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedDown_Expect();
  ElevatorLogicRunMoveToTargetFloor();

  //test
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionHigh);
  CabinGetCurrentFloor_ExpectAndReturn(3);
  QueueGetNexFloor_ExpectAndReturn(3, 1);

  MotorHighSpeedDown_Expect();
  stateChanged_CB();
}


void test_stateChanged_fast_up_unit(void)
{

  //setup state
  MotorGetState_ExpectAndReturn(e_MotorSpeedOff);
  CabinBrackeGetStatus_ExpectAndReturn(e_CabinBrackeEnable);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 3);
  DoorClose_Expect();
  CabinBrackeDisable_Expect();
  MotorLowSpeedUp_Expect();
  ElevatorLogicRunMoveToTargetFloor();

  //test
  CabinGetCurrenPosition_ExpectAndReturn(e_CabinPositionHigh);
  CabinGetCurrentFloor_ExpectAndReturn(1);
  QueueGetNexFloor_ExpectAndReturn(1, 3);

  MotorHighSpeedUp_Expect();
  stateChanged_CB();
}

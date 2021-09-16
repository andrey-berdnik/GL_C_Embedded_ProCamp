
#include "elevator_logic.h"

#include "motor.h"
#include "door.h"
#include "queue.h"
#include "cabin.h"

#include "mock_hal.h"

#include "support/setup_cabin_cb.h"
#include "support/setup_door_cb.h"
#include "support/setup_main_cb.h"
#include "support/setup_motor_cb.h"
#include "support/setup_queue_cb.h"

void setUp(void)
{
  setUp_motor_hal();
  setUP_door_hal();
  setUp_queue_hal();
  setUP_cabin_hal();
  setUp_main_hal();

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();

  HAL_CabinBrakesOff_Expect();
  HAL_MotorLowSpeedDown_Expect();

  HAL_DoorActuatorsClosing_Expect();

  ElevatorLogicInit();

  HAL_MotorLowSpeedUp_Expect();
  LimitSwitchesCabinMin();

  LimitSwitchesCabinFloorLow();

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();
  LimitSwitchesCabinFloor();
}

void tearDown(void)
{
}

void test_movin_on_call_from_1_to_2_floor_proccess()
{

  HAL_DoorActuatorsClosing_Expect();
  HAL_CabinBrakesOff_Expect();
  HAL_MotorLowSpeedUp_Expect();
  KeysFloor2OutCabin();

  LimitSwitchesCabinFloorHigh(); //1 to 2

  LimitSwitchesCabinFloorLow();

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();
  HAL_DoorActuatorsOpening_Expect();

  LimitSwitchesCabinFloor();

  HAL_DoorActuatorsOff_Expect();
  LimitSwitchesDoorOpened();
}

void test_movin_on_call_from_1_to_3_floor_proccess()
{

  HAL_DoorActuatorsClosing_Expect();
  HAL_CabinBrakesOff_Expect();
  HAL_MotorLowSpeedUp_Expect();
  KeysFloor3OutCabin();

  HAL_MotorHighSpeedUp_Expect();
  
  LimitSwitchesCabinFloorHigh(); //1 to 2
  LimitSwitchesCabinFloorLow();
  
  LimitSwitchesCabinFloor();  //2 


  LimitSwitchesCabinFloorHigh(); //2 to 3
  HAL_MotorLowSpeedUp_Expect();
  LimitSwitchesCabinFloorLow(); 

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();
  HAL_DoorActuatorsOpening_Expect();
  LimitSwitchesCabinFloor();  //3

  HAL_DoorActuatorsOff_Expect();
  LimitSwitchesDoorOpened();

}


void test__movin_on_call_from_1_to_3_pause_3_to_2_floor_proccess()
{

  HAL_DoorActuatorsClosing_Expect();
  HAL_CabinBrakesOff_Expect();
  HAL_MotorLowSpeedUp_Expect();
  KeysFloor3OutCabin();

  HAL_MotorHighSpeedUp_Expect();
  
  LimitSwitchesCabinFloorHigh(); //1 to 2
  LimitSwitchesCabinFloorLow();
  
  LimitSwitchesCabinFloor();  //2 


  LimitSwitchesCabinFloorHigh(); //2 to 3
  HAL_MotorLowSpeedUp_Expect();
  LimitSwitchesCabinFloorLow(); 

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();
  HAL_DoorActuatorsOpening_Expect();
  LimitSwitchesCabinFloor();  //3

  HAL_DoorActuatorsOff_Expect();
  LimitSwitchesDoorOpened();

  HAL_DoorActuatorsClosing_Expect();
  HAL_CabinBrakesOff_Expect();
  HAL_MotorLowSpeedDown_Expect();
  KeysFloor2InCabin();

  LimitSwitchesCabinFloorLow();
  LimitSwitchesCabinFloorHigh();

  HAL_MotorSpeedOff_Expect();
  HAL_CabinBrakesOn_Expect();
  HAL_DoorActuatorsOpening_Expect();
  LimitSwitchesCabinFloor();

}
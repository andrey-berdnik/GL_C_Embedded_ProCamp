#ifndef H_HAL
#define H_HAL

typedef void (*H_HAL_trigger_CB)(void);

void HAL_MotorLowSpeedUp(); //im,test.
void HAL_MotorHighSpeedUp(); //im,test.
void HAL_MotorLowSpeedDown(); //im,test.
void HAL_MotorHighSpeedDown(); //im,test.
void HAL_MotorSpeedOff(); //im,test.

void HAL_CabinBrakesOff();
void HAL_CabinBrakesOn();

void HAL_DoorActuatorsOpening(); //im,test.
void HAL_DoorActuatorsClosing(); //im,test.
void HAL_DoorActuatorsOff();     //im,test.

void HAL_LimitSwitchesCabinMax_CB_set(H_HAL_trigger_CB callback); // mainInit()
void HAL_LimitSwitchesCabinMin_CB_set(H_HAL_trigger_CB callback); //mainInit()
void HAL_KeysStop_CB_set(H_HAL_trigger_CB callback);              //mainInit()

void HAL_LimitSwitchesCabinFloorHigh_set(H_HAL_trigger_CB callback);   //cabinInit()
void HAL_LimitSwitchesCabinFloor_CB_set(H_HAL_trigger_CB callback);    //cabinInit()
void HAL_LimitSwitchesCabinFloorLow_CB_set(H_HAL_trigger_CB callback); //cabinInit()

void HAL_LimitSwitchesDoorOpened_CB_set(H_HAL_trigger_CB callback); // doorInit() , tested
void HAL_LimitSwitchesDoorClosed_CB_set(H_HAL_trigger_CB callback); // doorInit() , tested

void HAL_KeysFloor3InCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested
void HAL_KeysFloor2InCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested
void HAL_KeysFloor1InCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested

void HAL_KeysFloor1OutCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested
void HAL_KeysFloor2OutCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested
void HAL_KeysFloor3OutCabin_CB_set(H_HAL_trigger_CB callback); //QueueInit() , tested

#endif
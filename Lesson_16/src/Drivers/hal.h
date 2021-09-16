#ifndef H_HAL
#define H_HAL

typedef void (*H_HAL_trigger_CB)(void);

void HAL_MotorLowSpeedUp();
void HAL_MotorHighSpeedUp();
void HAL_MotorLowSpeedDown(); 
void HAL_MotorHighSpeedDown(); 
void HAL_MotorSpeedOff(); 

void HAL_CabinBrakesOff();
void HAL_CabinBrakesOn();

void HAL_DoorActuatorsOpening(); 
void HAL_DoorActuatorsClosing(); 
void HAL_DoorActuatorsOff();    

void HAL_LimitSwitchesCabinMax_CB_set(H_HAL_trigger_CB callback); 
void HAL_LimitSwitchesCabinMin_CB_set(H_HAL_trigger_CB callback); 
void HAL_KeysStop_CB_set(H_HAL_trigger_CB callback);              

void HAL_LimitSwitchesCabinFloorHigh_set(H_HAL_trigger_CB callback);   
void HAL_LimitSwitchesCabinFloor_CB_set(H_HAL_trigger_CB callback);    
void HAL_LimitSwitchesCabinFloorLow_CB_set(H_HAL_trigger_CB callback); 

void HAL_LimitSwitchesDoorOpened_CB_set(H_HAL_trigger_CB callback); 
void HAL_LimitSwitchesDoorClosed_CB_set(H_HAL_trigger_CB callback); 

void HAL_KeysFloor3InCabin_CB_set(H_HAL_trigger_CB callback); 
void HAL_KeysFloor2InCabin_CB_set(H_HAL_trigger_CB callback); 
void HAL_KeysFloor1InCabin_CB_set(H_HAL_trigger_CB callback); 

void HAL_KeysFloor1OutCabin_CB_set(H_HAL_trigger_CB callback); 
void HAL_KeysFloor2OutCabin_CB_set(H_HAL_trigger_CB callback); 
void HAL_KeysFloor3OutCabin_CB_set(H_HAL_trigger_CB callback); 

#endif
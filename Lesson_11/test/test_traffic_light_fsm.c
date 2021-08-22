#include "unity.h"
#include "traffic_light_fsm.h"
#include "mock_lamp_driver.h"

void setup(void)
{
    // set stuff up here
}
void teardown(void)
{
    // clean stuff up here
}

/*
* Given Traffic Light FSM is not initialized
* When FSM initialization occurs
* Then Lamp Driver shall be initialized
* And Red Lamp Flashing mode shall be activated on vehicle lights for both NS-SN and EW-We directions
* And Don't Walk lamp shall be switched on for both NS-SN and EW-We directions
*/
void test_Initialization(void)
{

    LDRV_Init_Expect();
    
    LDRV_EwweRedLampFlashing_Expect();
    LDRV_NssnRedLampFlashing_Expect();
    LDRV_EwweDontWalkLampOn_Expect();
    LDRV_NssnDontWalkLampOn_Expect();
    
    TLFSM_Init();
}

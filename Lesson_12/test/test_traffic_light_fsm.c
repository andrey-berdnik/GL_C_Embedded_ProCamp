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

void SwitchToDefaultPhase()
{
    LDRV_EwweRedLampFlashing_Expect();
    LDRV_NssnRedLampFlashing_Expect();
    LDRV_EwweDontWalkLampOn_Expect();
    LDRV_NssnDontWalkLampOn_Expect();
    TLFSM_SwitchToDefaultPhase();
}

void test_Phase1_to_Phase8(void)
{

    for (int i = 0; i <= 9; i++)
    {

        LDRV_Init_Expect();
        LDRV_EwweRedLampFlashing_Expect();
        LDRV_NssnRedLampFlashing_Expect();
        LDRV_EwweDontWalkLampOn_Expect();
        LDRV_NssnDontWalkLampOn_Expect();
        TLFSM_Init(); // init
        if (i == 0)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_EwweWalkLampOn_Expect();
        LDRV_EwweGreenLampOn_Expect();
        LDRV_NssnRedLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 1
        if (i == 1)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_EwweDontWalkLampFlashing_Expect();
        TLFSM_SwitchToNextPhase(); // to 2
        if (i == 2)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_EwweYellowLampOn_Expect();
        LDRV_EwweDontWalkLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 3
        if (i == 3)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_EwweRedLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 4
        if (i == 4)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_NssnGreenLampOn_Expect();
        LDRV_NssnWalkLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 5
        if (i == 5)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_NssnDontWalkLampFlashing_Expect();
        TLFSM_SwitchToNextPhase(); // to 6
        if (i == 6)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_NssnYellowLampOn_Expect();
        LDRV_NssnDontWalkLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 7
        if (i == 7)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_NssnRedLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 8
        if (i == 8)
        {
            SwitchToDefaultPhase();
            continue;
        }

        LDRV_EwweGreenLampOn_Expect();
        LDRV_EwweWalkLampOn_Expect();
        TLFSM_SwitchToNextPhase(); // to 1
        if (i == 9)
        {
            SwitchToDefaultPhase();
            continue;
        }
    }
}
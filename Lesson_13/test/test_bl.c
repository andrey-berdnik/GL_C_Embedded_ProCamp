#include "unity.h"
#include "bl.h"
#include "mock_h_timer.h"
#include "mock_h_pio.h"

static H_TIMER_CB ut_callback;
static void ut_H_TimInit_callback(H_TIMER_CB callback, int cmock_num_calls)
{
    ut_callback = callback;
}

void setUp(void)
{
    H_PioInit_Expect();
    H_TimInit_StubWithCallback(ut_H_TimInit_callback);
    BL_Init();
}
void tearDown(void)
{

}
/* Given bl unit is iniitializatted
* When first interrupt occurs
* Then Blue leds shall be activated
*/
void test(void)
{
    H_PioSwitchBlueLeds_Expect();
    ut_callback();

    H_PioSwitchRedLeds_Expect();
    ut_callback();

    H_PioSwitchOrangeLeds_Expect();
    ut_callback();

    H_PioSwitchGreenLeds_Expect();
    ut_callback();

    H_PioSwitchBlueLeds_Expect();
    ut_callback();

}


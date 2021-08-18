#include "unity.h"
#include "advanced_system_health_monitor.c"

#define MAX_SPEED 180
#define MIN_SPEED 0

#define MAX_GEAR 5
#define MIN_GEAR -1

#define MAX_RPM 6000
#define MIN_RPM 0

typedef struct test_case
{
    BOOLEAN_E waiting_result;
    unsigned short speed;
    signed char gear;
    unsigned short rpm;
    unsigned char isHandbrakeActive;
    char message[100];
} test_case;

void setUp(void)
{
}
void tearDown(void)
{
}

/**
 * Given sets of check combination
 * When SHM_AreMovingParametersValid  is called
 * Then it shall return value according combination
 */
void test_diff_one(void)
{
    test_case cases[] =
        {
            {.waiting_result = INVALID, .speed = 180, .gear = 6, .rpm = 6000, .isHandbrakeActive = 0, .message = "UP out of range gearbox"},
            {.waiting_result = INVALID, .speed = 180, .gear = -2, .rpm = 6000, .isHandbrakeActive = 0, .message = "Down out of range gearbox"},
            {.waiting_result = INVALID, .speed = 181, .gear = 2, .rpm = 6000, .isHandbrakeActive = 0, .message = "UP out of range speed"},
            {.waiting_result = INVALID, .speed = 180, .gear = 2, .rpm = 6001, .isHandbrakeActive = 0, .message = "UP out of range RPM"},
            {.waiting_result = INVALID, .speed = 10, .gear = 1, .rpm = 10, .isHandbrakeActive = 1, .message = "Runing with handbrake"}
            // and soo one
        };

    for (int i = 0; i <= sizeof(cases); i++)
    {
        BOOLEAN_E actual = INVALID;
        actual = SHM_AreMovingParametersValid(cases[i].speed, cases[i].gear, cases[i].rpm, cases[i].isHandbrakeActive);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[i].waiting_result, actual, cases[i].message);
    }
}

/**
 * Given all parametrs in correct range
 * When SHM_AreMovingParametersValid  is called
 * Then it shall return VALID
 */
void test_for_valid_data(void)
{

    char str[80];

    for (int speed = MIN_SPEED; speed <= MAX_SPEED; speed++)
    {
        for (int gear = MIN_GEAR; gear <= MAX_GEAR; gear++)
        {
            for (int rpm = MIN_RPM; rpm <= MAX_RPM; rpm++)
            {
                BOOLEAN_E actual = INVALID;
                actual = SHM_AreMovingParametersValid(speed, gear, rpm, 0);
                sprintf(str, "Error on valid data: speed %d gear %d rpm %d handbracke 0", speed, gear, rpm);
                TEST_ASSERT_EQUAL_INT_MESSAGE(VALID, actual, str);
            }
        }
    }
}


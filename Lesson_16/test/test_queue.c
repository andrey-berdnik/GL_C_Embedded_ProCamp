#include "unity.h"
#include "queue.h"

#include "mock_hal.h"

static H_HAL_trigger_CB KeysFloor3InCabin;
static H_HAL_trigger_CB KeysFloor2InCabin;
static H_HAL_trigger_CB KeysFloor1InCabin;
static H_HAL_trigger_CB KeysFloor1OutCabin;
static H_HAL_trigger_CB KeysFloor2OutCabin;
static H_HAL_trigger_CB KeysFloor3OutCabin;

static void KeysFloor3InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor3InCabin = callback;
}

static void KeysFloor2InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor2InCabin = callback;
}

static void KeysFloor1InCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor1InCabin = callback;
}

static void KeysFloor3OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor3OutCabin = callback;
}

static void KeysFloor2OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor2OutCabin = callback;
}

static void KeysFloor1OutCabin_CB_set(H_HAL_trigger_CB callback, int cmock_num_calls)
{
    KeysFloor1OutCabin = callback;
}

void setUp(void)
{
    HAL_KeysFloor3InCabin_CB_set_StubWithCallback(KeysFloor3InCabin_CB_set);
    HAL_KeysFloor2InCabin_CB_set_StubWithCallback(KeysFloor2InCabin_CB_set);
    HAL_KeysFloor1InCabin_CB_set_StubWithCallback(KeysFloor1InCabin_CB_set);

    HAL_KeysFloor3OutCabin_CB_set_StubWithCallback(KeysFloor3OutCabin_CB_set);
    HAL_KeysFloor2OutCabin_CB_set_StubWithCallback(KeysFloor2OutCabin_CB_set);
    HAL_KeysFloor1OutCabin_CB_set_StubWithCallback(KeysFloor1OutCabin_CB_set);

    QueueInit();
}

void tearDown(void)
{
}

void test_press_KF3OC_to_KF1OC(void)
{

    KeysFloor3OutCabin();
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFlour(1));

    KeysFloor2OutCabin();
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFlour(1));

    KeysFloor1OutCabin();
    TEST_ASSERT_EQUAL_INT(1, QueueGetNexFlour(1));
}

void test_press_KF3IC_to_KF1IC(void)
{
    KeysFloor3InCabin();
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFlour(1));

    KeysFloor2InCabin();
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFlour(1));

    KeysFloor1InCabin();
    TEST_ASSERT_EQUAL_INT(1, QueueGetNexFlour(1));
}

void test_QueueManage()
{
    QueueAppend(1);
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFlour(3));

    QueueAppend(3);
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFlour(3));

    QueueDrop();
    QueueAppend(3);
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFlour(1));

    QueueRemove(2);
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFlour(1));
}
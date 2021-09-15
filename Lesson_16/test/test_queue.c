#include "unity.h"
#include "queue.h"

#include "mock_hal.h"

#include "setup_hal_cb.c"

static int run_quite_processing_count = 0;
static void run_quite_processing()
{
    run_quite_processing_count++;
}

void setUp(void)
{
    setUp_queue_hal();

    QueueInit(run_quite_processing);
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
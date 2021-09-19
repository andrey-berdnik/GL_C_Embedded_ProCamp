#include "StateMachine/Queue/queue.h"

#include "mock_hal.h"

#include "support/setup_queue_cb.h"

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
    run_quite_processing_count = 0;
    QueueDrop();
}

void test_QueueAppend_unit(void)
{
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));
}

void test_QueueGetNexFloor_1_unit(void)
{
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));
}

void test_QueueGetNexFloor_2_unit(void)
{
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(3));
}

void test_QueueGetNexFloor_3_unit(void)
{
    QueueAppend(2);
    QueueAppend(3);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));
}

void test_QueueGetNexFloor_4_unit(void)
{
    QueueAppend(1);
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(3));
}

void test_QueueDrop_unit(void)
{
    QueueAppend(1);
    QueueAppend(2);
    QueueDrop();
    TEST_ASSERT_EQUAL_INT(0, QueueGetNexFloor(3));
}

void test_QueueRemove_unit()
{
    QueueAppend(1);
    QueueAppend(2);
    QueueRemove(2);
    TEST_ASSERT_EQUAL_INT(1, QueueGetNexFloor(3));
}



void test_KeysFloor3InCabin_CB_unit(void)
{
    KeysFloor3InCabin();
    TEST_ASSERT(QueueGetNexFloor(1) == 3);
}

void test_KeysFloor3OutCabin_CB_unit(void)
{
    KeysFloor3OutCabin();
    TEST_ASSERT(QueueGetNexFloor(1) == 3);
}

void test_KeysFloor2InCabin_CB_unit(void)
{
    KeysFloor2InCabin();
    TEST_ASSERT(QueueGetNexFloor(1) == 2);
}

void test_KeysFloor2OutCabin_CB_unit(void)
{
    KeysFloor2OutCabin();
    TEST_ASSERT(QueueGetNexFloor(1) == 2);
}

void test_KeysFloor1InCabin_CB_unit(void)
{
    KeysFloor1InCabin();
    TEST_ASSERT(QueueGetNexFloor(2) == 1);
}

void test_KeysFloor1OutCabin_CB_unit(void)
{
    KeysFloor1OutCabin();
    TEST_ASSERT(QueueGetNexFloor(2) == 1);
}

void test_press_KF3OC_to_KF1OC_functional(void)
{

    KeysFloor3OutCabin();
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFloor(1));

    KeysFloor2OutCabin();
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));

    KeysFloor1OutCabin();
    TEST_ASSERT_EQUAL_INT(1, QueueGetNexFloor(1));
}

void test_press_KF3IC_to_KF1IC_functional(void)
{
    KeysFloor3InCabin();
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFloor(1));

    KeysFloor2InCabin();
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));

    KeysFloor1InCabin();
    TEST_ASSERT_EQUAL_INT(1, QueueGetNexFloor(1));
}
void test_QueueManage_functional()
{
    QueueAppend(1);
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(3));

    QueueAppend(3);
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFloor(3));

    QueueDrop();
    QueueAppend(3);
    QueueAppend(2);
    TEST_ASSERT_EQUAL_INT(2, QueueGetNexFloor(1));

    QueueRemove(2);
    TEST_ASSERT_EQUAL_INT(3, QueueGetNexFloor(1));
}

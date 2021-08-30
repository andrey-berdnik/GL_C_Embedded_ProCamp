#include "unity.h"
#include "domain_logic.h"
#include "mock_input_processor.h"
#include "mock_output_processor.h"
#include <stdlib.h>

static INPUT_PROCESSOR_FP rd_callback;
static char *pd_buffer;

static void catch_reaDataCB(INPUT_PROCESSOR_FP callback, int cmock_num_calls)
{
    rd_callback = callback;
}

static void catch_buffer(char *buff, int cmock_num_calls)
{
    pd_buffer = buff;
}

void setUp(void)
{
    readData_StubWithCallback(catch_reaDataCB);
    printData_StubWithCallback(catch_buffer);
    createTable();
}
void tearDown(void)
{
}

void test(void)
{
    char buffer[1000];

    for (int i = 0; i < 1000; i++)
    {
        buffer[i]= rand()  % 100;
        rd_callback(&buffer[i], sizeof(buffer[i]));
    }

    for (int i = 0; i < 1000; i++)
    {
        TEST_ASSERT_EQUAL_INT(pd_buffer[i], buffer[i]);
    }
}
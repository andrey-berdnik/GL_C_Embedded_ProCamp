#pragma once
#include "stdio.h"

void check_int(int expected, int actual, int line_number, char *file_name);

void user_function1(void);
int* user_function1_service(void);
void user_function1_Expect(void);

#define TEST_ASSERT_EQUAL_INT(expected, actual) check_int(expected, actual, __LINE__, __FILE__)

void function_call_marker(const char *function_name, int line_number,  int *op);

#define TEST_FUNCTION_CALL_MARKER(f_name, s_name)             \
    do                                                \
    {                                                 \
        const char *function_name = #f_name;          \
        function_call_marker(function_name, __LINE__, s_name()); \
    } while (0)
    
#define SERVICE_FUNCTION_CALL_MARKER()             \
    do                                                \
    {                                                 \
        static int calls_allowed = 0;          \
        return &calls_allowed; \
    } while (0)






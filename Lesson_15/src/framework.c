#include "framework.h"

void check_int(int expected, int actual, int line_number, char *file_name)
{
    if (expected != actual)
    {
        printf("Fail in line %i: Expected %i, actual %i", line_number, expected, actual);
        printf("\nFile name: %s", file_name);
    }
}

void function_call_marker(const char *function_name, int line_number, int *op)
{
    if (*op < 1)
    {
        printf("\nFail in line %i: function %s is called more than expected \n", line_number, function_name);
    }
    
    if (*op > 0)
    {
        *op=*op-1;
    }
}

int* user_function1_service() // generated connection function that store number  of allowed calls and return pointer to it
{
    SERVICE_FUNCTION_CALL_MARKER();   
}

void user_function1(void) // mock of real user function
{
    TEST_FUNCTION_CALL_MARKER(user_function1, user_function1_service);
}

void user_function1_Expect(void) //generated function that increment number of allowed calls
{
    *user_function1_service()=*user_function1_service()+1; 
}
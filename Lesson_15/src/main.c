#include "stdio.h"
#include "framework.h"

int main(void)
{
    TEST_ASSERT_EQUAL_INT(5, 2);
    
    user_function1_Expect();
    user_function1();
    user_function1();


}

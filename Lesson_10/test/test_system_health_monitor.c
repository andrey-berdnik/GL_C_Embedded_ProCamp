#include "unity.h"
#include "system_health_monitor.c"


void setUp(void)
{
}
void tearDown(void)
{
}

/**
 * Given all parametrs equal to minimal valid values
 * When SHM_AreMovingParametersValid  iis called
 * Then it shall return VALID
 */
void test_MovingParametrs_MinimalValues( void )
{
    BOOLEAN_E actual = INVALID;
    actual = SHM_AreMovingParametersValid(0,-1,0,0);
    //TEST_FAIL_MESSAGE("her");
    TEST_ASSERT_EQUAL_INT_MESSAGE( VALID, actual , "her");
}


/**
 * Given all parametrs equal to maximum valid values
 * When SHM_AreMovingParametersValid  iis called
 * Then it shall return VALID
 */
void test_MovingParametrs_MaximalValues( void )
{
    BOOLEAN_E actual = INVALID;
    actual = SHM_AreMovingParametersValid(180,5,6000,0);
    TEST_ASSERT_EQUAL_INT( VALID, actual );
}

/**
 * Given all parametrs equal to normal valid values
 * But selected gear is invalid
 * When SHM_AreMovingParametersValid  iis called
 * Then it shall return VALID
 */
void test_MovingParametrs_Wrong_gearOutOfMin( void )
{
    BOOLEAN_E actual = VALID;
    actual = SHM_AreMovingParametersValid(0,-2,0,0);
    TEST_ASSERT_EQUAL_INT( INVALID, actual );
}

/**
 * Given all parametrs equal to normal valid values
 * But selected gear is invalid
 * When SHM_AreMovingParametersValid  iis called
 * Then it shall return VALID
 */
void test_MovingParametrs_Wrong_gearOutOfMax( void )
{
    BOOLEAN_E actual = VALID;
    actual = SHM_AreMovingParametersValid(0,6,0,0);
    TEST_ASSERT_EQUAL_INT( INVALID, actual );
}


/**
 * Given all parametrs equal to normal valid values
 * But rpm invalid
 * When SHM_AreMovingParametersValid  is called
 * Then it shall return VALID
 */
void test_MovingParametrs_Wrong_RpmOutOfMax( void )
{
    BOOLEAN_E actual = VALID;
    actual = SHM_AreMovingParametersValid(0,-1,6001,0);
    TEST_ASSERT_EQUAL_INT( INVALID, actual );
}


/**
 * Given all parametrs equal to normal valid values
 * But hanbrake invalid
 * When SHM_AreMovingParametersValid  is called
 * Then it shall return VALID
 */
void test_MovingParametrs_Wrong_handbrake( void )
{
    BOOLEAN_E actual = VALID;
    actual = SHM_AreMovingParametersValid(0,-1,5999,2);
    TEST_ASSERT_EQUAL_INT( INVALID, actual );
}


/**
 * Given all parametrs equal to normal valid values
 * But speed is out of range
 * When SHM_AreMovingParametersValid  is called
 * Then it shall return VALID
 */
void test_MovingParametrs_Wrong_Speed( void )
{
    BOOLEAN_E actual = VALID;
    actual = SHM_AreMovingParametersValid(190,1,5999,0);
    TEST_ASSERT_EQUAL_INT( INVALID, actual );
}
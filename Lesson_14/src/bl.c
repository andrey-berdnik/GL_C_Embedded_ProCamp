#include "h_timer.h"
#include "h_pio.h"
#include "bl.h"
#include "stdint.h"

static uint8_t current_state_index;

static void bl_RotationLeds(void);
static void bl_TimerEventHandler(void);

static void bl_State1(void);
static void bl_State2(void);
static void bl_State3(void);
static void bl_State4(void);

typedef void (*BL_STATE_HANDLER)(void);

static const BL_STATE_HANDLER blStates[] = {
    bl_State1,
    bl_State2,
    bl_State3,
    bl_State4};

void BL_Init(void)
{
  current_state_index = 0;
  H_PioInit();
  H_TimInit(bl_TimerEventHandler);
};

static void bl_TimerEventHandler(void)
{
  bl_RotationLeds();
};

static void bl_RotationLeds(void)
{
  BL_STATE_HANDLER current_state;
  current_state = blStates[current_state_index++];
  if (current_state != 0)
  {
    current_state();
  }
  if (current_state_index > 3)
    current_state_index = 0;
}

static void bl_State1(void)
{
  H_PioSwitchBlueLeds();
}

static void bl_State2(void)
{
  H_PioSwitchRedLeds();
}

static void bl_State3(void)
{
  H_PioSwitchOrangeLeds();
}

static void bl_State4(void)
{
  H_PioSwitchGreenLeds();
}

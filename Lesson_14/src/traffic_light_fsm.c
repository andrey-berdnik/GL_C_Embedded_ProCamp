#include "traffic_light_fsm.h"
#include "lamp_driver.h"
#include "string.h"
#include "stdint.h"

static void TLFSM_SET_DEFAULT_PHASE(void);
static void TLFSM_SET_PHASE_1(void);
static void TLFSM_SET_PHASE_2(void);
static void TLFSM_SET_PHASE_3(void);
static void TLFSM_SET_PHASE_4_8(void);
static void TLFSM_SET_PHASE_5(void);
static void TLFSM_SET_PHASE_6(void);
static void TLFSM_SET_PHASE_7(void);
static void TLFSM_SET_PHASE_4_8(void);

typedef enum TLFSM_PHASE
{
    TLFSM_DEFAULT_PHASE,
    TLFSM_PHASE_1,
    TLFSM_PHASE_2,
    TLFSM_PHASE_3,
    TLFSM_PHASE_4_8,
    TLFSM_PHASE_5,
    TLFSM_PHASE_6,
    TLFSM_PHASE_7
} TLFSM_PHASE_E;

typedef struct TLFSM_DATA
{
    TLFSM_PHASE_E activePhase;
    TLFSM_PHASE_E previousPhase;
} TLFSM_DATA_S;

static TLFSM_DATA_S gTlfsmData;

static uint8_t current_state_index = 0;

void TLFSM_Init(void)
{
    memset(&gTlfsmData, 0, sizeof(gTlfsmData));
    LDRV_Init();
    TLFSM_SwitchToDefaultPhase();
}

typedef void (*TL_STATE_HANDLER)(void);

static const TL_STATE_HANDLER tlStates[] = {
    TLFSM_SET_DEFAULT_PHASE,
    TLFSM_SET_PHASE_1,
    TLFSM_SET_PHASE_2,
    TLFSM_SET_PHASE_3,
    TLFSM_SET_PHASE_4_8,
    TLFSM_SET_PHASE_5,
    TLFSM_SET_PHASE_6,
    TLFSM_SET_PHASE_7,
    TLFSM_SET_PHASE_4_8};

void TLFSM_SwitchToNextPhase(void)
{
    TL_STATE_HANDLER current_state;
    current_state = tlStates[current_state_index++];
    if (current_state != 0)
    {
        current_state();
    }
    if (current_state_index > 8)
        current_state_index = 1;
}

void TLFSM_SET_DEFAULT_PHASE()
{
    gTlfsmData.activePhase = TLFSM_PHASE_1;
    gTlfsmData.previousPhase = TLFSM_DEFAULT_PHASE;
    LDRV_EwweWalkLampOn();
    LDRV_EwweGreenLampOn();
    LDRV_NssnRedLampOn();
};

void TLFSM_SET_PHASE_1()
{
    gTlfsmData.activePhase = TLFSM_PHASE_2;
    gTlfsmData.previousPhase = TLFSM_PHASE_1;
    LDRV_EwweDontWalkLampFlashing();
}

void TLFSM_SET_PHASE_2()
{
    gTlfsmData.activePhase = TLFSM_PHASE_3;
    gTlfsmData.previousPhase = TLFSM_PHASE_2;
    LDRV_EwweYellowLampOn();
    LDRV_EwweDontWalkLampOn();
}

void TLFSM_SET_PHASE_3()
{
    gTlfsmData.activePhase = TLFSM_PHASE_4_8;
    gTlfsmData.previousPhase = TLFSM_PHASE_3;
    LDRV_EwweRedLampOn();
}

void TLFSM_SET_PHASE_4_8()
{
    if (gTlfsmData.previousPhase == TLFSM_PHASE_3)
    {
        gTlfsmData.activePhase = TLFSM_PHASE_5;
        LDRV_NssnGreenLampOn();
        LDRV_NssnWalkLampOn();
    }
    else
    {
        gTlfsmData.activePhase = TLFSM_PHASE_1;
        LDRV_EwweGreenLampOn();
        LDRV_EwweWalkLampOn();
    }
    gTlfsmData.previousPhase = TLFSM_PHASE_4_8;
}

void TLFSM_SET_PHASE_5()
{
    gTlfsmData.activePhase = TLFSM_PHASE_6;
    gTlfsmData.previousPhase = TLFSM_PHASE_5;
    LDRV_NssnDontWalkLampFlashing();
}

void TLFSM_SET_PHASE_6()
{
    gTlfsmData.activePhase = TLFSM_PHASE_7;
    gTlfsmData.previousPhase = TLFSM_PHASE_6;
    LDRV_NssnYellowLampOn();
    LDRV_NssnDontWalkLampOn();
}

void TLFSM_SET_PHASE_7()
{
    gTlfsmData.activePhase = TLFSM_PHASE_4_8;
    gTlfsmData.previousPhase = TLFSM_PHASE_7;
    LDRV_NssnRedLampOn();
}

void TLFSM_SwitchToDefaultPhase(void)
{
    gTlfsmData.activePhase = TLFSM_DEFAULT_PHASE;
    gTlfsmData.previousPhase = TLFSM_DEFAULT_PHASE;
    LDRV_EwweRedLampFlashing();
    LDRV_NssnRedLampFlashing();
    LDRV_EwweDontWalkLampOn();
    LDRV_NssnDontWalkLampOn();
    current_state_index = 0;
}

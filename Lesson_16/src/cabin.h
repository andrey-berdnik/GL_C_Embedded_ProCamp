#ifndef  H_CABIN
#define H_CABIN
typedef enum
{
    e_CabinBrackeUknow,
    e_CabinBrackeEnable,
    e_CabinBrackeDisable
} cState;

void CabinBrackeEnable();
void CabinBrackeDisable();

cState CabinBrackeGetStatus();


typedef enum
{
    e_CabinPositionUknow,
    e_CabinPositionMin,
    e_CabinPositionLow,
    e_CabinPositionFloor,
    e_CabinPositionHigh,
    e_CabinPositionMax
} positionType;



void CabinInit();
void CabinSet(int floor, positionType state);
int CabinGetCurrentFloor();


#endif
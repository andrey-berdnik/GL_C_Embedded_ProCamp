#ifndef  H_DOOR
#define H_DOOR

typedef enum
{
    e_DoorUknow,
    e_DoorOpened,
    e_DoorOpening,
    e_DoorClosed,
    e_DoorClosing
} dState;

void DoorInit(void); 
void DoorOpen(void); 
void DoorClose(void); 
dState DoorGetState(void); 

#endif // H_DOOR
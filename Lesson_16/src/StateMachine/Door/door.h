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

void DoorInit(); 
void DoorOpen(); 
void DoorClose(); 
dState DoorGetState(); 

#endif
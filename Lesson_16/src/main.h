#ifndef MAIN_H
#define MAIN_H
void setup();


void DoorOpen();
void DoorClose();

void processHAL_LimitSwitchesDoorOpened();
void processHAL_LimitSwitchesDoorClosed();



void processKeysStop();

void runMoveToTargetFloor();


#endif
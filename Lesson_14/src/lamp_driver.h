#ifndef LAMP_DRIVER_H
#define LAMP_DRIVER_H

/*
Performs Lamp Driver Initialization
*/
void LDRV_Init(void);

/*
Switches on the Red lamp at the EW-WE direction.
Yellow and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_EwweRedLampOn(void);

/*
Switches on the Yellow lamp at the EW-WE direction.
Red and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_EwweYellowLampOn(void);

/*
Switches on the Green lamp at the EW-WE direction.
Red and Yellow lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_EwweGreenLampOn(void);

/*
Switches on the Flashing Red mode at the EW-WE direction.
Yellow and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_EwweRedLampFlashing(void);

/*
Switches on the "DON'T WALK" lamp at the EW-WE direction.
"WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_EwweDontWalkLampOn(void);

/*
Switches on the "WALK" lamp at the EW-WE direction.
"DON'T WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_EwweWalkLampOn(void);

/*
Switches on the "DON'T WALK" lamp flashing mode at the EW-WE direction.
"WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_EwweDontWalkLampFlashing(void);

/*
Switches on the Red lamp at the NS-SN direction.
Yellow and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_NssnRedLampOn(void);

/*
Switches on the Yellow lamp at the NS-SN direction.
Red and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_NssnYellowLampOn(void);

/*
Switches on the Green lamp at the NS-SN direction.
Red and Yellow lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_NssnGreenLampOn(void);

/*
Switches on the Flashing Red mode at the NS-SN direction.
Yellow and Green lamps are switched off by this function.
Pedestrian traffic light state is not changed.
*/
void LDRV_NssnRedLampFlashing(void);

/*
Switches on the "DON'T WALK" lamp at the NS-SN direction.
"WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_NssnDontWalkLampOn(void);

/*
Switches on the "WALK" lamp at the NS-SN direction.
"DON'T WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_NssnWalkLampOn(void);

/*
Switches on the "DON'T WALK" lamp flashing mode at the NS-SN direction.
"WALK" lamp is switched off by this function.
Vehicle traffic light state is not changed.
*/
void LDRV_NssnDontWalkLampFlashing(void);
#endif
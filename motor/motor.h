#ifndef _MOTOR_H
#define _MOTOR_H
#include "reg52.h"

#define CYCLE  		56320
#define MID_POINT	64154

#define SETOFFL		7
#define SETOFFR     7

/*���Ҷ���ı��*/
#define LEFT_MOTOR 	    1
#define RIGHT_MOTOR 	0

/*С�������߶���*/
#define STOP    	0
#define FORWARD 	1
#define BACKWARD 	2
#define LEFT     	3
#define RIGHT   	4
#define CCW    		5
#define CW     		6
void initMotor(void);
void shutDownMotor(void);
void motorAction(char pos,char speed);
void wheelMotorInterrupt(void);


#endif

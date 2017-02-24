#include <reg52.h>
#include "motor.h"
#include "trace.h"
#include "firesensor.h"

#define NUM 1
int angle;
bit pwmFlag=0;
sbit beep=P2^3;
sbit angleMotor=P1^2;

extern uint fireSensorAngle[5];
void delayms(uint xms)
{
 uint i,j;
 for(i=xms;i>0;i--)
 	for(j=110;j>0;j--);
}

void main(void)		
{
	//initWheelMotor();
	delayms(2);
	initAngleMotor();
	delayms(2);
	angle=fireSensorAngle[0];
	
	while(1)
	{
	 //trace();
	}
}

void Tim1forWheel(void) interrupt 3			//两个轮子
{
 	EA=0;
	wheelMotorInterrupt();
	EA=1;
}

void Tim0forAngleMotor(void) interrupt 1
{
 	
	EA=0;
	if(pwmFlag)
	{
		pwmFlag=0;
		angleMotor=1;
		TH0=(65536-(fireSensorAngle[NUM]))/256;			//高电平时间
		TL0=(65526-(fireSensorAngle[NUM]))%256;
		//angleMotorInterrupt(angle,pwmFlag);
		//beep=pwmFlag=0;
	}
	else
	{
		pwmFlag=1;
		angleMotor=0;
		TH0=(65536-(18349+fireSensorAngle[NUM]))/256; 	//低电平时间
		TL0=(65536-(18349+fireSensorAngle[NUM]))%256;
		//angleMotorInterrupt(18349-angle,pwmFlag);	 		//18349是20ms		
		//beep=pwmFlag=1;
	}
	EA=1;
}
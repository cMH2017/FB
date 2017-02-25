#include <reg52.h>
#include "motor.h"
#include "trace.h"
#include "firesensor.h"
int  angle=0;
bit  pwmFlag=0;
sbit beep=P2^3;
sbit angleMotor=P1^2;
sbit fan=P2^5;				//连接继电器的引脚，控制风扇
uchar angleMotorCount=0;

extern uint fireSensorAngle[5];
extern char fireFlag;

void delayms(uint xms)
{
 uint i,j;
 for(i=xms;i>0;i--)
 	for(j=110;j>0;j--);
}

void main(void)		
{
	initWheelMotor();
	delayms(2);
	initAngleMotor();
	delayms(2);
	while(1)
	{
		angle=checkFire();			//传回度数
		if(fireFlag<0)
		{
			fan=0;					//关闭继电器
			trace();				//如果没有火焰就循迹
		}
		else						//有火焰就灭火
		{
			delayms(10);			//防止误测
			if(fireFlag)
				fan=1;				//打开继电器	
		}
	}
}

void Tim1forWheel(void) interrupt 3				//两个轮子
{
 	EA=0;
	wheelMotorInterrupt();
	EA=1;
}

void Tim0forAngleMotor(void) interrupt 1
{
	TR0=0;
	TH0=(65536-100)/256;
	TL0=(65536-100)%256;
	if(angle>angleMotorCount)				  //18,最左，3最右
	 	 angleMotor=1; 	
	else
	 	angleMotor=0;
	angleMotorCount++;
	if(angleMotorCount>=200)
	 	angleMotorCount=0;
	TR0=1;
}
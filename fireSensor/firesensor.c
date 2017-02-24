#include <reg52.h>
#include "firesensor.h"
//sbit fireSensor[5]={1,1,1,1,1};
sfr fireSensor=0XA0;			//P2端口的地址
//从左到右 P20 P21 P22 P23 P24
sbit sersor0=P2^0;
sbit sersor1=P2^1;
sbit sersor2=P2^2;
sbit sersor3=P2^3;
sbit sersor4=P2^4;

uint fireSensorAngle[]={1706,1576,1046,881,2};

sbit angleMotor=P1^2;
uint checkFire(void)   	//返回定时器角度值
{
 	static char fire[5];
	char i;
	uint angle;
	char fs;
	fs=fireSensor;
	for(i=0;i<5;i++)
	{
	 	fire[i]|=(char)(!((fs>>i)&0X01));
		if(fire[i])
		{
			angle=fireSensorAngle[i];			
			return angle;
		}
	}
	return ANGLE_INIT;			//如果没有火焰则风扇正对中间	  
}

void initAngleMotor(void)
{
 	TMOD&=0XF0;
	TMOD|=0X01;				//定时器0 16位定时器
	TR0=1;
	ET0=1;
	EA=1;
}
//在main中写T0的中断函数 调整舵机角度 为配合风扇 设置flag

void angleMotorInterrupt(uint pwmWidth,bit pinState)
{
 	angleMotor=pinState;
	TH0=(65536-pwmWidth)/256;
	TL0=(65536-pwmWidth)%256;
}

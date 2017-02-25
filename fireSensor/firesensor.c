#include <reg52.h>
#include "firesensor.h"
#include "motor.h"
//sbit fireSensor[5]={1,1,1,1,1};
sfr fireSensor=0XA0;			//P2端口(火焰传感器)的地址
sbit angleMotor=P1^2;
//从左到右 P20 P21 P22 P23 P24
sbit sersor0=P2^0;
sbit sersor1=P2^1;
sbit sersor2=P2^2;
sbit sersor3=P2^3;
sbit sersor4=P2^4;

char fireFlag=-1;

uint fireSensorAngle[]={14,12,10,8,6};	   //数值方案暂定 	2.25 9:35


extern int angle;							//在main中定义

uint checkFire(void)   	
{
 	static char fire[5];
	char i;
	uint angle;
	char fs;
	fs=fireSensor;
	fs=~fs;									//有火焰是低电平，进行反转
	for(i=0;i<5;i++)
	{
	 	fire[i]=(char)((fs>>i)&0X01);
		if(fire[i])
		{
			angle=fireSensorAngle[i];
			fireFlag=i;						//用来设置角度舵机转动的角度
			motorAction(STOP,0);			//小车轮子别动			
			return angle;
		}
	}
	fireFlag=-1;
	return fireSensorAngle[2];				//如果没有火焰则风扇正对中间	  
}

void initAngleMotor(void)
{
 	TMOD&=0XF0;
	TMOD|=0X01;								//定时器0 16位定时器
	TR0=1;
	ET0=1;
	EA=1;
}
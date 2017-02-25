#include <reg52.h>
#include "motor.h"
#include "trace.h"
#include "firesensor.h"
int  angle=0;
bit  pwmFlag=0;
sbit beep=P2^3;
sbit angleMotor=P1^2;
sbit fan=P2^5;				//���Ӽ̵��������ţ����Ʒ���
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
		angle=checkFire();			//���ض���
		if(fireFlag<0)
		{
			fan=0;					//�رռ̵���
			trace();				//���û�л����ѭ��
		}
		else						//�л�������
		{
			delayms(10);			//��ֹ���
			if(fireFlag)
				fan=1;				//�򿪼̵���	
		}
	}
}

void Tim1forWheel(void) interrupt 3				//��������
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
	if(angle>angleMotorCount)				  //18,����3����
	 	 angleMotor=1; 	
	else
	 	angleMotor=0;
	angleMotorCount++;
	if(angleMotorCount>=200)
	 	angleMotorCount=0;
	TR0=1;
}
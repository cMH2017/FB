#include <reg52.h>
#include "firesensor.h"
#include "motor.h"
//sbit fireSensor[5]={1,1,1,1,1};
sfr fireSensor=0XA0;			//P2�˿�(���洫����)�ĵ�ַ
sbit angleMotor=P1^2;
//������ P20 P21 P22 P23 P24
sbit sersor0=P2^0;
sbit sersor1=P2^1;
sbit sersor2=P2^2;
sbit sersor3=P2^3;
sbit sersor4=P2^4;

char fireFlag=-1;

uint fireSensorAngle[]={14,12,10,8,6};	   //��ֵ�����ݶ� 	2.25 9:35


extern int angle;							//��main�ж���

uint checkFire(void)   	
{
 	static char fire[5];
	char i;
	uint angle;
	char fs;
	fs=fireSensor;
	fs=~fs;									//�л����ǵ͵�ƽ�����з�ת
	for(i=0;i<5;i++)
	{
	 	fire[i]=(char)((fs>>i)&0X01);
		if(fire[i])
		{
			angle=fireSensorAngle[i];
			fireFlag=i;						//�������ýǶȶ��ת���ĽǶ�
			motorAction(STOP,0);			//С�����ӱ�			
			return angle;
		}
	}
	fireFlag=-1;
	return fireSensorAngle[2];				//���û�л�������������м�	  
}

void initAngleMotor(void)
{
 	TMOD&=0XF0;
	TMOD|=0X01;								//��ʱ��0 16λ��ʱ��
	TR0=1;
	ET0=1;
	EA=1;
}
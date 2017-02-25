#include"motor.h"
sbit Rmotor=P1^0;
sbit Lmotor=P1^1;

uint leftPWM=MID_POINT;
uint rightPWM=MID_POINT;
uint step=25;
bit motorFlag=LEFT_MOTOR;
bit isPwmHigh=0;
bit isMotorRun=0;

void initWheelMotor(void)
{
	 TMOD&=0X0F; 		
	 TMOD|=0X10;		//16位定时器
	 TR1=1;
	 ET1=1;
	 EA=1;
	 Rmotor=0;
	 Lmotor=0;
}

void shutDownMotor(void)
{
	 leftPWM=MID_POINT;
	 rightPWM=MID_POINT;
	 isMotorRun=1;
	 while(isMotorRun);	 		//等待舵机周期完成
	 TR0=0;
	 ET0=0;
	 Rmotor=0;
	 Lmotor=0;
}

void motorAction(char pos,char speed)
{
  switch(speed)
  {
	    case 0:step=10;break;
		case 1:step=25;break;
		case 2:step=50;break;
		case 3:step=125;break;
		default:step=25;
  }
  switch(pos)
  {
	  	case STOP:		leftPWM=MID_POINT;					rightPWM=MID_POINT;break;
		case FORWARD:	leftPWM=MID_POINT-(step+SETOFFL);	rightPWM=MID_POINT+step;break;
		case BACKWARD:	leftPWM=MID_POINT+(step+2*SETOFFL);	rightPWM=MID_POINT-(step-SETOFFR);break;
		case LEFT:		leftPWM=MID_POINT;					rightPWM=MID_POINT+step;break;
		case RIGHT:		leftPWM=MID_POINT-step;				rightPWM=MID_POINT;break;
		case CCW:		leftPWM=MID_POINT+step;				rightPWM=MID_POINT+step;break;
		case CW:		leftPWM=MID_POINT-step;				rightPWM=MID_POINT-step;break;
		default:		leftPWM=MID_POINT;					rightPWM=MID_POINT;break;
  }
}

void wheelMotorInterrupt(void)
{
 if(motorFlag==LEFT_MOTOR)
 {
	   if(isPwmHigh==0)
	   {
			 Lmotor=1; 
			 isPwmHigh=1;
			 /*定时器计时x1时间*/
			 TH1=leftPWM/256;
			 TL1=leftPWM%256;
	
	   }
	   else
	   {
			 isPwmHigh=0;
			 Lmotor=0;
			 /*定时器计时y1时间*/			//x1+y1=10ms
			 TH1=(65536-leftPWM+CYCLE)/256;	//(9174-leftPWM)/256;
			 TL1=(65536-leftPWM+CYCLE)%256;	//(9174-leftPWM)%256;
			 motorFlag=RIGHT_MOTOR;
			 isMotorRun=1;
	   }
	 }
	 else
	 {
		 if(isPwmHigh==0)
		 {
			   Rmotor=1;
			   isPwmHigh=1;
			   /*定时器延时x2时间*/
			   TH1=rightPWM/256;	
			   TL1=rightPWM%256;	
		   
		 }
		 else
		 {
			   Rmotor=0;
			   isPwmHigh=0;
			   /*定时器计时y2时间*/	   			//x2+y2=10ms
			   TH1=(65536-rightPWM+CYCLE)/256;	//(9174-rightPWM)/256;
			   TL1=(65536-rightPWM+CYCLE)%256;	//(9174-rightPWM)%256;
			   motorFlag=LEFT_MOTOR;
			   isMotorRun=0;
		 }
	 }
}


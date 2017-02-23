 #include "trace.h"
sbit qtiR=P0^3;
sbit qtiMR=P0^4;
sbit qtiML=P0^5;
sbit qtiL=P0^6;
//uchar qtiVal=0X00;

//uchar readQTI(void)
//{
//  static volatile uchar atiVal=0X00;
//  atiVal|=qtiL;
//  atiVal<<=1;
//  atiVal|=qtiML;
//  atiVal<<=1;
//  atiVal|=qtiMR;
//  atiVal<<=1;
//  atiVal|=qtiR;
//  atiVal&=0X0F;
//  return atiVal;
//}

void trace(void)
{
 	if(qtiR==0&&qtiL==0)
	{
	 	if(qtiMR==qtiML)
		{
			motorAction(FORWARD,3);//直行
		}
		else if(qtiML==0&&qtiMR==1)
		{
			motorAction(RIGHT,3);//右
		}
		else
		{
			motorAction(LEFT,3);//左
		}
	}
	else
	{
	 	if(qtiR==0&qtiL==1)
		{
			motorAction(CCW,3);//逆时针
		}
		else if(qtiR==1&&qtiL==0)
		{
			 motorAction(CW,3);//顺时针
		}
		else
		{
			 motorAction(FORWARD,3);//直行
		}
	}
}

/*弃用
void trace(void)
{
 	uchar qti;
	qti=readQTI();
	switch(qti)
	{
	 	case  6:motorAction(FORWARD,3);break;//0110

		case  1://0001
		case 14:
		case  4:motorAction(LEFT,3);break;//0100

		case 12:motorAction(CCW,0);break;//1100

		case  8://1000
		case  7://0111
		case  2:motorAction(RIGHT,3);break;//0010

		case  3:motorAction(CW,0);break;//0011
		default:motorAction(FORWARD,3);break;break;//others
	}
		
}
*/

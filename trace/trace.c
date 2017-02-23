 #include "trace.h"
sbit qtiR=P0^3;
sbit qtiMR=P0^4;
sbit qtiML=P0^5;
sbit qtiL=P0^6;
void trace(void)
{
 	if(qtiR==0&&qtiL==0)
	{
	 	if(qtiMR==qtiML)
			motorAction(FORWARD,3);//直行
		else if(qtiML==0&&qtiMR==1)
			motorAction(RIGHT,3);//右
		else
			motorAction(LEFT,3);//左
	}
	else
	{
	 	if(qtiR==0&qtiL==1)
			motorAction(CCW,3);//逆时针
		else if(qtiR==1&&qtiL==0)
			motorAction(CW,3);//顺时
		else
			motorAction(FORWARD,3);//直行
	}
}



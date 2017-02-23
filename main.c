#include <reg52.h>
#include "motor.h"
#include "trace.h"

void delayms(uint xms)
{
 uint i,j;
 for(i=xms;i>0;i--)
 	for(j=11;j>0;j--);
}

void main(void)		
{
	initMotor();
	delayms(2);
	while(1)
	{
	 trace();
	}
}

void Tim1(void) interrupt 3
{
 	EA=0;
	motorInterrupt();
	EA=1;
}
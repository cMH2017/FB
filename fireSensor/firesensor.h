#ifndef _FIRESENSOR_H
#define _FIRESENSOR_H
//火焰传感器检测到火焰返回低电平
#define ANGLE_BASE 2
#define ANGLE_INIT 1046
uint checkFire(void);
void initAngleMotor(void);
void initWheelMotor(void);
void angleMotorInterrupt(uint pwmWidth,bit pinState);
#endif
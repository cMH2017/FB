#ifndef _FIRESENSOR_H
#define _FIRESENSOR_H
//���洫������⵽���淵�ص͵�ƽ,ģ���ϵ�LED����
#define ANGLE_BASE 2
#define ANGLE_INIT 1046
uint checkFire(void);
void initAngleMotor(void);
void initWheelMotor(void);
#endif
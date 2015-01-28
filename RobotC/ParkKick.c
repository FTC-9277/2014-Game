#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S2_C1_1,     fRight,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     rRight,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C2_1,     fLeft,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     rLeft,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_1,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     secondStageLift, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     lift2,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S4_C2_1,    servo1,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S4_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S4_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_6,    servo6,               tServoNone)

#include "JoystickDriver.c"

void setAllMotors(int power)
{
	motor[fRight] = power;
	motor[rRight] = power;
	motor[fLeft] = power;
	motor[rLeft] = power;
}

void turn(int leftSpeed, int rightSpeed)
{
	motor[fRight] = leftSpeed;
	motor[rRight] = leftSpeed;
	motor[fLeft] = rightSpeed;
	motor[rLeft] = rightSpeed;
}

task main()
{
	waitForStart();

	wait1Msec(25000);

	servo[servo6] = 20;
	setAllMotors(80);
	wait1Msec(2000);
	turn(40, -40);
	wait1Msec(700);
	setAllMotors(0);

	while(true)
	{
		alive();
	}
}

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

int tubeLatchRetracted = 20;
int tubeLatchActive = 120;

int rampDown = 90;
int rampUp = 0;

void setAllMotors(int power)
{
	motor[fRight] = power;
	motor[rRight] = power;
	motor[fLeft] = power;
	motor[rLeft] = power;

	if(power == 0)
	{
		wait1Msec(1000);
	}
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

	servo[servo6] = tubeLatchRetracted;

	setAllMotors(80);
	//turn(80, 75);
	wait1Msec(3000);
	setAllMotors(0);

	servo[servo6] = tubeLatchActive;

	turn(-80, 80);
	wait1Msec(1900);
	setAllMotors(0);

	setAllMotors(80);
	wait1Msec(3500);
	setAllMotors(0);

	servo[servo6] = tubeLatchRetracted;

	setAllMotors(-80);
	wait1Msec(2000);
	setAllMotors(0);

	//turn 180
	turn(80,-80);
	wait1Msec(2000);
	setAllMotors(0);

	setAllMotors(80);
	wait1Msec(1000);
	setAllMotors(0);

	//turn 45 left
	turn(-80,80);
	wait1Msec(500);
	setAllMotors(0);

	setAllMotors(80);
	wait1Msec(500);
	setAllMotors(0);

	servo[servo6] = tubeLatchActive;

	setAllMotors(-80);
	wait1Msec(1000);
	setAllMotors(0);

	//turn 90 back and left
	turn(-80,80);
	wait1Msec(1000);


	/*
	turn(80, -80);
	wait1Msec(600);
	setAllMotors(0);
 // this ^ was previously commented out

	setAllMotors(-80);
	wait1Msec(1000);
	setAllMotors(0);

	servo[servo6] = tubeLatchActive;


	//lift the lift

	servo[servo1] = liftUp; //fix
	servo[servo2] = liftUp;

	servo[servo6] = tubeLatchRetracted;

	setAllMotors(80);
	wait1Msec(750);

	motor[lift1] = 95;
	motor[lift2] = 95;
	wait1Msec(5000);
	motor[lift1] = 0;
	motor[lift2] = 0;

	setAllMotors(-80);
	wait1Msec(500);
	setAllMotors(0);
	*/

	while(true)
	{
		alive();
	}
}

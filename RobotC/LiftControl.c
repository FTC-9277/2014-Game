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

task main()
{
	while(true)
	{
		if(nNxtButtonPressed == 1)
		{
			motor[secondStageLift] = 50;
		}
		else
		{
			if(nNxtButtonPressed == 2)
			{
				motor[secondStageLift] = -50;
			}
			else
			{
				motor[secondStageLift] = 0;
			}
		}
	}
}

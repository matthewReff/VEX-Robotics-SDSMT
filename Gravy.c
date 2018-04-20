#pragma config(Sensor, in5,    SwingPot,       sensorPotentiometer)
#pragma config(Sensor, in6,    TipperPot,      sensorPotentiometer)
#pragma config(Sensor, in7,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in8,    LiftPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  RightEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftEnc,        sensorQuadEncoder)
#pragma config(Motor,  port2,           Swing,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Lift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Mogo,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LeftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LeftRearDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RightRearDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RightFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Tipper,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//PROTOTYPES
void mogoGrab();
void mogoDrop();
void drivePID(int driveDistance);
void turnLeft(int driveDistance);
void turnRight(int driveDistance);

//GLOBALS
int swingRestPos = 0;
int swingDropPos = 0;
int liftHeight = 0;
int swingHeight = 0;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task liftToHeight()
{
	int error = 0;
	error = liftHeight - SensorValue[LiftPot];
	while(true)
	{
		error = liftHeight - SensorValue[LiftPot];
		motor[Lift] = error/5;
		wait1Msec(15);

	}
}

task swingToHeight()
{
	int error = 0;
	error = swingHeight - SensorValue[LiftPot];
	while(true)
	{
		error = swingHeight - SensorValue[LiftPot];
		motor[Lift] = error/5;
		wait1Msec(15);

	}
}

//autos
task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................
	//swingHeight = 100;
	//startTask(swingToHeight);
	//int driveDistance = 250;
	//liftHeight = 2500;
	drivePID(200);
	wait1Msec(1000);
	drivePID(-200);
	wait1Msec(1000);
	drivePID(500);
	wait1Msec(1000);
	drivePID(-500);
	//mogoGrab();
	//mogoDrop();
	//startTask(liftToHeight);
	//wait1Msec(3000);
	//liftHeight = 4000;
	//wait1Msec(3000);
	//liftHeight = 2000;
	//wait1Msec(2000);
	//startTask(mogoDrop)
	//wait1Msec(400)
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void mogoGrab()
{
	//3600 bottom
	//950 top

	while(SensorValue[MogoPot] < 3600)
	{
		motor[Mogo] = 127;
	}

	drivePID(100);
	//add timers
	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	while(SensorValue[MogoPot] > 950)
	{
		motor[Mogo] = -127;
	}
}

void mogoDrop()
{
	while(SensorValue[MogoPot] > 950)
	{
		motor[Mogo] = -127;
	}

	drivePID(-100);
	//add timers
	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	while(SensorValue[MogoPot] > 3600)
	{
		motor[Mogo] = -127;
	}
}

void turnLeft(int driveDistance)
{
	int error = 0;
	int speed = 0;
	SensorValue[LeftEnc] = 0;
	while(SensorValue[LeftEnc] < driveDistance)
	{
		error = driveDistance - SensorValue[LeftEnc];
		if(error > 250)
		{
			speed = error/2;
			motor[LeftFrontDrive] = speed;
			motor[LeftRearDrive] = speed;
			motor[RightFrontDrive] = -speed;
			motor[RightRearDrive] = -speed;
		}
		else
		{
			motor[LeftFrontDrive] = 100;
			motor[LeftRearDrive] = 100;
			motor[RightFrontDrive] = -100;
			motor[RightRearDrive] = -100;
		}
	}
	motor[LeftFrontDrive] = -25;
	motor[LeftRearDrive] = -25;
	motor[RightFrontDrive] = 25;
	motor[RightRearDrive] = 25;

	wait1Msec(200);

	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	wait1Msec(200);
}

void turnRight(int driveDistance)

{
	int error = 0;
	int speed = 0;
	SensorValue[RightEnc] = 0;
	while(SensorValue[RightEnc] < driveDistance)
	{
		error = driveDistance - SensorValue[RightEnc];
		if(error > 250)
		{
			speed = error/2;
			motor[LeftFrontDrive] = -speed;
			motor[LeftRearDrive] = -speed;
			motor[RightFrontDrive] = speed;
			motor[RightRearDrive] = speed;
		}
		else
		{
			motor[LeftFrontDrive] = -100;
			motor[LeftRearDrive] = -100;
			motor[RightFrontDrive] = 100;
			motor[RightRearDrive] = 100;
		}
	}
	motor[LeftFrontDrive] = 25;
	motor[LeftRearDrive] = 25;
	motor[RightFrontDrive] = -25;
	motor[RightRearDrive] = -25;

	wait1Msec(200);

	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	wait1Msec(200);
}

void drivePID(int driveDistance)
{
	int errorRight = 0;
	int prevErrorRight = 0;
	int errorLeft = 0;
	int prevErrorLeft = 0;
	int integralRight = 0;
	int integralLeft = 0;
	int derivativeRight = 0;
	int derivativeLeft = 0;
	int speedRight;
	int speedLeft;
	float kP = .9;
	float kI = .00001;
	float kD = .005;

	//values for turn
	/*float kP = .1;
	float kI = .0003;
	float kD = .005;
	*/
	SensorValue[LeftEnc] = 0;
	SensorValue[RightEnc] = 0;


	errorRight = driveDistance - SensorValue[RightEnc];
	prevErrorRight = driveDistance - SensorValue[RightEnc];
	errorLeft = driveDistance - SensorValue[LeftEnc];
	prevErrorLeft = driveDistance - SensorValue[LeftEnc];

	while ( abs(errorRight) > 10 && abs(errorLeft) > 10 )
	{
		errorLeft = driveDistance - SensorValue[LeftEnc];
		errorRight = driveDistance - SensorValue[RightEnc];
		integralRight = integralRight + errorRight;
		integralLeft = integralLeft + errorLeft;
		if (errorLeft == 0 || errorRight == 0)
		{
			integralRight = 0;
			integralLeft = 0;
		}
		derivativeRight = errorRight - prevErrorRight;
		prevErrorRight = errorRight;
		derivativeLeft = errorLeft - prevErrorLeft;
		prevErrorLeft = errorLeft;

		speedRight = errorRight*kP + integralRight*kI + derivativeRight*kD;
		speedLeft = errorLeft * kP + integralLeft*kI + derivativeLeft*kD;
		motor[LeftFrontDrive] = speedLeft;
		motor[RightFrontDrive] = speedRight;
		motor[LeftRearDrive] = speedLeft;
		motor[RightRearDrive] = speedRight;

		wait1Msec(15);
	}

	//run in reverse for a bit to make sure movement
	//is stopped
	/*
	motor[LeftFrontDrive] = -25;
	motor[RightFrontDrive] = -25;
	motor[LeftRearDrive] = -25;
	motor[RightRearDrive] = -25;
	wait1Msec(400);
	*/


	//kill motors
	motor[LeftFrontDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightRearDrive] = 0;
	wait1Msec(500);
	return;
}

task usercontrol()
{

	// User control code here, inside the loop
	int y;
	int x;
	int threshhigh = 100;
	int threshlow = 20;

	while (true)
	{

		if(abs(vexRT[Ch3]) >= threshhigh)
		{
			y = vexRT[Ch3] * .8;
		}
		else if(abs(vexRT[Ch3]) <= threshlow)
		{
			y = 0;
		}
		else
		{
			y = vexRT[Ch3];
		}

		if(abs(vexRT[Ch1]) >= threshhigh)
		{
			x = vexRT[Ch1] * .8;
		}
		else if(abs(vexRT[Ch1]) <= threshlow)
		{
			x = 0;
		}
		else
		{
			x = vexRT[Ch1];
		}

		motor[LeftFrontDrive] = x + y;
		motor[RightFrontDrive] = -x + y;
		motor[LeftRearDrive] = x + y;
		motor[RightRearDrive] = -x + y;

		if(vexRT[Btn6U] == 1)
		{
			motor[Lift] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[Lift] = -127;
		}
		else
		{
			motor[Lift] = 0;
		}

		if(vexRT[Btn5U] == 1)
		{
			motor[Swing] = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[Swing] = -127;
		}
		else
		{
			motor[Swing] = 0;
		}

		if(vexRT[Btn8U] == 1)
		{
			motor[Mogo] = 127;
		}
		else if(vexRT[Btn8D] == 1)
		{
			motor[Mogo] = -127;
		}
		else
		{
			motor[Mogo] = 0;
		}
		wait1Msec(15);
	}
}

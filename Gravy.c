#pragma config(Sensor, in6,    SwingPot,       sensorPotentiometer)
#pragma config(Sensor, in7,    GyroSensor,     sensorGyro)
#pragma config(Sensor, in8,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LeftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RightEnc,       sensorQuadEncoder)
#pragma config(Motor,  port2,           LeftFrontDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RightFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LeftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Roller,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Mogo,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftRearDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RightRearDrive, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//PROTOTYPES
void autoStack();
void drivePID(int driveDistance);
void turnLeft(int driveDistance);
void turnRight(int driveDistance);
void displayAuton();


//GLOBALS
int auton;
int numAutons = 4;

task mogoDown()
{
	motor[Mogo] = 0;
	wait1Msec(20);
	while(SensorValue[MogoPot] < 3500)
	{
		motor[Mogo] = -127;
		wait1Msec(20);
		hogCPU();
	}
	releaseCPU();
	motor[Mogo] = -20;
	wait1Msec(20);
	stopTask(mogoDown);
}

task mogoUp()
{
	motor[Mogo] = 0;
	wait1Msec(20);

	while(SensorValue[MogoPot] > 880)
	{
		motor[Mogo] = 127;
		wait1Msec(20);
	}
	motor[Mogo] = 0;
	wait1Msec(20);
	stopTask(mogoUp);
}

task LCDControl()
{
	clearLCDLine(0);
	clearLCDLine(1);
	bool noButtonsPressed = true;
	displayAuton();
	while(true){
		if(noButtonsPressed){ // only update auton if a button is pressed AND wasn't pressed previously
			switch(nLCDButtons){
			case kButtonLeft:
				auton--;
				if (auton < 0)
					auton = 0;
				displayAuton();
				break;
			case kButtonCenter:
				stopTask(LCDControl);
				break;
			case kButtonRight:
				auton++;
				if(auton > numAutons)
					auton = numAutons;
				displayAuton();
				break;
			}
		}
		noButtonsPressed = !nLCDButtons; //update if there is a button currently pressed
		wait1Msec(20);
	}
}

void displayAuton()
{
	switch(auton)
	{
	case 1:
		displayLCDCenteredString(0, "Hunter");
		break;

	case 2:
		displayLCDCenteredString(0, "Matt");
		break;

	case 0:
		displayLCDCenteredString(0, "?");
		break;

	case 3:
		displayLCDCenteredString(0, "Aldo");
		break;

	default:
		displayLCDCenteredString(0, "No auton");
		break;
	}
}

void pre_auton()
{
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in7] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in7] = sensorGyro;
	wait1Msec(2000);
	bLCDBacklight = true;

	clearLCDLine(0);
	clearLCDLine(1);
	bDisplayCompetitionStatusOnLcd = false;
	startTask(LCDControl);

	bStopTasksBetweenModes = true;
}

task autonomous()
{
	//ill advised distance constants
	int driveReverse17 = 0;
	int driveForward17 = 0;
	int driveReverse24 = 0;
	int driveForward24 = 0;
	int driveReverse34 = 0;
	int driveForward34 = 0;
	int driveReverse48 = 0;
	int driveForward48 = 0;
	int driveReverse72 = 0;
	int driveForward72 = 0;
	int turnLeft45 = 0;
	int turnRight45 = 0;
	int turnLeft90 = 0;
	int turnRight90 = 0;
	int turnLeft135 = 0;
	int turnRight135 = 0;


	clearLCDLine(0);
	clearLCDLine(1);
	stopTask(LCDControl);
	switch(auton){
	case 1:
		motor[LeftLift] = -30;
		motor[RightLift] = -30;
		//drop onto stationary goal
		drivePID(-330);
		motor[LeftLift] = 10;
		motor[RightLift] = 10;
		wait1Msec(200);
		drivePID(182);

		motor[RightLift] = 0;
		motor[LeftLift] = 0;

		//go to the left mobile goal
		// turn right
		turnRight(175);

		//drive forward
		drivePID(738);

		//turn right
		turnRight(58);

		//mogo out
		startTask(mogoDown);
		wait1Msec(800);

		//drive forward
		drivePID(951);

		//mogo in
		stopTask(mogoDown);
		startTask(mogoUp);
		wait1Msec(1000);
		stopTask(mogoUp);

		//drive back
		drivePID(-262);

		//turn right
		turnRight(128);

		//back up
		motor[LeftFrontDrive] = -30;
		motor[LeftRearDrive] = -30;
		motor[RightFrontDrive] = -30;
		motor[RightRearDrive] = -30;
		wait1Msec(1000);

		//autostack onto left mobile goal
		//autoStack();

		//place left mobile goal on far scoring goal
		//go straight
		drivePID(325);

		//turn right
		turnRight(145);

		//drive straight
		drivePID(791);

		//turn right
		turnRight(52);

		//drive straight
		drivePID(276);

		//mogo down
		//stopTask(mogoUp);
		startTask(mogoDown);
		wait1Msec(1000);
		stopTask(mogoDown);

		//dive backwards
		drivePID(-342);

		//mogo up
		stopTask(mogoDown);
		startTask(mogoUp);
		wait1Msec(1000);
		stopTask(mogoUp);

		//turn right
		turnRight(102);

		//drive forward
		drivePID(390);

		//go get right mobile goal
		//turn to wall
		drivePID(-42);
		turnLeft(38);

		//drive forward to wall
		drivePID(95);

		//turn left to face mogo
		startTask(mogoDown);
		turnLeft(38);

		//lower mogo lift and run into mogo
		drivePID(170);

		//drive back toward goal
		stopTask(mogoDown);
		startTask(mogoUp);
		wait1Msec(300);
		drivePID(-170);

		//go to scoring platform
		//turn to other wall
		turnLeft(76);

		//drive to wall
		drivePID(150);

		//drive toward loader
		turnRight(32);

		//drive forward to loader
		drivePID(40);

		//turn right
		turnRight(38);

		//back into loader
		motor[LeftFrontDrive] = -30;
		motor[LeftRearDrive] = -30;
		motor[RightFrontDrive] = -30;
		motor[RightRearDrive] = -30;
		wait1Msec(1000);

		//autostack onto right mobile goal
		//autoStack();

		//go straight to place right mobile goal onto right side of second score
		drivePID(70);

		//turn right
		turnRight(50);

		//drive straight
		drivePID(174);

		//turn right
		turnRight(50);

		//mogo out
		startTask(mogoDown);

		//back up to drop off mogo
		drivePID(-40);

		//put mogo back up
		stopTask(mogoDown);
		startTask(mogoUp);
		wait1Msec(300);
		break;

	case 0:
		//go right auton
		//drop on stationary goal
		/*
		drivePID(-80);
		drivePID(80);
		motor[LeftFrontDrive] = 20;
		motor[LeftRearDrive] = 20;
		motor[RightFrontDrive] = 20;
		motor[RightRearDrive] = 20;
		wait1Msec(500);
		*/
		//go get right mobile goal
		//turn to wall
		drivePID(-125);
		//turnRight(150);
		turnLeft(275);

		//drive forward to wall
		drivePID(1475);

		//turn left to face mogo
		startTask(mogoDown);
		turnLeft(25);

		//lower mogo lift and run into mogo
		drivePID(1075);

		//drive back toward goal
		stopTask(mogoDown);
		startTask(mogoUp);
		wait1Msec(1100);
		drivePID(-1075);

		//go to score on right mobile goal
		//turn to other wall1
		//turnRight(70);
		turnLeft(350);
		drivePID(250);
		turnLeft(60);
		drivePID(100);
		stopTask(mogoUp);
		startTask(mogoDown);
		//drive to wall
		//drivePID(100);
		wait1Msec(1000);
		//drive toward loader
		//turnRight(38);

		//drive forward to loader
		//drivePID(40);

		//turn right
		//turnRight(38);

		//back into loader
		motor[LeftFrontDrive] = -60;
		motor[LeftRearDrive] = -60;
		motor[RightFrontDrive] = -60;
		wait1Msec(1000);

		stopTask(mogoDown);
		startTask(mogoUp);

		wait1Msec(3000);

		motor[LeftFrontDrive] = 0;
		motor[LeftRearDrive] = 0;
		motor[RightFrontDrive] = 0;
		motor[RightRearDrive] = 0;
		break;

	case 2:

		break;

	case 3:
		break;

	default:

		break;
	}

}

void autoStack()
{
	int grabHeight = 3800;
	int armDrop[5] = {250, 500, 550, 1000, 1300};


	//hug wall while stacking to preventing rocking
	motor[LeftFrontDrive] = -10;
	motor[LeftRearDrive] = -10;
	motor[RightFrontDrive] = -10;
	motor[RightRearDrive] = -10;


	for(int i = 0; i < 5; i++)
	{
/*
		while(SensorValue[SwingPot] < 2000 && vexRT[Btn6D] != 1)
		{
			motor[Roller] = -127;
			motor[LeftLift] = 127;
			motor[RightLift] = 127;
			wait1Msec(20);
		}
		*/
		//drop Roller down to grab height to grab cone
		while(SensorValue[SwingPot] < grabHeight && vexRT[Btn6D] != 1)
		{
			motor[Roller] = 127;
			motor[LeftLift] = 127;
			motor[RightLift] = 127;
			wait1Msec(20);
		}

		//Roller back over to arm drop height
		//slow down roller at certain height to 60
		while(SensorValue[SwingPot] > armDrop[i] && vexRT[Btn6D] != 1)
		{

			//right side determines drop height
			if(SensorValue[SwingPot] > armDrop[i] + 500)
			{
				motor[Roller] = 30;
				motor[LeftLift] = -127;
				motor[RightLift] = -127;
				wait1Msec(20);
			}
			else
			{
				//release cone
				motor[Roller] = -127;
			}
		}

		//kill switch
		if(vexRT[Btn6D] == 1)
		{
			i = 6;
		}
	}
}


void turnRight(int driveDistance)
{
	int error = 0;
	int speed = 0;
	SensorValue[GyroSensor] = 0;
	wait1Msec(200);
	clearTimer(T2);
	clearTimer(T3);


	while(abs(SensorValue[GyroSensor]) < driveDistance && time1[T2] < 2000)
	{
		error = driveDistance + SensorValue[GyroSensor];
		if(error > 350)
		{
			speed = error/2;
			if(speed > 500)
			{
				speed = 500;
			}
			motor[LeftFrontDrive] = speed / 3;
			motor[LeftRearDrive] = speed / 3;
			motor[RightFrontDrive] = -speed / 3;
			motor[RightRearDrive] = -speed / 3;
		}
		else if(abs(error) < 200)
		{
			motor[LeftFrontDrive] = 20;
			motor[LeftRearDrive] = 20;
			motor[RightFrontDrive] = -20;
			motor[RightRearDrive] = -20;
		}
		else
		{
			motor[LeftFrontDrive] = 40;
			motor[LeftRearDrive] = 40;
			motor[RightFrontDrive] = -40;
			motor[RightRearDrive] = -40;
		}
	}



	if(driveDistance > 1000)
	{
		motor[LeftFrontDrive] = -30;
		motor[LeftRearDrive] = -30;
		motor[RightFrontDrive] = 30;
		motor[RightRearDrive] = 30;
	}
	else if(driveDistance > 600)
	{
		motor[LeftFrontDrive] = -25;
		motor[LeftRearDrive] = -25;
		motor[RightFrontDrive] = 25;
		motor[RightRearDrive] = 25;
	}
	else if (driveDistance < 300)
	{
		motor[LeftFrontDrive] = -15;
		motor[LeftRearDrive] = -15;
		motor[RightFrontDrive] = 15;
		motor[RightRearDrive] = 15;
	}
	else
	{
		motor[LeftFrontDrive] = -20;
		motor[LeftRearDrive] = -20;
		motor[RightFrontDrive] = 20;
		motor[RightRearDrive] = 20;
	}
	wait1Msec(150);
	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;


}

void turnLeft(int driveDistance)

{
	int error = 0;
	float kG = .5;
	SensorValue[GyroSensor] = 0;
	wait1Msec(200);
	clearTimer(T2);
	clearTimer(T3);

	while(abs(SensorValue[GyroSensor]) < driveDistance && time1[T2] < 2000)
	{
		error = driveDistance - SensorValue[GyroSensor];
		motor[LeftFrontDrive] = -error * kG;
		motor[LeftRearDrive] = -error * kG;
		motor[RightFrontDrive] = error * kG;
		motor[RightRearDrive] = error * kG;
		wait1Msec(20);

	}

	if(driveDistance > 1000)
	{
		motor[LeftFrontDrive] = 30;
		motor[LeftRearDrive] = 30;
		motor[RightFrontDrive] = -30;
		motor[RightRearDrive] = -30;
	}
	else if(driveDistance > 600)
	{
		motor[LeftFrontDrive] = 25;
		motor[LeftRearDrive] = 25;
		motor[RightFrontDrive] = -25;
		motor[RightRearDrive] = -25;
	}
	else if (driveDistance < 300)
	{
		motor[LeftFrontDrive] = 15;
		motor[LeftRearDrive] = 15;
		motor[RightFrontDrive] = -15;
		motor[RightRearDrive] = -15;
	}
	else
	{
		motor[LeftFrontDrive] = 20;
		motor[LeftRearDrive] = 20;
		motor[RightFrontDrive] = -20;
		motor[RightRearDrive] = -20;
	}
	wait1Msec(150);

	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	wait1Msec(200);
}

void drivePID(int driveDistance)
{
	int maxDriveTime = 2000;
	int errorRight = 0;
	int prevErrorRight = 0;
	int integralRight = 0;
	int derivativeRight = 0;
	int speedRight;
	/*	int initialTime = 0;
	int initialEncRight = 0;
	int intitialEncLeft = 0;
	int velocityLeft = 0;
	int velocityRight = 0;
	*/
	//PID constants
	float kP = .9;
	float kI = .00001;
	float kD = .005;
	float kG = 1.5;

	//reset all values
	SensorValue[LeftEnc] = 0;
	SensorValue[RightEnc] = 0;
	SensorValue[GyroSensor] = 0;
	wait1Msec(200);
	clearTimer(T1);
	clearTimer(T3);

	errorRight = driveDistance - SensorValue[RightEnc];
	prevErrorRight = driveDistance - SensorValue[RightEnc];

	while ( abs(SensorValue[RightEnc]) < driveDistance && time1(T1) < maxDriveTime)
	{


		errorRight = driveDistance - SensorValue[RightEnc];
		integralRight = integralRight + errorRight;
		if (errorRight == 0)
		{
			integralRight = 0;
		}
		derivativeRight = errorRight - prevErrorRight;
		prevErrorRight = errorRight;

		speedRight = errorRight*kP + integralRight*kI + derivativeRight*kD;

		speedRight = speedRight /10;


		if(abs(speedRight) < 30 && speedRight < 0)
		{
			speedRight = -30;
		}
		else if(abs(speedRight) < 30 && speedRight > 0)
		{
			speedRight = 30;
		}

		if(abs(SensorValue[RightEnc]) < 200)
		{
			if(driveDistance < 0)
			{
				speedRight= -126;
			}
			else
			{
				speedRight = 126;
			}
		}

		if(abs(SensorValue[RightEnc]) < errorRight / 4.0)
		{
			if(driveDistance < 0)
			{
				speedRight= -50;
			}
			else
			{
				speedRight = 50;
			}
			//velocityLeft = (SensorValue[LeftEnc] - intitialEncLeft) / (time1(T3) - initialTime);
			//velocityRight = (SensorValue[RightEnc] - initialEncRight) / (time1(T3) - initialTime);
		}


		motor[LeftFrontDrive] = speedRight + SensorValue[GyroSensor] * kG;
		motor[RightFrontDrive] = speedRight - SensorValue[GyroSensor] * kG;
		motor[LeftRearDrive] = speedRight + SensorValue[GyroSensor] * kG;
		motor[RightRearDrive] = speedRight - SensorValue[GyroSensor] * kG;

		wait1Msec(15);
	}

	if(driveDistance > 600)
	{
		motor[LeftFrontDrive] = -30;
		motor[LeftRearDrive] = -30;
		motor[RightFrontDrive] = -30;
		motor[RightRearDrive] = -30;
	}
	else if(driveDistance > 400)
	{
		motor[LeftFrontDrive] = -25;
		motor[LeftRearDrive] = -25;
		motor[RightFrontDrive] = -25;
		motor[RightRearDrive] = -25;
	}
	else if (driveDistance < 200)
	{
		motor[LeftFrontDrive] = -15;
		motor[LeftRearDrive] = -15;
		motor[RightFrontDrive] = -15;
		motor[RightRearDrive] = -15;
	}
	else
	{
		motor[LeftFrontDrive] = -20;
		motor[LeftRearDrive] = -20;
		motor[RightFrontDrive] = -20;
		motor[RightRearDrive] = -20;
	}
	wait1Msec(200);

	//kill motors
	motor[LeftFrontDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightRearDrive] = 0;
	wait1Msec(500);
	return;
}

void driveP(int driveDistance)
{
	int speed = 0;
	int error = 0;
	float kS = .3;
	float kG = 1;
	SensorValue[GyroSensor] = 0;
	SensorValue[LeftEnc] = 0;
	wait1Msec(200);
	clearTimer(T2);

	error = driveDistance - SensorValue[LeftEnc];
	while(error > 0 && time1[T2] < 4000)
	{
		error = driveDistance - SensorValue[LeftEnc];
		if(SensorValue[LeftEnc] < driveDistance/ 6)
		{
			speed = 150;
		}
		else if(error < driveDistance / 3 * 2)
		{
			speed = 100;
		}
		else
		{
			speed = error;
		}
		motor[LeftFrontDrive] = speed * kS + SensorValue[GyroSensor] * kG;
		motor[LeftRearDrive] = speed * kS + SensorValue[GyroSensor] * kG;
		motor[RightFrontDrive] = speed * kS - SensorValue[GyroSensor] * kG;
		motor[RightRearDrive] = speed * kS - SensorValue[GyroSensor] * kG;
	}

	if(driveDistance > 1000)
	{
		motor[LeftFrontDrive] = -50;
		motor[LeftRearDrive] = -50;
		motor[RightFrontDrive] = -50;
		motor[RightRearDrive] = -50;
	}
	else if(driveDistance > 600)
	{
		motor[LeftFrontDrive] = -30;
		motor[LeftRearDrive] = -30;
		motor[RightFrontDrive] = -30;
		motor[RightRearDrive] = -30;
	}
	else if (driveDistance < 300)
	{
		motor[LeftFrontDrive] = -25;
		motor[LeftRearDrive] = -25;
		motor[RightFrontDrive] = -25;
		motor[RightRearDrive] = -25;
	}
	else
	{
		motor[LeftFrontDrive] = -25;
		motor[LeftRearDrive] = -25;
		motor[RightFrontDrive] = -25;
		motor[RightRearDrive] = -25;
	}
	wait1Msec(200);

	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	wait1Msec(200);
}

void driveReverseP(int driveDistance)
{
	int speed = 0;
	int error = 0;
	float kS = .3;
	float kG = .5;
	SensorValue[GyroSensor] = 0;
	SensorValue[LeftEnc] = 0;
	wait1Msec(200);
	clearTimer(T2);

	error = driveDistance + SensorValue[LeftEnc];
	while(error > 0 && time1[T2] < 4000)
	{
		error = driveDistance + SensorValue[LeftEnc];
		//if in the first fraction
		if(abs(SensorValue[LeftEnc]) < driveDistance/ 6)
		{
			speed = -150;
		}
		//else in the last fraction of drive
		else if(error < driveDistance / 3 * 2)
		{
			speed = -75;
		}
		else
		{
			speed = -error;
		}
		motor[LeftFrontDrive] = speed * kS + SensorValue[GyroSensor] * kG;
		motor[LeftRearDrive] = speed * kS + SensorValue[GyroSensor] * kG;
		motor[RightFrontDrive] = speed * kS - SensorValue[GyroSensor] * kG;
		motor[RightRearDrive] = speed * kS - SensorValue[GyroSensor] * kG;
	}

	if(driveDistance > 1000)
	{
		motor[LeftFrontDrive] = 20;
		motor[LeftRearDrive] = 20;
		motor[RightFrontDrive] = 20;
		motor[RightRearDrive] = 20;
	}
	else if(driveDistance > 600)
	{
		motor[LeftFrontDrive] = 30;
		motor[LeftRearDrive] = 30;
		motor[RightFrontDrive] = 30;
		motor[RightRearDrive] = 30;
	}
	else if (driveDistance < 300)
	{
		motor[LeftFrontDrive] = 10;
		motor[LeftRearDrive] = 10;
		motor[RightFrontDrive] = 10;
		motor[RightRearDrive] = 10;
	}
	else
	{
		motor[LeftFrontDrive] = 12;
		motor[LeftRearDrive] = 12;
		motor[RightFrontDrive] = 12;
		motor[RightRearDrive] = 12;
	}
	wait1Msec(200);

	motor[LeftFrontDrive] = 0;
	motor[LeftRearDrive] = 0;
	motor[RightFrontDrive] = 0;
	motor[RightRearDrive] = 0;

	wait1Msec(200);
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

task usercontrol()
{
	// User control code here, inside the loop
	clearLCDLine(0);
	clearLCDLine(1);
	stopTask(LCDControl);
	int y;
	int x;
	int threshhigh = 100;
	int threshlow = 20;

	while (true)
	{
		motor[Roller] = 0;
		motor[LeftLift] = 0;
		motor[RightLift] = 0;
		// make joystick move far enough before using values
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
		// make joystick move far enough before using values
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


		if(vexRT[Btn5U] == 1)
		{
			/*
			motor[LeftFrontDrive] = x/3 + y/2.5;
			motor[RightFrontDrive] = -x/3 + y/2.5;
			motor[LeftRearDrive] = x/3 + y/2.5;
			motor[RightRearDrive] = -x/3 + y/2.5;
			*/
			motor[LeftFrontDrive] = x + y;
			motor[RightFrontDrive] = -x + y;
			motor[LeftRearDrive] = x + y;
			motor[RightRearDrive] = -x + y;
		}
		else
		{
			/*
			motor[LeftFrontDrive] = x + y;
			motor[RightFrontDrive] = -x + y;
			motor[LeftRearDrive] = x + y;
			motor[RightRearDrive] = -x + y;
			*/
			motor[LeftFrontDrive] = x / 1.5 + y / 1.5;
			motor[RightFrontDrive] = -x / 1.5 + y / 1.5;
			motor[LeftRearDrive] = x / 1.5 + y / 1.5;
			motor[RightRearDrive] = -x / 1.5 + y / 1.5;
		}
		/*
		speed = 2600 - SensorValue[SwingPot];
		motor[LeftLift] = speed * 0.05;
		motor[RightLift] = speed * 0.05;
		motor[Roller] = -40;
		*/


		if(vexRT[Btn8U] == 1)
		{
			stopTask(mogoUp);
			startTask(mogoDown);
		}
		else if(vexRT[Btn8D] == 1)
		{
			stopTask(mogoDown);
			startTask(mogoUp);
		}

		if(vexRT[Btn6U] == 1)
		{
			autoStack();
		}
		if(vexRT[Btn7R] == 1)
		{
			driveReverseP(400);
		}
		if(vexRT[Btn7L] == 1)
		{
			turnLeft(500);
			wait1Msec(1000);
			turnRight(500);
			wait1Msec(1000);
			turnLeft(1050);
			wait1Msec(1000);
			turnRight(1050);
			wait1Msec(1000);

		}
		if(vexRT[Btn7D] == 1)
		{
			drivePID(200);
			wait1Msec(100);
			drivePID(400);
			wait1Msec(100);
			drivePID(400);
		}
		wait1Msec(20);
	}
}

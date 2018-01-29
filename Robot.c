\#pragma config(Sensor, in1,    LeftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    RightPot,       sensorPotentiometer)
#pragma config(Sensor, in3,    SwingPot,       sensorPotentiometer)
#pragma config(Motor,  port1,           mogo1,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LeftOutsideD,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           LeftInsideD,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           RightInsideD,  tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           RightOutsideD, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           LeftLift,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           RightLift,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           Swing,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          mogo2,         tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// init numCons to 1 and stacking to false so robot doesnt try to autostack
int numCones = 1;
bool stacking = false;

/*/////////////////////////////////////////////////////////////
pre autonomous task
reset sensor values/initializations here
*//////////////////////////////////////////////////////////////
void pre_auton()
{
	bStopTasksBetweenModes = true;
}

/*/////////////////////////////////////////////////////////////
autonomous mode task
code here runs during the autonomous period of the match
*//////////////////////////////////////////////////////////////
task autonomous()
{
	numCones = 1;
}

/*/////////////////////////////////////////////////////////////
auto stacking task
this code relies on the press of a button and the current number
of cones stacked on the mobile goal. pressing button 5U executes 
the whole code.
*//////////////////////////////////////////////////////////////
task autostack()
{
	// establish heights for the lift and the swinging arm positions
	int coneHeight[12] = { 70, 100, 250, 400, 550, 700, 850, 1000, 1150, 1300, 1450, 1600 };
	int SwingHigh = 4000;
	int SwingMid = 2000;
	int CurrentL;
	int CurrentS;

	// runs until lift reaches target and swing arm reaches top position
	while(SensorValue[LeftPot] < coneHeight[numCones] -50 || SensorValue[LeftPot] > coneHeight[numCones] + 50  || CurrentS < SwingHigh)
	{
		
		CurrentL = SensorValue[LeftPot];
		CurrentS = SensorValue[SwingPot];
		wait1Msec(20);

		// if lift height is below target lift up higher
		if(SensorValue[LeftPot] < coneHeight[numCones])
		{
			motor[LeftLift] = (coneHeight[numCones] - CurrentL)*10 ;
			motor[RightLift] = (coneHeight[numCones] - CurrentL)*10 ;
			wait1Msec(20);
		}
		// if lift height is above target lift down lower
		else if(SensorValue[LeftPot] > coneHeight[numCones])
		{
			motor[LeftLift] = -(coneHeight[numCones] - CurrentL)*10 ;
			motor[RightLift] = -(coneHeight[numCones] - CurrentL)*10 ;
			wait1Msec(20);
		}
		
		// if height is not close enough to the target hen hold mid position
		if(CurrentL - coneHeight[numCones] < 300)
		{
			// if swing arm is below mid position swing up higher
			if(CurrentS < SwingMid)
			{
				motor[Swing] = abs(SwingMid - CurrentS) / 10;
				wait1Msec(20);
			}
			
			// if swing arm is above mid position swing down lower
			else	if(CurrentS > SwingMid)
			{
				motor[Swing] = -1 * abs(SwingMid - CurrentS) / 10;
				wait1Msec(20);
			}

		}
		else
		{
			// if swing arm is not at high position lift up
			if(CurrentS < SwingHigh)
			{
				motor[Swing] = abs(SwingHigh - CurrentS) / 10;
				wait1Msec(20);
			}
			
			// hold the up position
			else
			{
				motor[Swing] = 20;
				wait1Msec(20);
			}
		}
	}
	motor[LeftLift] = -10;
	motor[RightLift] = -10;
	motor[Swing] = -10;
	wait1Msec(100);


	// start lifting down
	motor[LeftLift] = -127;
	motor[RightLift] = -127;
	wait1Msec(200);

	// add one to numCones to signify it was stacked
	++numCones;
	stacking = false;
	wait1Msec(20);

	// end task
	stopTask(autostack);
}

/*/////////////////////////////////////////////////////////////
Driver control task
code here runs during the driver period of the match
*//////////////////////////////////////////////////////////////
task usercontrol()
{
	
	int x;
	int y;
	int CurrentS;
	int CurrentL;
	
	// set lift and swing heights
	int LiftLow = 70;
	int SwingMid = 2000;
	int thresh = 10;
	stacking = false;
	numCones = 1;

	// big ole while loop
	while (true)
	{
		// constantly set current swing and lift heights
		CurrentS = SensorValue[SwingPot];
		CurrentL = SensorValue[LeftPot];

		// make joystick move far enough before using values
		if(abs(vexRT[Ch3]) >= thresh)
		{
			y = vexRT[Ch3];
		}
		else
		{
			y = 0;
		}
		// make joystick move far enough before using values
		if(abs(vexRT[Ch2]) >= thresh)
		{
			x = vexRT[Ch1];
		}
		else
		{
			x = 0;
		}

		// set motor values for arcade drive
		motor[LeftInsideD] = y + x;
		motor[LeftOutsideD] = y + x;
		motor[RightInsideD] = y - x;
		motor[RightOutsideD] = y - x;

		// mobile goal lift up 
		if(vexRT[Btn8U] == 1)
		{
			motor[mogo1] = 127;
			motor[mogo2] = 127;
		}
		
		// mobile goal lift down and reset number of cones on drop off
		else if(vexRT[Btn8D] == 1)
		{
			motor[mogo1] = -127;
			motor[mogo2] = -127;
			numCones = 1;
		}
		
		// subtract one cone from total
		else if(vexRT[Btn8R] == 1)
		{
			--numCones;
		}
		
		// stop
		else
		{
			motor[mogo1] = 0;
			motor[mogo2] = 0;
		}

		// run auto stack code
		//*
		if(vexRT[Btn5U] == 1)
		{
			stacking = true;
			startTask(autostack);
		}
		//*/

		/*
		if(vexRT[Btn5U] == 1)
		{
		motor[Swing] = 127;
		}
		//*/

		// if not running auto stack code
		else if(stacking == 0)
		{
			// swing arm down
			if(vexRT[Btn5D] == 1)
			{
				motor[Swing] = -127;
			}

			// maintain mid position
			else
			{
				// when below target position swing up
				if(CurrentS < SwingMid)
				{
					motor[Swing] = abs(SwingMid - CurrentS) / 10;
				}
				// when above target position swing down
				else	if(CurrentS > SwingMid)
				{
					motor[Swing] = -1 * abs(SwingMid - CurrentS) / 10;
				}
			}
		}
		
		// when not auto stacking 
		else if (stacking == 0)
		{
			// lift up
			if(vexRT[Btn6U] == 1 )
			{
				motor[LeftLift] = 127;
				motor[RightLift] = 127;
			}
			// lift down
			else if(vexRT[Btn6D] == 1)
			{
				motor[LeftLift] = -127;
				motor[RightLift] = -127;
			}
			else
			{
				// when below low position hold down
				if(abs(CurrentL - LiftLow) < 200)
				{
					motor[LeftLift] = -20;
					motor[RightLift] = -20;
				}
				// otherwise stop
				else
				{
					motor[LeftLift] = 0;
					motor[RightLift] = 0;
				}		
			}
		}
	}
}

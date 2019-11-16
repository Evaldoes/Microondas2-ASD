/*
 * Motor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Motor.h"
#include "h1/mkl_TPM.h"
#include "h1/mkl_TPMPulseWidthModulation.h"

//Motor::Motor() {
//	// TODO Auto-generated constructor stub
//
//Motor::~Motor() {
//	// TODO Auto-generated destructor stub
//}

void Motor::setupMotor(tpm_Pin motorPin) {
	mkl_TPMPulseWidthModulation motorConstructor(motorPin);
	motorObjt = motorConstructor;
	motorObjt.setFrequency(tpm_div16, 999);
}

void Motor::setControl(uint32_t inputOrigin) {
	control = inputOrigin;
}

void Motor::setSpeed() {
	speed = (control == 0) ? 1 : 0;

	//configura PWM
}

void Motor::setRotation() {
	if (operating) {
		clockWiseRotation = (control == 0) ? true : false;
		if (clockWiseRotation) {
			inDriveRight = 1;
			inDriveLeft = 0;
		}
		else {
			inDriveRight = 0;
			inDriveLeft = 1;
		}
	}
	else {
		inDriveRight = 0;
		inDriveLeft = 0;
	}

}

void Motor::switchState() {
	if (operating) {
		operating = false;
		setRotation();
	}
	else {
		operating = true;
		setRotation();
		setSpeed();
		setupPWM();
	}
}

void Motor::setupPWM(){
	if (control == 0) {
		motorObjt.setDutyCycle(100);
	}
	else {
		motorObjt.setDutyCycle(600);
	}
}

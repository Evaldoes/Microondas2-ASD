/*
 * Motor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include <h1/Motor.h>
#include "h1/mkl_TPM.h"

Motor::Motor(tpm_Pin motorPin) {
	// TODO Auto-generated constructor stub
	motor.mkl_TPMPulseWidthModulation(motorPin);
	motor.setFrequency(tpm_Div16, 999);
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

Motor::setControl(uint32_t inputOrigin) {
	control = inputOrigin;
}

Motor::setSpeed() {
	speed = (control == 0) ? 1 : 0;

	//configura PWM
}

Motor::setRotation() {
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

Motor::switchState() {
	if (operating) {
		operating = false;
		setRotation(0);
	}
	else {
		operating = true;
		setRotation(control);
		setSpeed(control);
		setupPWM();
	}
}

Motor::setupPWM(){
	if (control == 0) {
		motor.setDutyCycle(100);
	}
	else {
		motor.setDutyCycle(600);
	}
}

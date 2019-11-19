/*
 * Motor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Motor.h"
#include "h1/mkl_TPM.h"
#include "h1/mkl_TPMPulseWidthModulation.h"
#include "h1/dsf_GPIO_ocp.h"

Motor::Motor() {operating = false;}

void Motor::setPWMPin(tpm_Pin pin) {
	mkl_TPMPulseWidthModulation motorConstructor(pin);
	motor = motorConstructor;
	motor.setFrequency(tpm_div16, 999);
	control = 0;
}
//Motor::~Motor() {
//	// TODO Auto-generated destructor stub
//}

//void Motor::setupMotor(tpm_Pin motorPin, dsf_GPIO_ocp _inDriveRight, dsf_GPIO_ocp _inDriveLeft) {
//	mkl_TPMPulseWidthModulation motorConstructor(motorPin);
//	motor = motorConstructor;
//	motor.setFrequency(tpm_div16, 999);
//}

void Motor::setDriverInputs(dsf_GPIO_ocp _inDriveRight, dsf_GPIO_ocp _inDriveLeft) {
	inDriveRight = _inDriveRight;
	inDriveLeft = _inDriveLeft;
}

void Motor::setControl(uint32_t inputOrigin) {
	control = inputOrigin;
}

void Motor::setRotation() {
	clockWiseRotation = (control == 0) ? true : false;
	if (clockWiseRotation) {
		inDriveRight.writeBit(1);
		inDriveLeft.writeBit(0);
	}
	else {
		inDriveRight.writeBit(0);
		inDriveLeft.writeBit(1);
	}
}

void Motor::setSpeed(){
	if (control == 0) {
		motor.setDutyCycle(100);
	}
	else {
		motor.setDutyCycle(600);
	}
}

void Motor::powerConfig() {
	setControl(0);
	setRotation();
	setSpeed();
}

void Motor::enableDisablePower() {
	if (operating) {
		motor.disableOperation();
		operating = false;
	}
	else {
		motor.enableOperation();
		operating = true;
	}
}

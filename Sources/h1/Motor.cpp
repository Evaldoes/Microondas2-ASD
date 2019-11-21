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

Motor::Motor() {}

Motor::Motor(tpm_Pin motorPin,dsf_GPIO_ocp rotationRight, dsf_GPIO_ocp rotationLeft) {
	mkl_TPMPulseWidthModulation motorConstructor(motorPin);
	motor = motorConstructor;
	motor.setFrequency(tpm_div16, 999);

	setDriverInputs(rotationRight,rotationLeft);
	control = 0;
}

void Motor::setPWMPin(tpm_Pin pin) {
	mkl_TPMPulseWidthModulation motorConstructor(pin);
	motor = motorConstructor;
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

void Motor::setSpeed(int duty){
	motor.setDutyCycle(duty);
}

void Motor::powerConfig() {
	setControl(0);
	motor.setFrequency(tpm_div16, 999);
	setRotation();
	setSpeed(900);
//	operation = waitOp;
}

void Motor::enableDisablePower(bool inputBtn) {
	switch (operation) {
	case waitOp:
		if (inputBtn) {
			motor.enableOperation();
			operation = inOperation;
		}
		break;
	case inOperation:
		if (inputBtn) {
			motor.disableOperation();
			operation = waitOp;
		}
		break;
	}
}
mkl_TPMPulseWidthModulation Motor::getPWM() {
	return motor;
}

void Motor::keepEnable(bool on) {
	if (on) {
//		setRotation();
		motor.enableOperation();
	}
	else {
		motor.disableOperation();
	}
}

void Motor::disable() {
	motor.setDutyCycle(0);
	motor.enableOperation();
//	motor.disableOperation();
}

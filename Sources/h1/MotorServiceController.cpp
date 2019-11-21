/*
 * MotorServiceController.cpp
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#include "h1/MotorServiceController.h"

MotorServiceController::MotorServiceController(){}

MotorServiceController::MotorServiceController(Motor  _hBridgeAcess) {
	// TODO Auto-generated constructor stub
	hBridgeAcess = _hBridgeAcess;
	hBridgeAcess.powerConfig();
	actualState = waitingWheel;
}

MotorServiceController::~MotorServiceController() {
	// TODO Auto-generated destructor stub
}

void MotorServiceController::enableDisablePower(bool inputBtn) {
	if (inputBtn)
		actualState = (actualState == waitingWheel) ? workingWheel : waitingWheel;

	hBridgeAcess.enableDisablePower(inputBtn);
}

Motor MotorServiceController::getMotor() {
	return hBridgeAcess;
}

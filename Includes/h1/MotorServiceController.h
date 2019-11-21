/*
 * MotorServiceController.h
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_MOTORSERVICECONTROLLER_H_
#define SOURCES_H1_MOTORSERVICECONTROLLER_H_

#include "h1/Motor.h"

enum StatusMotor {
	waitingWheel,
	workingWheel
};

class MotorServiceController {
public:
	MotorServiceController();
	MotorServiceController(Motor _hBridgeAcess);
	virtual ~MotorServiceController();
	void enableDisablePower(bool inputBtn);
	Motor getMotor();

private:
	Motor hBridgeAcess;
	StatusMotor actualState;
};

#endif /* SOURCES_H1_MOTORSERVICECONTROLLER_H_ */

/*
 * Motor.h
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_MOTOR_H_
#define SOURCES_H1_MOTOR_H_

#include "mkl_TPMPulseWidthModulation.h"
#include <stdint.h>
#include "dsf_GPIO_ocp.h"
#include "mkl_TPM.h"

enum pwmPower {
	waitOp,
	inOperation
};

class Motor {
public:
	Motor();
	explicit Motor(tpm_Pin motorPin);
//	virtual ~Motor();
//	void setupMotor(tpm_Pin motorPin, dsf_GPIO_ocp _inDriveRight, dsf_GPIO_ocp _inDriveLeft);

	void setPWMPin(tpm_Pin pin);
	void setDriverInputs(dsf_GPIO_ocp _inDriveRight, dsf_GPIO_ocp _inDriveLeft);
	void setRotation();
	void setControl(uint32_t inputOrigin);
	void setSpeed();

	void powerConfig();
	void enableDisablePower(bool inputBtn);
private:
	mkl_TPMPulseWidthModulation motor;
	dsf_GPIO_ocp inDriveRight, inDriveLeft;
	uint32_t control;
	bool clockWiseRotation;
	pwmPower operation;
};

#endif /* SOURCES_H1_MOTOR_H_ */

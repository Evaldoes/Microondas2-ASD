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

class Motor {
public:
//	Motor();
//	virtual ~Motor();
	void setupMotor(tpm_Pin motorPin);
	void setSpeed();
	void setRotation();
	void setControl(uint32_t inputOrigin);
	void switchState(); 				//enable or disable
	void setupPWM();
private:
	mkl_TPMPulseWidthModulation motorObjt;
	uint32_t speed, dutyCycle, control;
	bool clockWiseRotation, operating;
	int inDriveRight, inDriveLeft;
};

#endif /* SOURCES_H1_MOTOR_H_ */

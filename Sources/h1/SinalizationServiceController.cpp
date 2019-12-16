/*
 * SinalizationServiceController.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/SinalizationServiceController.h"
#include "base/mkl_TPMDelay.h"

SinalizationServiceController::SinalizationServiceController(){

}

SinalizationServiceController::~SinalizationServiceController() {
	// TODO Auto-generated destructor stub
}

SinalizationServiceController::SinalizationServiceController(mkl_GPIOPort _buzzer,
		mkl_GPIOPort _doorSensor, mkl_GPIOPort _doorLed) {
	// TODO Auto-generated constructor stub
	buzzer = _buzzer;
	doorSensor = _doorSensor;
	doorLed = _doorLed;
	buzzer.writeBit(0);
}

bool SinalizationServiceController::isDoorClosed() {
	if (doorSensor.readBit() == 1) {
		doorLed.writeBit(1);
		return false;
	}
	doorLed.writeBit(0);
	return true;
}

mkl_GPIOPort SinalizationServiceController::getDoorLed() {
	return doorLed;
}

void SinalizationServiceController::callEndOfOperation() {
	mkl_TPMDelay delay(tpm_TPM0);
	delay.setFrequency(tpm_div128);
	delay.waitDelay(0xFFFF);
	delay.waitDelay(0xFFFF);
	delay.waitDelay(0xFFFF);
	delay.waitDelay(0xFF);
	doorLed.writeBit(1);
	buzzer.writeBit(1);
	delay.waitDelay(0xFFFF);
	delay.waitDelay(0xFFFF);
	buzzer.writeBit(0);
}

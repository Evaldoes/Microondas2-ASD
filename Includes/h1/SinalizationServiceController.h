/*
 * SinalizationServiceController.h
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_SINALIZATIONSERVICECONTROLLER_H_
#define SOURCES_H1_SINALIZATIONSERVICECONTROLLER_H_

#include "h1/DebouncedButton.h"
#include "h1/dsf_GPIO_ocp.h"
#include "h1/mkl_GPIOPort.h"

enum StatusSinalization {
	waitDoor,
	working
};

class SinalizationServiceController {
public:
	SinalizationServiceController();
	SinalizationServiceController(mkl_GPIOPort _buzzer, mkl_GPIOPort _doorSensor,
			mkl_GPIOPort _doorLed);
	virtual ~SinalizationServiceController();
	bool isDoorClosed();
	void callEndOfOperation();
	mkl_GPIOPort getDoorLed();
private:
	mkl_GPIOPort buzzer, doorSensor, doorLed;

};

#endif /* SOURCES_H1_SINALIZATIONSERVICECONTROLLER_H_ */

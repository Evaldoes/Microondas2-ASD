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

enum StatusSinalization {
	waitDoor,
	working
};

class SinalizationServiceController {
public:
	SinalizationServiceController();
	SinalizationServiceController(dsf_GPIO_ocp _buzzer, dsf_GPIO_ocp _doorSensor,
			dsf_GPIO_ocp _doorLed);
	virtual ~SinalizationServiceController();
	bool isDoorClosed();
	void callEndOfOperation();
private:
	dsf_GPIO_ocp buzzer, doorSensor, doorLed;

};

#endif /* SOURCES_H1_SINALIZATIONSERVICECONTROLLER_H_ */

/*
 * LED.h
 *
 *  Created on: 11/12/2019
 *      Author: Nader Hauache
 */

#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_

#include "base/mkl_GPIOPort.h"

class LED : mkl_GPIOPort{
public:
	LED(gpio_Pin pin);

	void turnOn();

	void turnOff();
};

#endif /* SOURCES_LED_H_ */

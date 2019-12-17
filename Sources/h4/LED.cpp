/*
 * LED.cpp
 *
 *  Created on: 11/12/2019
 *      Author: Nader Hauache
 */

#include "h4/LED.h"
#include "base/mkl_GPIOPort.h"

LED::LED(gpio_Pin pin) : mkl_GPIOPort(pin) {
	setPortMode(gpio_output);
	writeBit(1);
}

void LED::turnOn(){
	writeBit(0);
}

void LED::turnOff(){
	writeBit(1);
}




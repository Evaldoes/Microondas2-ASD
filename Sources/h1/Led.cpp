/*
 * Led.cpp
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#include <h1/Led.h>
#include <stdint.h>
#include "h1/dsf_GPIO_ocp.h"

Led::Led(dsf_GPIO_ocp pin) {
	// TODO Auto-generated constructor stub
	this->ledPin = pin;
	this->state = 0;
}

Led::~Led() {
	// TODO Auto-generated destructor stub
}

void Led::setState(uint32_t select) {
	this->state = select;
}

void Led::switchState() {
	this->state != this->state;
}

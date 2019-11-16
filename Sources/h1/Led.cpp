/*
 * Led.cpp
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#include "h1/Led.h"
#include <stdint.h>
#include "h1/dsf_GPIO_ocp.h"

//Led::Led(){}

//Led::~Led() {
//	// TODO Auto-generated destructor stub
//}

void Led::setup(dsf_GPIO_ocp pin) {
	ledPin = pin;
	state = 0;
}

void Led::setState(uint32_t select) {
	state = select;
}

void Led::switchState() {
	state != state;
}

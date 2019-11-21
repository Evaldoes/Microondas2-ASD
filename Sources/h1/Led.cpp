/*
  * Led.cpp
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#include "h1/Led.h"
#include <stdint.h>
#include "h1/dsf_GPIO_ocp.h"

Led::Led(){}

//Led::~Led() {
//	// TODO Auto-generated destructor stub
//}

void Led::setup(dsf_GPIO_ocp pin) {
	ledPin = pin;
	status = isOff;
}

void Led::setState(int select) {
	state = select;
	ledPin.writeBit(select);
}

int Led::getState(){
	return state;
}

void Led::switchState(bool pression) {
	switch (status) {
	case isOff:
		if (pression) {
			ledPin.writeBit(1);
			status = isOn;
		}
		break;
	case isOn:
		if (pression) {
			ledPin.writeBit(0);
			status = isOff;
		}
		break;
	default:
		break;
	}
}

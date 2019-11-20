/*
 * Led.h
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_LED_H_
#define SOURCES_H1_LED_H_

#include <stdint.h>
#include "dsf_GPIO_ocp.h"

enum onOff {
	isOn,
	isOff
};

class Led {
public:
	Led();
//	virtual ~Led();
	void setup(dsf_GPIO_ocp pin);
	void setState(int select);
	int getState();
	void switchState(bool pression);
private:
	int state;
	dsf_GPIO_ocp ledPin;
	onOff status;
};

#endif /* SOURCES_H1_LED_H_ */

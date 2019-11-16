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

class Led {
public:
//	Led();
//	virtual ~Led();
	void setup(dsf_GPIO_ocp pin);
	void setState(uint32_t select);
	void switchState();
private:
	uint32_t state;
	dsf_GPIO_ocp ledPin;
};

#endif /* SOURCES_H1_LED_H_ */

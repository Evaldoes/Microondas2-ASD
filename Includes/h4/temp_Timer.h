/*
 * temp_Timer.h
 *
 *  Created on: 02/12/2019
 *      Author: Nader Hauache
 */

#ifndef TEMP_TIMER_H_
#define TEMP_TIMER_H_

#include "base/mkl_SystickPeriodicInterrupt.h"

//mkl_SystickPeriodicInterrupt systickModule(10,clock42Mhz);

class temp_Timer : mkl_SystickPeriodicInterrupt {
public:
	temp_Timer();
	void liga();
	void desliga();
};

#endif /* TEMP_TIMER_H_ */


/*
 * temp_Timer.cpp
 *
 *  Created on: 02/12/2019
 *      Author: Nader Hauache
 */

#include "temp_Timer.h"

temp_Timer::temp_Timer() : mkl_SystickPeriodicInterrupt(10, clock42Mhz) {
	// TODO Auto-generated constructor stub
	//systickModule.setPriority(systick_priority0);
	//setPriority(systick_priority0);
}

void temp_Timer::liga(){
	//systickModule.enableInterruptRequest();
	enableInterruptRequest();
}

void temp_Timer::desliga(){
	//systickModule.disableInterruptRequest();
	disableInterruptRequest();
}

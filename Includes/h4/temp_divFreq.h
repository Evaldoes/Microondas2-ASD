/*
 * temp_divFreq.h
 *
 *  Created on: 03/12/2019
 *      Author: Nader Hauache
 */

#ifndef SOURCES_TEMP_DIVFREQ_H_
#define SOURCES_TEMP_DIVFREQ_H_

#include "temp_Timer.h"

//temp_Timer timer;

//Basicamente um contador

class temp_divFreq: temp_Timer  {
public:

	int contagem;
	int tempo;

	// 100 ciclos de 10ms = 1seg.
	// mudança analisada empiricamente... ciclos= 50, nao 100.
	int ciclos = 50;

	bool cout;

	temp_divFreq();

	void increment();
	bool isCarryOut();


};

#endif /* SOURCES_TEMP_DIVFREQ_H_ */

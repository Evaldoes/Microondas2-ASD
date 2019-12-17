/*
 * srvTemp.h
 *
 *  Created on: 12/12/2019
 *      Author: Nader Hauache
 */

#include "digTemp.h"
#include "types.h"

#ifndef SOURCES_SRVTEMP_H_
#define SOURCES_SRVTEMP_H_


class srvTemp {
public:
	srvTemp();

	int getMD();
	int getMU();
	int getSD();
	int getSU();
	char int2Char(int a);

	bool putTime(int MD, int MU, int SD, int SU);
	bool putPreCoz(cozimentotype tipo);
	bool decrement();

	bool isEot();
	bool isExecute();

	bool play();
	bool pause();
	bool reset();

protected:
	bool ocupaBT = false;
	bool ocupaKB = false;
	bool executando = false;
};

#endif /* SOURCES_SRVTEMP_H_ */

/*
 * digTemp.h
 *
 *  Created on: 11/12/2019
 *      Author: Nader Hauache
 */

#include "types.h"

#ifndef SOURCES_DIGTEMP_H_
#define SOURCES_DIGTEMP_H_

class digTemp {
public:
	digTemp();

	bool edicao(int MD, int MU, int SD, int SU);
	//bool atualiza(int MD, int MU, int SD, int SU);
	bool preCoz(cozimentotype tipo);
	bool decrementa();

	bool isEot();
	int getContador();
	int min2Seg(int MD, int MU, int SD, int SU);

	bool clear();

private:
	int contador;
	bool eot;

};

#endif /* SOURCES_DIGTEMP_H_ */

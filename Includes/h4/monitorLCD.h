/*
 * monitor.h
 *
 *  Created on: 12/12/2019
 *      Author: Nader Hauache
 */

#include "types.h"
#include "srvTemp.h"
#include "srvShow.h"

#ifndef SOURCES_MONITOR_H_
#define SOURCES_MONITOR_H_

class monitorLCD {
public:
	monitorLCD();

	//Fun��es de Read. Respondem estaticamente ao lcd
	bool setTime(int MD, int MU, int SD, int SU, cozimentotype tipo); //tipo edi��o ou update
	bool setPreCoz(cozimentotype tipo); //Pizza, Lasanha ou Pipoca
	bool setState(bool door, bool valveSpin); //Estado da Porta e Estado da V�lvula

	//Fun��es de funcionamento
	bool printLCD(); // ---> Fun��o a ser chamada na temporiza��o do systick para atualiza��o de tempo
	bool play();
	bool pause();
	bool cancel(); //-- cancelamento ou clear
	bool ledEot();
	bool decrementa1(); //depende da temporiza��o do systick

	//Fun��es de Retorno
	bool isEot();
	int getMD();
	int getMU();
	int getSD();
	int getSU();

};

#endif /* SOURCES_MONITOR_H_ */

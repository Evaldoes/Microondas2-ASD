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

	//Funções de Read. Respondem estaticamente ao lcd
	bool setTime(int MD, int MU, int SD, int SU, cozimentotype tipo); //tipo edição ou update
	bool setPreCoz(cozimentotype tipo); //Pizza, Lasanha ou Pipoca
	bool setState(bool door, bool valveSpin); //Estado da Porta e Estado da Válvula

	//Funções de funcionamento
	bool printLCD(); // ---> Função a ser chamada na temporização do systick para atualização de tempo
	bool play();
	bool pause();
	bool cancel(); //-- cancelamento ou clear
	bool ledEot();
	bool decrementa1(); //depende da temporização do systick

	//Funções de Retorno
	bool isEot();
	int getMD();
	int getMU();
	int getSD();
	int getSU();

};

#endif /* SOURCES_MONITOR_H_ */

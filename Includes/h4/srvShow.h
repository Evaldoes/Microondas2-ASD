/*
 * srvShow.h
 *
 *  Created on: 05/12/2019
 *      Author: Nader Hauache
 */

//Serviço de Exibição de Dados no LCD
//MicroServiço de impressão de tempo, estado(valvula, porta e giro) e cozimento

#include "lcd_escreveVisor.h"

#ifndef SOURCES_SRVSHOW_H_
#define SOURCES_SRVSHOW_H_

class srvShow {
public:
	srvShow();
	void printTime(int MD, int MU, int SD, int SU);
	void printCoz(cozimentotype tipo);
	void printOp(onOfftype porta, onOfftype valvulaGiro);
	void clean();
	char castInt2Char(int number);
};

#endif /* SOURCES_SRVSHOW_H_ */

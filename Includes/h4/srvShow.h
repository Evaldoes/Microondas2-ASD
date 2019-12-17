/*
 * srvShow.h
 *
 *  Created on: 05/12/2019
 *      Author: Nader Hauache
 */

//Servi�o de Exibi��o de Dados no LCD
//MicroServi�o de impress�o de tempo, estado(valvula, porta e giro) e cozimento

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

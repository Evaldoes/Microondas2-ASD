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
	void config(lcd_escreveVisor _visor);
	void printTime(int MD, int MU, int SD, int SU);
	void printCoz(cozimentotype tipo);
	void printOp(bool porta, onOfftype valvulaGiro);
	void clean();
	char castInt2Char(int number);
	bool editingPermission;
private:
	lcd_escreveVisor visor;
};

#endif /* SOURCES_SRVSHOW_H_ */

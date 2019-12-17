/*
 * lcd_escreveVisor.h
 *
 *  Created on: 30/11/2019
 *      Author: Nader Hauache
 */

#include <mkl_LCD.h>
#include "types.h"

#ifndef SOURCES_LCD_ESCREVEVISOR_H_
#define SOURCES_LCD_ESCREVEVISOR_H_

class lcd_escreveVisor {
public:

	lcd_escreveVisor();

	void setup();

	void escreveCozimento(cozimentotype tipo);

	void escrevePorta(onOfftype boolean);
	void escreveValvula(onOfftype boolean);
	void escreveGiro(onOfftype boolean);

	//metodo que altera Valvula e Giro ao mesmo tempo
	void escreveValvulaGiro(onOfftype boolean);

	void escreveTempo(char MD, char MU, char SD, char SU);

};


#endif /* SOURCES_LCD_ESCREVEVISOR_H_ */

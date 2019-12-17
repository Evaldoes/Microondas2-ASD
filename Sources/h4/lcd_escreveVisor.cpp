/*
 * lcd_escreveVisor.cpp
 *
 *  Created on: 30/11/2019
 *      Author: Nader Hauache
 */

#include "h4/lcd_escreveVisor.h"

/*!
 *   Endereço do módulo I2C utilizado
 */
uint8_t deviceAddress = 0x27;

/*!
 *   Configura e instancia o formato do display e os parametros do modulo I2C
 */
mkl_LCD lcdVisor(mode2Lines, mode16Cols, mode5x8Dots, i2c_PTE1, i2c_PTE0,
  deviceAddress);

lcd_escreveVisor::lcd_escreveVisor() {
	// TODO Auto-generated constructor stub
	lcdVisor.setBacklightOn();
	lcdVisor.setDisplayOn();
	lcdVisor.setCursorOff();
	lcdVisor.setBlinkOff();
	lcdVisor.clear();
	setup();
}

void lcd_escreveVisor::setup(){
	lcdVisor.clear();

	lcdVisor.setCursor(1,3);
	lcdVisor.putChar(':');

	lcdVisor.setCursor(2,1);
	lcdVisor.putString("P:");

	lcdVisor.setCursor(2,6);
	lcdVisor.putString("V:");

	lcdVisor.setCursor(2,12);
	lcdVisor.putString("G:");
}

void lcd_escreveVisor::escreveCozimento(cozimentotype tipo){

	lcdVisor.setCursor(1,7);

	switch (tipo){

	case edicao:
		lcdVisor.putString("EDICAO ");
		break;

	case pizza:
		lcdVisor.putString("PIZZA  ");
		break;

	case pipoca:
		lcdVisor.putString("PIPOCA ");
		break;

	case lasanha:
		lcdVisor.putString("LASANHA");
		break;

	case inc3:
		lcdVisor.putString("INC3   ");
		break;

	case inc5:
		lcdVisor.putString("INC5   ");
		break;

	case inc7:
		lcdVisor.putString("INC7   ");
		break;

	}
}

void lcd_escreveVisor::escrevePorta(onOfftype boolean){
	lcdVisor.setCursor(2,3);
	switch (boolean){

	case on:
		lcdVisor.putString("ON ");
		break;

	case off:
		lcdVisor.putString("OFF");
		break;

	}
}

void lcd_escreveVisor::escreveValvula(onOfftype boolean){
	lcdVisor.setCursor(2,8);
	switch (boolean){

	case on:
		lcdVisor.putString("ON ");
		break;

	case off:
		lcdVisor.putString("OFF");
		break;

	}
}

void lcd_escreveVisor::escreveGiro(onOfftype boolean){
	lcdVisor.setCursor(2,14);
	switch (boolean){

	case on:
		lcdVisor.putString("ON ");
		break;

	case off:
		lcdVisor.putString("OFF");
		break;

	}
}

void lcd_escreveVisor::escreveValvulaGiro(onOfftype boolean){
		escreveValvula(boolean);
		escreveGiro(boolean);
}

void lcd_escreveVisor::escreveTempo(char MD, char MU, char SD, char SU){
	if (SU == '0' && SD == '0'){
		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(' ');
		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(' ');
	}

	else if(SD == '0'){
		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(' ');
	}
	else{
		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(SD);
	}

	if (MU == '0' && MD == '0'){
			lcdVisor.setCursor(1,2);
			lcdVisor.putChar(' ');
			lcdVisor.setCursor(1,1);
			lcdVisor.putChar(' ');
		}

		else if(MD == '0'){
			lcdVisor.setCursor(1,2);
			lcdVisor.putChar(MU);
			lcdVisor.setCursor(1,1);
			lcdVisor.putChar(' ');
		}
		else{
			lcdVisor.setCursor(1,2);
			lcdVisor.putChar(MU);
			lcdVisor.setCursor(1,1);
			lcdVisor.putChar(MD);
		}

}

/*
void lcd_escreveVisor::escreveTempo(char MD, char MU, char SD, char SU){
	if(MD == '0' && MU == '0' && SD == '0' && SU == '0'){

		lcdVisor.setCursor(1,1);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,2);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(' ');

	}

	else if(MD == '0' && MU == '0' && SD == '0'){
		lcdVisor.setCursor(1,1);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,2);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
	}

	else if(MD == '0' && MU == '0'){
		lcdVisor.setCursor(1,1);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,2);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(SD);

		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
		}

	else if(MD == '0'){
		lcdVisor.setCursor(1,1);
		lcdVisor.putChar(' ');

		lcdVisor.setCursor(1,2);
		lcdVisor.putChar(MU);

		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(SD);

		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
		}

	else{
		lcdVisor.setCursor(1,1);
		lcdVisor.putChar(MD);

		lcdVisor.setCursor(1,2);
		lcdVisor.putChar(MU);

		lcdVisor.setCursor(1,4);
		lcdVisor.putChar(SD);

		lcdVisor.setCursor(1,5);
		lcdVisor.putChar(SU);
	}
}
*/

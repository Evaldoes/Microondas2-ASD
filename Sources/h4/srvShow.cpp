/*
 * srvShow.cpp
 *
 *  Created on: 05/12/2019
 *      Author: Nader Hauache
 */

#include "h4/srvShow.h"

lcd_escreveVisor visor;

srvShow::srvShow() {
	// TODO Auto-generated constructor stub
}

char srvShow::castInt2Char(int number){
	char out;
	switch(number){
	case 0:
		out = '0';
		break;
	case 1:
		out = '1';
		break;
	case 2:
		out = '2';
		break;
	case 3:
		out = '3';
		break;
	case 4:
		out = '4';
		break;
	case 5:
		out = '5';
		break;
	case 6:
		out = '6';
		break;
	case 7:
		out = '7';
		break;
	case 8:
		out = '8';
		break;
	case 9:
		out = '9';
		break;
	}
	return out;
}

void srvShow::clean(){
	visor.setup();
}

void srvShow::printTime(int MD, int MU, int SD, int SU){
	char M1,M2;
	char S1,S2;

	M1 = castInt2Char(MD);
	M2 = castInt2Char(MU);
	S1 = castInt2Char(SD);
	S2 = castInt2Char(SU);

	visor.escreveTempo(M1,M2,S1,S2);
}

void srvShow::printOp(onOfftype porta, onOfftype valvulaGiro){
	visor.escrevePorta(porta);
	visor.escreveValvulaGiro(valvulaGiro);
}


void srvShow::printCoz(cozimentotype tipo){
	visor.escreveCozimento(tipo);
}




/*
 * monitor.cpp
 *
 *  Created on: 12/12/2019
 *      Author: Nader Hauache
 */

#include "h4/monitorLCD.h"

srvTemp tempo;
srvShow lcd;
LED redLed(gpio_PTB19);

monitorLCD::monitorLCD() {
	// TODO Auto-generated constructor stub

}

bool monitorLCD::setTime(int MD, int MU, int SD, int SU, cozimentotype tipo){

	if(tipo == edicao){
		lcd.printCoz(edicao);
	}
	else if(tipo == inc3){
		lcd.printCoz(inc3);
	}
	else if(tipo == inc7){
		lcd.printCoz(inc7);
	}
	else{
		return false;
	}

	if(tempo.isExecute() == false || tipo == inc3 || tipo == inc7){
		return tempo.putTime(MD,MU,SD,SU);
	}

}

bool monitorLCD::setPreCoz(cozimentotype tipo){

	if(tipo == pizza){
		lcd.printCoz(pizza);
	}
	else if(tipo == lasanha){
		lcd.printCoz(lasanha);
	}
	else if(tipo == pipoca){
		lcd.printCoz(pipoca);
	}
	else{
		return false;
	}

	return tempo.putPreCoz(tipo);
}

bool monitorLCD::setState(bool door, bool valvespin){
	lcd.printOp(door,valvespin);
}

bool monitorLCD::printLCD(){
	lcd.printTime(tempo.int2Char(tempo.getMD()), tempo.int2Char(tempo.getMU()), tempo.int2Char(tempo.getSD()), tempo.int2Char(tempo.getSU()));
}

bool monitorLCD::play(){
	tempo.play();
}

bool monitorLCD::pause(){
	tempo.pause();
}

bool monitorLCD::cancel(){
	tempo.reset();
	lcd.printTime('0','0','0','0');
	lcd.printCoz(edicao);
	redLed.turnOff();
}

bool monitorLCD::ledEot(){
	if (tempo.isEot() == true){
		redLed.turnOn();
		return true;
	}
	else{
		return false;
	}
}

bool monitorLCD::isEot(){
	return tempo.isEot();
}

bool monitorLCD::decrementa1(){
	return tempo.decrement();

}

int monitorLCD::getMD(){
	return tempo.getMD();
}

int monitorLCD::getMU(){
	return tempo.getMU();
}

int monitorLCD::getSD(){
	return tempo.getSD();
}

int monitorLCD::getSU(){
	return tempo.getSU();
}

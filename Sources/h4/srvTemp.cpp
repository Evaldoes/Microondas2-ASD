/*
 * srvTemp.cpp
 *
 *  Created on: 12/12/2019
 *      Author: Nader Hauache
 */

#include <srvTemp.h>

digTemp temp;

srvTemp::srvTemp() {
	// TODO Auto-generated constructor stub
	ocupaBT = false;
	ocupaKB = false;
	executando = false;
}

int srvTemp::getMD(){
	int time = temp.getContador();
	int totalMinutes = time/60; //separa a quantidade de minutos
	int dezMinutes = totalMinutes/10; //separa a quantidade de dezenas de minutos
	return dezMinutes;
}

int srvTemp::getMU(){
	int time = temp.getContador();
	int totalMinutes = time/60; //separa a quantidade de minutos
	int unidMinutes = totalMinutes%10; //separa a quantidade de unidades de minutos
	return unidMinutes;
}

int srvTemp::getSD(){
	int time = temp.getContador();
	int totalSec = time%60; //Separa a quantidade de segundos dos minutos
	int dezSec = totalSec/10;
	return dezSec;
}

int srvTemp::getSU(){
	int time = temp.getContador();
	int totalSec = time%60; //Separa a quantidade de segundos dos minutos
	int unidSec = totalSec%10;
	return unidSec;
}

char srvTemp::int2Char(int a){
	return (char)a;
}

bool srvTemp::putTime(int MD, int MU, int SD, int SU){
	//Se terminado anteriormente
	if (temp.isEot() == true){
		temp.clear();
	}

	//Se vazio, i.e, resetado
	if (temp.getContador() == 0 && ocupaBT == false && ocupaKB == false && executando == false){
		ocupaKB = true;
		ocupaBT = false;
		executando = false;
		temp.edicao(MD,MU,SD,SU);
		return true;
	}

	//Se ocupado, i.e, atualização de tempo para incremento
	else if (temp.getContador() != 0 && executando == true){
		temp.edicao(MD,MU,SD,SU);
	}
	//Se BT estiver usando para preCoz, então ignora-se edição até término.
	else{
		return false;
	}

}

bool srvTemp::putPreCoz(cozimentotype tipo){
	//Se terminado anteriormente
	if (temp.isEot() == true){
		temp.clear();
	}

	ocupaKB = false;
	ocupaBT = true;

	temp.preCoz(tipo);

	return true;

}

bool srvTemp::decrement(){
	//se estiver executando temporizacao
	if(executando == true){
		//se temporizador não estiver vazio
		if(temp.isEot() == false){
			temp.decrementa();
			return true;
		}
		//se estiver com temporizador vazio
		else{
			executando = false;
			ocupaBT = false;
			ocupaKB = false;
			return false;
		}
	}
}

bool srvTemp::isEot(){
	return temp.isEot();
}

bool srvTemp::isExecute(){
	return executando;
}

bool srvTemp::play(){
	executando = true;
	return true;
}

bool srvTemp::pause(){
	executando = false;
	return true;
}

bool srvTemp::reset(){
	ocupaBT = false;
	ocupaKB = false;
	executando = false;
	temp.clear();
}

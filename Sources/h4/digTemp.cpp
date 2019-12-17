/*
 * digTemp.cpp
 *
 *  Created on: 11/12/2019
 *      Author: Nader Hauache
 */

#include <digTemp.h>

digTemp::digTemp() {
	// TODO Auto-generated constructor stub
	int contador = 0;
	eot = false;
}

bool digTemp::edicao(int MD, int MU, int SD, int SU){
	contador = min2Seg(MD,MU,SD,SU);
	return true;
}

//Atualiza para inserção de incremento(não importa quem está ocupando o uso, o incremento é direto)

/*
 * int digTemp::atualiza(int MD, int MU, int SD, int SU){
 *	contador = min2Seg(MD,MU,SD,SU);
 *	return contador;
}*/

//PreCozimento tem prioridade de "input" e troca de usuario
bool digTemp::preCoz(cozimentotype tipo){
		switch (tipo){
			case pizza:
				contador = min2Seg(0,1,0,1);
				break;

			case lasanha:
				contador = min2Seg(0,2,0,2);
				break;

			case pipoca:
				contador = min2Seg(0,0,3,0);
				break;
		return true;
	}
}

//decrementa 1 unidade cada vez que é invocado
bool digTemp::decrementa(){
	if(contador == 0){
		eot = true;
		return false;
	}
	else{
		eot = false;
		contador -= 1;
		return true;
	}

}

int digTemp::min2Seg(int MD, int MU, int SD, int SU){
	int segundos;
	segundos = SU+(10*SD)+(60*MU)+(10*60*MD);
	return segundos;
}

int digTemp::getContador(){
	return contador;
}

bool digTemp::isEot(){
	return eot;
}

bool digTemp::clear(){
	contador = 0;
	eot = false;
	return true;
}

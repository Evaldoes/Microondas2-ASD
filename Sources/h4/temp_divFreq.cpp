/*
 * temp_divFreq.cpp
 *
 *  Created on: 03/12/2019
 *      Author: Nader Hauache
 */

#include "h4/temp_divFreq.h"

temp_divFreq::temp_divFreq() : temp_Timer() {
	// TODO Auto-generated constructor stub

}

void temp_divFreq::increment(){
	contagem += 1;
	if(contagem == ciclos){
		cout = true;
		contagem = 0;
	}
	else{
		cout = false;
	}
}

bool temp_divFreq::isCarryOut(){
	return cout;
}

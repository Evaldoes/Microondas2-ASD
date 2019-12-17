#include "Register.h"


Register::Register() {
	q = 0;
}

void Register::loadQ(int data) {
	q = data;
}

void Register::clear(){
	q = 0;
}

int Register::getQ0(){
	return (q & 0x000f);
}

int Register::getQ1(){
	return (q & 0x00f0)>>4;
}

int Register::getQ2(){
	return (q & 0x0f00)>>8;
}

int Register::getQ3(){
	return (q & 0xf000)>>12;
}

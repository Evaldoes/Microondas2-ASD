#include "DigitalFactory.h"

DigitalFactory::DigitalFactory(){

}

bool DigitalFactory::createDecoder(){
	try {
		ptrdec = new Decoder;
		return true;
	}
	catch(...){
		return false;
	}
}

bool DigitalFactory::createRegister(){
	try {
		ptrreg = new Register;
		ptrreg->clear();
		return true;
	}
	catch(...){
		return false;
	}
}

Decoder* DigitalFactory::getptrdec(){
	return ptrdec;
}

Register* DigitalFactory::getptrreg(){
	return ptrreg;
}

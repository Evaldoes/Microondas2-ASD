#include "Decoder.h"

int Decoder::doDecode(int data){
	switch(data){
	case 'a': //PIPOCA
		return 0x0030;
	case 'b': //PIZZA
		return 0x0101;
	case 'c': //LASANHA
		return 0x0202;
	case 'd': //LIGA
		return 0x1000;
	case 'e': //DESLIGA
		return 0x2000;
	}
}


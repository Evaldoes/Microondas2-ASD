#include "displaySegments.h"


dsf_Delay_ocp tpm(TPM_t::dsf_TPM2);

displaySegments::displaySegments(gpio_Pin pinoA,gpio_Pin pinoB,gpio_Pin pinoC,
		gpio_Pin pinoD,gpio_Pin pinoE,gpio_Pin pinoF,gpio_Pin pinoG, gpio_Pin pinoDig1,
		 gpio_Pin pinDig2,  gpio_Pin pinDig3,  gpio_Pin pinDig4, gpio_Pin pinDelay){
	//Pinagem dos 7 segmentos
	D1=mkl_GPIOPort(pinoDig1);
	D2=mkl_GPIOPort(pinDig2);
	D3=mkl_GPIOPort(pinDig3);
	D4=mkl_GPIOPort(pinDig4);
	sega=mkl_GPIOPort(pinoA);
	segb=mkl_GPIOPort(pinoB);
	segc=mkl_GPIOPort(pinoC);
	segd=mkl_GPIOPort(pinoD);
	sege=mkl_GPIOPort(pinoE);
	segf=mkl_GPIOPort(pinoF);
	segg=mkl_GPIOPort(pinoG);
//	segdot=mkl_GPIOPort(segm_dot);
	D1.setPortMode(gpio_output);
	D2.setPortMode(gpio_output);
	D3.setPortMode(gpio_output);
	D4.setPortMode(gpio_output);
	sega.setPortMode(gpio_output);
	segb.setPortMode(gpio_output);
	segc.setPortMode(gpio_output);
	segd.setPortMode(gpio_output);
	sege.setPortMode(gpio_output);
	segf.setPortMode(gpio_output);
	segg.setPortMode(gpio_output);
}
void displaySegments::seta_segmento(int key){
	if(key==0){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(1);
		segf.writeBit(1);
		segg.writeBit(0);
	}
	else if(key==1){
		sega.writeBit(0);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(0);
		sege.writeBit(0);
		segf.writeBit(0);
		segg.writeBit(0);
	}
	else if(key==2){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(0);
		segd.writeBit(1);
		sege.writeBit(1);
		segf.writeBit(0);
		segg.writeBit(1);
	}
	else if(key==3){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(0);
		segf.writeBit(0);
		segg.writeBit(1);
	}
	else if(key==4){
		sega.writeBit(0);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(0);
		sege.writeBit(0);
		segf.writeBit(1);
		segg.writeBit(1);
	}
	else if(key==5){
		sega.writeBit(1);
		segb.writeBit(0);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(0);
		segf.writeBit(1);
		segg.writeBit(1);
	}
	else if(key==6){
		sega.writeBit(1);
		segb.writeBit(0);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(1);
		segf.writeBit(1);
		segg.writeBit(1);
	}
	else if(key==7){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(0);
		sege.writeBit(0);
		segf.writeBit(0);
		segg.writeBit(0);
	}
	else if(key==8){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(1);
		segf.writeBit(1);
		segg.writeBit(1);
	}
	else if(key==9){
		sega.writeBit(1);
		segb.writeBit(1);
		segc.writeBit(1);
		segd.writeBit(1);
		sege.writeBit(0);
		segf.writeBit(1);
		segg.writeBit(1);
	}
}


void displaySegments::digito(int key, int position){

	switch(position){
	case 1:
		D1.writeBit(0);
		D2.writeBit(1);
		D3.writeBit(1);
		D4.writeBit(1);
		break;
	case 2:
		D1.writeBit(1);
		D2.writeBit(0);
		D3.writeBit(1);
		D4.writeBit(1);
		break;
	case 3:
		D1.writeBit(1);
		D2.writeBit(1);
		D3.writeBit(0);
		D4.writeBit(1);
		break;
	case 4:
		D1.writeBit(1);
		D2.writeBit(1);
		D3.writeBit(1);
		D4.writeBit(0);
		break;
	}
	seta_segmento(key);
}

void displaySegments::monitora(int key1, int key2, int key3, int key4){
	tpm.setFrequency(TPMDiv_t::Div1);
	digito(key4,4);
	tpm.waitDelay(0xFFFF);
	digito(key3,3);
	tpm.waitDelay(0xFFFF);
	digito(key2,2);
	tpm.waitDelay(0xFFFF);
	digito(key1,1);
	tpm.waitDelay(0xFFFF);

}

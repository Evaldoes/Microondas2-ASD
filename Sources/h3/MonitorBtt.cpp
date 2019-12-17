#include "h3/MonitorBtt.h"

bool hasdata;
int read;

MonitorBtt::MonitorBtt(){
	ptrledon = new Led(gpio_PTB19);
	ptrledoff = new Led(gpio_PTB18);
	ptrledon->turnOff();
	ptrledoff->turnOff();
	bluetooth = new Bluetooth(uart0_PTA2, uart0_PTA1);
	factory = new DigitalFactory;
	factory->createDecoder();
	factory->createRegister();
	ops = new OperationService(factory);
	coz = new CookingService(factory);
	coz->setup(&buff0,&buff1,&buff2,&buff3);
	ops->setup(&onoff);
	setup();
}

void MonitorBtt::setup(){
	hasdata = false;
	read = 0;
	buff0 = 0;
	buff1 = 0;
	buff2 = 0;
	buff3 = 0;
	onoff = 0;
	//sid = SemServico;
}

void MonitorBtt::readInputs(){
	hasdata = bluetooth->wasData();
	read = bluetooth->read();
}

sid_t MonitorBtt::selectService(){
	if(hasdata == true){
		switch(read){
		case 'a':
			return Cooking; //Pizza
			break;
		case 'b':
			return Cooking;//Pipoca
			break;
		case 'c':
			return Cooking;//Lasanha
			break;
		case 'd':
			return Operation;//Start/Continue
			break;
		case 'e':
			return Operation;//Cancel
			break;
		default:
			return NoService; //Sem Servicos
			break;
		}
	}
	else{
		return NoService;
	}
}

void MonitorBtt::doService(sid_t next){
	if(next == Cooking){
		coz->doService(read);
	}
	else if(next == Operation){
		ops->doService(read);
	}
}

void MonitorBtt::writeOutputs(sid_t sid){
	if(sid == Cooking){
		printf("%d\n",buff3);
		printf("%d\n",buff2);
		printf("%d\n",buff1);
		printf("%d\n",buff0);
		//BOTAR AQUI OS TIPOS DE COZIMENTO <-----------------------
	}
	if(sid == Operation){
		if(onoff == 1){
			ptrledoff->turnOn();
			ptrledon->turnOff();
			//BOTAR AQUI A VARIAVEL START/CONTINUE<-----------------------
		}
		else{
			ptrledoff->turnOff();
			ptrledon->turnOn();
			//BOTAR AQUI A VARIAVEL CANCEL<-----------------------
		}
	}

}


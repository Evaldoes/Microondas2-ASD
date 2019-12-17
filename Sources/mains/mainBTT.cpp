#include <stdio.h>
#include "h3/MonitorLCD.h"
sid_t estado;

int main(){
	Monitor service;
	while(true){
		service.readInputs(); // L� as entradas do Bluetooth
		estado = service.selectService(); //Seleciona a opera��o
		service.doService(estado); // realiza as opera��es de cozimento ou start/cancel
		service.writeOutputs(estado); // Retorna as Saidas
	}
}

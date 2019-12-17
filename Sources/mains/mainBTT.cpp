#include <stdio.h>
#include "h3/MonitorLCD.h"
sid_t estado;

int main(){
	Monitor service;
	while(true){
		service.readInputs(); // Lê as entradas do Bluetooth
		estado = service.selectService(); //Seleciona a operação
		service.doService(estado); // realiza as operações de cozimento ou start/cancel
		service.writeOutputs(estado); // Retorna as Saidas
	}
}

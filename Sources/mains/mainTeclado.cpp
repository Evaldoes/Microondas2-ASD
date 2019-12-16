#include <stdint.h>
#include <MKL25Z4.h>
#include "teclado/mkl_KeyboardParallelPort.h"
#include "bibliotecas/mkl_SystickPeriodicInterrupt.h"
#include "dispositivos/led.h"
#include "dispositivos/switch.h"
#include "dispositivos/displaySegments.h"
#include "servicos/EditService.h"
#include "dispositivos/button.h"
#include "servicos/IncrementService.h"

mkl_KeyboardParallelPort keyboard(gpio_PTA13, gpio_PTD5, gpio_PTD0, gpio_PTD2,
gpio_PTC12, gpio_PTC13, gpio_PTC16, gpio_PTC17); // Pinagem para o teclado

displaySegments display (gpio_PTC7,gpio_PTC0,gpio_PTC3,gpio_PTC4,gpio_PTC5,
		gpio_PTC6,gpio_PTC10,gpio_PTC1, gpio_PTE29, gpio_PTE23, gpio_PTE22, gpio_PTB8); //Vai ser substituido pelo LCD


mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

/*Registradores tipo Int, ponteiros*/
registrador Us(0);
registrador Ds(0);
registrador Um(0);
registrador Dm(0);

switche botao3(gpio_PTB9),botao7(gpio_PTB11); //Botões de incremento


switche permission(gpio_PTE5); //Botão que simulava a resposta da permissão do Temporizador

//Serviços da História Teclado
controlador service_edit;
IncrementService service_inc;

char key;
int valor=0; //Conversão para Int

extern "C" {
    void SysTick_Handler(void) {
    	keyboard.update();
        key = keyboard.getKey();
        if(keyboard.keyIsPressed()){
        	valor=key;
        }
        else{
        }
    }
}

void setup(){

}
int main(){
	setup();
	while(1){
		/*Serviço de edição*/
		service_edit.maq_est(keyboard.keyIsPressed(),!permission.read());
		service_edit.select_service();
		service_edit.do_service(&Dm,&Um,&Ds,&Us,valor);

		/*Serviço de Incremento*/
    	service_inc.machineState(botao3.isOn(),botao7.isOn(),!permission.read());
    	service_inc.selectService();
    	service_inc.doService(&Dm,&Um,&Ds,&Us);

    	/*Exibição no Display
    	 * (valores dos ponteiros passados como inteiros para
    	 *  o display serão passados do mesmo jeito para LCD)*/
    	display.monitora(Dm.leValor(),Um.leValor(),Ds.leValor(),Us.leValor());


	}
	return 0;
}


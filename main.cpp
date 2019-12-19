/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>

// SDK PLACA
#include "MKL25Z4.h"


////FRAMEWORK E DEBOUNCE PARA AS HISTORIAS
//#include "base/mkl_GPIOPort.h"
//#include "base/mkl_TPMDelay.h"
//#include "base/mkl_TPMPulseWidthModulation.h"
//#include "base/DebouncedButton.h"
//#include "base/mkl_KeyboardParallelPort.h"
//#include "base/mkl_SystickPeriodicInterrupt.h"
//
//#include "base/variables.h"
//
//
////---------------------------------------------------------------------- MOTOR H1 ---------------------------------------------------
//#include "h1/Motor.h"
#include "h1/Monitor.h"
//#include "h1/SinalizationServiceController.h"
//#include "h1/MotorServiceController.h"
//
//
////---------------------------------------------------------------------- TECLADO H2 -------------------------------------------------
//#include "h2/led.h"
//#include "h2/switch.h"
//#include "h2/displaySegments.h"
//#include "h2/EditService.h"
//#include "h2/IncrementService.h"
//
//
////---------------------------------------------------------------------- BTT H3 ------------------------------------------------------
//#include "h3/MonitorBtt.h"
//
//
////---------------------------------------------------------------------- LCD H4 ------------------------------------------------------
//#include "h4/srvShow.h"
//#include "h4/LED.h"
//#include "h4/temp_divFreq.h"
//#include "h4/srvTemp.h"
//#include "h4/types.h"

/*
 * Criacao dos objetos perifericos
 */

// BOTOES
DebouncedButton onOff_Btn(gpio_Pin::gpio_PTE23,gpio_PullResistor::gpio_pullUpResistor);
DebouncedButton startPause_Btn(gpio_Pin::gpio_PTC1,gpio_PullResistor::gpio_pullUpResistor);
DebouncedButton cancel_Btn(gpio_Pin::gpio_PTC2,gpio_PullResistor::gpio_pullUpResistor);
DebouncedButton endOperation_Btn(gpio_Pin::gpio_PTE29,gpio_PullResistor::gpio_pullUpResistor);

DebouncedButton btnSum3(gpio_Pin::gpio_PTB9,gpio_PullResistor::gpio_pullUpResistor);
DebouncedButton btnSum7(gpio_Pin::gpio_PTB11,gpio_PullResistor::gpio_pullUpResistor);

//
mkl_GPIOPort door_Key(gpio_Pin::gpio_PTC7);
mkl_GPIOPort ledDoor(gpio_Pin::gpio_PTA1);
mkl_GPIOPort ledOp(gpio_Pin::gpio_PTB19);
mkl_GPIOPort buzzer(gpio_Pin::gpio_PTA2);

mkl_KeyboardParallelPort keyboard(gpio_PTA13, gpio_PTD5, gpio_PTD0, gpio_PTD2,
gpio_PTC12, gpio_PTC13, gpio_PTC16, gpio_PTC17); // Pinagem para o teclado


mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

/*Registradores tipo Int, ponteiros*/
registrador Us(0);
registrador Ds(0);
registrador Um(0);
registrador Dm(0);

//Serviços da História Teclado
controlador service_edit;
IncrementService service_inc;

char key;

// BTT
//sid_t estado;

// LCD
lcd_escreveVisor visorMain;
digTemp digit;

srvShow lcdm;
srvTemp tempr;
temp_divFreq f1Hz;

LED redLed(gpio_PTB18);
LED blueLed(gpio_PTD1);
//LED greenLed(gpio_PTB19);

int valor = 0;


extern "C" {
    void SysTick_Handler(void) {
    	keyboard.update();
        key = keyboard.getKey();
        if(keyboard.keyIsPressed()){
        	valor = key;
        }
        else{
        }

       // lcdm.printTime(tempr.int2Char(tempr.getMD()), tempr.int2Char(tempr.getMU()), tempr.int2Char(tempr.getSD()),
       //     			tempr.int2Char(tempr.getSU()));

        lcdm.printTime('1','1','1','1');
        lcdm.printOp(off,on);

        f1Hz.increment();

        if(f1Hz.isCarryOut() == true && tempr.isExecute() == true){
        	blueLed.turnOn();
        	//tempr.decrement();
        }

        else{
        	blueLed.turnOff();
        }
    }
}


void setup(){

	visorMain.config();
	lcdm.config(visorMain);
	tempr.config(digit);

	//---------------------------------------------------------------------- MOTOR H1 ---------------------------------------------------
	door_Key.setPortMode(gpio_PortMode::gpio_output);
	ledDoor.setPortMode(gpio_PortMode::gpio_output);
	ledOp.setPortMode(gpio_PortMode::gpio_output);
	buzzer.setPortMode(gpio_PortMode::gpio_output);

	ledOp.writeBit(0);

	//---------------------------------------------------------------------- TECLADO H2 -------------------------------------------------


}

int main(void)
{
	setup();

	Motor motorPeripheral(tpm_Pin::tpm_PTD4);

	SinalizationServiceController sinalizationController(buzzer,door_Key,ledDoor);
	MotorServiceController motorController(motorPeripheral);

	Monitor monitor(onOff_Btn,startPause_Btn,cancel_Btn,endOperation_Btn,sinalizationController,motorController, ledOp);

	monitor.setKeyboardObjects(keyboard, Us, Um, Ds, Dm, service_edit, service_inc,valor);

	monitor.setLCDObjects(lcdm,tempr,f1Hz);

	while (true) {
		monitor.readInputs(monitor.getState());
	}
    return 0;
}

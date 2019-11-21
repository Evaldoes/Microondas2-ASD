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

#include "MKL25Z4.h"
#include "h1/dsf_GPIO_ocp.h"
#include "h1/mkl_TPMDelay.h"
#include "h1/mkl_TPMPulseWidthModulation.h"
#include "h1/Led.h"
#include "h1/DebouncedButton.h"
#include "h1/Motor.h"

#include "h1/Monitor.h"
#include "h1/SinalizationServiceController.h"
#include "h1/MotorServiceController.h"

#define LOW 0
#define HIGH 1

/*
 * Criacao dos objetos perifericos
 */

// BOTOES

DebouncedButton startPause_Btn(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC1,PullResistor_t::PullUpResistor);
DebouncedButton cancel_Btn(GPIO_t::dsf_GPIOE,GPIO_t::dsf_PTE29,PullResistor_t::PullUpResistor);
DebouncedButton endOperation_Btn(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC2,PullResistor_t::PullUpResistor);

////// SINALIZADORES

dsf_GPIO_ocp door_Key(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC7);
dsf_GPIO_ocp ledDoor(GPIO_t::dsf_GPIOA,GPIO_t::dsf_PTA1);
dsf_GPIO_ocp buzzer(GPIO_t::dsf_GPIOB,GPIO_t::dsf_PTB19);

////// DIRECIONAIS MOTOR

dsf_GPIO_ocp inDriverRight(GPIO_t::dsf_GPIOC, GPIO_t::dsf_PTC13);
dsf_GPIO_ocp inDriverLeft(GPIO_t::dsf_GPIOC, GPIO_t::dsf_PTC12);

void setup(){

	door_Key.setPortMode(PortMode_t::Input);
	ledDoor.setPortMode(PortMode_t::Output);
	buzzer.setPortMode(PortMode_t::Output);
	ledDoor.writeBit(0);
	buzzer.writeBit(0);

	inDriverRight.setPortMode(PortMode_t::Output);
	inDriverLeft.setPortMode(PortMode_t::Output);

}

int main(void)
{
	setup();

	Motor motorPeripheral(tpm_Pin::tpm_PTD4,inDriverRight,inDriverLeft);

	SinalizationServiceController sinalizationController(buzzer,door_Key,ledDoor);
	MotorServiceController motorController(motorPeripheral);

	Monitor monitor(startPause_Btn,cancel_Btn,endOperation_Btn,sinalizationController,motorController);
	int teste = 0;

	while (true) {
		monitor.readInputs(monitor.getState());
	}
    return 0;
}

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
//#include "h1/mkl_TPM.h"
#include "h1/mkl_TPMDelay.h"
#include "h1/mkl_TPMPulseWidthModulation.h"
#include "h1/Led.h"
#include "h1/DebouncedButton.h"
#include "h1/Motor.h"


#define LOW 0
#define HIGH 1

/*
 * Criacao dos objetos perifericos
 */

// BOTOES E CHAVES

//dsf_GPIO_ocp startPause_btn(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC1);
//dsf_GPIO_ocp cancel_btn(GPIO_t::dsf_GPIOE,GPIO_t::dsf_PTE29);
//dsf_GPIO_ocp endOperation_btn(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC2);
//dsf_GPIO_ocp door_Key(GPIO_t::dsf_GPIOE,GPIO_t::dsf_PTE29);
//
////Debounce dos botoes
//
uint32_t low = LOW;
uint32_t high = HIGH;
//
DebouncedButton dsP_Btn(GPIO_t::dsf_GPIOC,GPIO_t::dsf_PTC1,high);
//
//// LED	BUZZER	MOTOR_PWM
//
//dsf_GPIO_ocp ledDoor(GPIO_t::dsf_GPIOA,GPIO_t::dsf_PTA1);
//dsf_GPIO_ocp buzzer(GPIO_t::dsf_GPIOA,GPIO_t::dsf_PTA2);
//
////Led doorSensor();
//Motor motor(tpm_Pin tpm_PTA13);
//
//void setup() {
//	Led doorSensor();
//}

int main(void)
{
	dsf_GPIO_ocp greenLed(GPIO_t::dsf_GPIOB, GPIO_t::dsf_PTB18);
	greenLed.setPortMode(PortMode_t::Output);
	dsP_Btn.getButtonPin().setPullResistor(PullResistor_t::PullUpResistor);
	mkl_TPMDelay delay(tpm_TPMNumberMask::tpm_TPM0);
	delay.setFrequency(tpm_Div::tpm_div32);

	greenLed.writeBit(0);

    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    while (1) {
    	delay.waitDelay(0XFFF);
    	if(dsP_Btn.getState() == dsP_Btn.Pressed) {
    		delay.waitDelay(0XFFFF);
    		delay.waitDelay(0xFFFF);
    		greenLed.toogleBit();
    	}
    }
    /* Never leave main */
    return 0;
}

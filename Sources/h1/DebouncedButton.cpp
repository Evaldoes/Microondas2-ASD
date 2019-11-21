/*
 * DebouncedButton.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: caiotelles
 */

#include "h1/DebouncedButton.h"
#include "h1/dsf_GPIO_ocp.h"
#include "h1/mkl_TPM.h"
#include "h1/mkl_TPMDelay.h"

#define LOW 0
#define HIGH 1

/*
 * Setup the class
 */
DebouncedButton::DebouncedButton() {

}

DebouncedButton::DebouncedButton(GPIO_t::dsf_GPIO GPIOName, GPIO_t::dsf_Pin pin, PullResistor_t::dsf_PullResistor pullResistor) {
	_pinBtt.setupPin(GPIOName,pin);
	_pinBtt.setPullResistor(pullResistor);
}

dsf_GPIO_ocp DebouncedButton::getButtonPin() {
	return _pinBtt;
}

/*
 * Get the current state
 */
bool DebouncedButton::getActivity() {
	mkl_TPMDelay delay(tpm_TPMNumberMask::tpm_TPM1);
	delay.setFrequency(tpm_Div::tpm_div128);

	if(_pinBtt.readBit() == 1) {
		delay.waitDelay(0xFFFF);
		status = pressed;
	}
	else {
		status = notPressed;
	}
	return status;
}


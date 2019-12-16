/*
 * DebouncedButton.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: caiotelles
 */

#include "base/DebouncedButton.h"

#define LOW 0
#define HIGH 1

/*
 * Setup the class
 */
DebouncedButton::DebouncedButton() {

}

DebouncedButton::DebouncedButton(gpio_Pin GPIOName, gpio_PullResistor pullResistor) {
	_pinBtt.setPin(GPIOName);
	_pinBtt.setPullResistor(pullResistor);
}

mkl_GPIOPort DebouncedButton::getButtonPin() {
	return _pinBtt;
}

/*
 * Get the current state
 */
bool DebouncedButton::getActivity() {
	mkl_TPMDelay delay(tpm_TPMNumberMask::tpm_TPM1);
	delay.setFrequency(tpm_Div::tpm_div128);

	if(_pinBtt.readBit() == 0) {
		delay.waitDelay(0xFFFF);
		delay.waitDelay(0xFFFF);
		delay.waitDelay(0xFFF);
		return true;
	}
	return false;
}


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

DebouncedButton::DebouncedButton(GPIO_t::dsf_GPIO GPIOName, GPIO_t::dsf_Pin pin,uint8_t pressedState_) {
	_pinBtt.setupPin(GPIOName,pin);
	_pressedState=pressedState_;
	_internalState=Idle;
	newTime = 0;
//	delay = new mkl_TPMDelay(tpm_TPMNumberMask::tpm_TPM0);
}

dsf_GPIO_ocp DebouncedButton::getButtonPin() {
	return _pinBtt;
}

/*
 * Get the current state
 */

DebouncedButton::ButtonState DebouncedButton::getState() {
	int newTime;
	uint8_t state;

	mkl_TPMDelay delay(tpm_TPMNumberMask::tpm_TPM0);
	delay.setFrequency(tpm_Div::tpm_div32);

	// read the pin and flip it if this switch reads high when open

	state=_pinBtt.readBit();
	if(_pressedState==LOW)
		state^=HIGH;

	// if state is low then wherever we were, we are now back at not pressed

	if(state==LOW)
	{
		_internalState=Idle;
		return NotPressed;
	}

	// sample the clock

	newTime += 1;

	// act on the internal state machine

	switch(_internalState)
	{
    	case Idle:
    		_internalState=DebounceDelay;
    		_lastTime=0;
    		break;

    	case DebounceDelay:
    		if(newTime-_lastTime>=DEBOUNCE_DELAY_MILLIS)
    		{
    			// been high for at least the debounce time: we are pressed
    			delay.waitDelay(0xFFFF);
    			delay.waitDelay(0xFFFF);
    			delay.waitDelay(0xFFFF);
    			newTime = 0;
    			return Pressed;
    		}
    		break;
  }

// nothing happened at this time

	return NotPressed;
}

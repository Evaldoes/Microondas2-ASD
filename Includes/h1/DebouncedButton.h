/*
 * DebouncedButton.h
 *
 *  Created on: Oct 12, 2019
 *      Author: caiotelles
 */

#ifndef DEBOUNCEDBUTTON_H_
#define DEBOUNCEDBUTTON_H_

#include <stdint.h>
#include "dsf_GPIO_ocp.h"
#include "h1/mkl_GPIOPort.h"
#include "mkl_TPM.h"
#include "mkl_TPMDelay.h"
//
// Button implementation that does software debouncing
//

class DebouncedButton
{
public:
	DebouncedButton();
	DebouncedButton(gpio_Pin GPIOName, gpio_PullResistor pullResistor);
	bool getActivity();
	mkl_GPIOPort getButtonPin();

	enum activity {
		notPressed = false,
		pressed = true
	};

private:
	bool status;
	mkl_GPIOPort _pinBtt;
};


#endif /* DEBOUNCEDBUTTON_H_ */

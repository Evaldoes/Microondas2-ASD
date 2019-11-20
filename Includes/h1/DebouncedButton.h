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
#include "mkl_TPM.h"
#include "mkl_TPMDelay.h"
//
// Button implementation that does software debouncing
//

class DebouncedButton
{
public:
	DebouncedButton();
	DebouncedButton(GPIO_t::dsf_GPIO GPIOName, GPIO_t::dsf_Pin pin, PullResistor_t::dsf_PullResistor pullResistor);
	bool getActivity();
	dsf_GPIO_ocp getButtonPin();

	enum activity {
		notPressed = false,
		pressed = true
	};

private:
	activity status;
	dsf_GPIO_ocp _pinBtt;
};


#endif /* DEBOUNCEDBUTTON_H_ */

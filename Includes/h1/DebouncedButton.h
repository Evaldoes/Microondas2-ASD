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

//
// Button implementation that does software debouncing
//

class DebouncedButton
{

private:
	// time to wait for bounce to clear
	static const uint32_t DEBOUNCE_DELAY_MILLIS=4;
	uint32_t newTime;

  // Internal button state
  enum InternalState
  {
    Idle,													// nothing happening
    DebounceDelay,								// delaying...
  };

  // The digital pin where the button is connected
  //uint8_t _digitalPin;
  dsf_GPIO_ocp _pinBtt;

  // The pressed state (HIGH/LOW)
  uint8_t _pressedState;

  // Internal state of the class
  InternalState _internalState;

  // The last time we sampled our button
  uint32_t _lastTime;

public:

  DebouncedButton(dsf_GPIO_ocp pinBtt_,uint8_t pressedState_);
		// Possible button states
    enum ButtonState
    {
      NotPressed,						// button is up
      Pressed,							// button is down
    };

  // Setup the class
  void setup(dsf_GPIO_ocp pinBtt_,uint8_t pressedState_);

  // Get the current state of the button
  ButtonState getState();
};


#endif /* DEBOUNCEDBUTTON_H_ */

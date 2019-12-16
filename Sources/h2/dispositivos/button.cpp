#include "button.h"

Button::Button(gpio_Pin pin) : mkl_port(pin) {
	mkl_port.setPortMode(gpio_input);
	mkl_port.setPullResistor(gpio_pullNoneResistor);
	State_t state = wait0;
}

bool Button::isOn(){

	bool b = !mkl_port.readBit();

	switch (state) {
	    case wait0:
	          if (b == 1){
	        	  state = wait1;
	          }
	          else {
	        	  state = wait0;
	          }
	          return 0;
	    case wait1:
	          if (b == 0) {
	        	  state = return_value;
	          }
	          else {
	        	  state = wait1;
	          }
	          return 0;
	    case return_value:
	          state = wait0;
	          return 1;

	}
	/*switch (state) {
	     case wait0: return 0;
	     case wait1: return 0;
	     case return_value: return 1;
	}*/
}

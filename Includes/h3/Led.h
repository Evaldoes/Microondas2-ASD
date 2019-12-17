#include "mkl_GPIOPort.h"

class Led {
private:
	mkl_GPIOPort port;
public:
	Led(gpio_Pin pin);
	void turnOn();
	void turnOff();
};

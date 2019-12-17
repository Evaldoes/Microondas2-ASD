#include "h3/Led.h"

Led::Led(gpio_Pin pin) : port(pin){
	port.setPortMode(gpio_output);
	port.writeBit(1);
}

void Led::turnOn() {
	port.writeBit(0); //Acende led
}

void Led::turnOff() {
	port.writeBit(1); //Apaga led
}

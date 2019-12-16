#include "led.h"

led::led(gpio_Pin pino) {
	pisca=mkl_GPIOPort(pino);
	pisca.setPortMode(gpio_output);
	pisca.writeBit(0);
}

void led::on(){
	pisca.writeBit(1);
}
void led::off(){
	pisca.writeBit(0);
}

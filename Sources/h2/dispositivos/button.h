#ifndef BUTTON_H
#define BUTTON_H

#include "bibliotecas/mkl_GPIOPort.h"

typedef enum {
    wait0,
    wait1,
    return_value
} State_t;

class Button {
private:
	mkl_GPIOPort mkl_port;
	State_t state;
public:
	Button(gpio_Pin pin);
	bool isOn();
};

#endif

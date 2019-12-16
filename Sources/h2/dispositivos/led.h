#include "../bibliotecas/mkl_GPIOPort.h"

class led {
	public:
		explicit led(gpio_Pin pino);
		void on();
		void off();
	private:
		mkl_GPIOPort pisca;
};

#include "../bibliotecas/mkl_GPIOPort.h"
#include "../bibliotecas/dsf_Delay_ocp.h"

typedef enum{
	wait_for_press=0,
	while_pressed=1,
	send_data=2
}estados;


class switche {
	public:
		explicit switche(gpio_Pin pino);
		int read();
		bool isOn();
	private:
		mkl_GPIOPort chave;
		estados atualState;
};

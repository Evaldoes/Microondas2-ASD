#include "h3/Bluetooth.h"
bool *ptrfull;
int *ptrbuffer;
mkl_HC06BluetoothSlave *ptrbt;

int tempbuf;

Bluetooth::Bluetooth(uart_PinTx_t pinTx,uart_PinRx_t pinRx): bt(pinTx,pinRx){
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();
	full = false;
	buffer = 0;
	ptrbuffer = &buffer;
	ptrfull = &full;
	ptrbt = &bt;
}

bool Bluetooth::wasData() {
	return full;
}

int Bluetooth::read() {
	tempbuf = buffer;
	buffer = 0;
	full = false;
	return tempbuf;
}

extern "C" {
	void UART0_IRQHandler(){
		*ptrfull = true;
		*ptrbuffer = ptrbt->receive8Bits();
	}
}

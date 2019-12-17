#include "base/mkl_HC06BluetoothSlave.h"

class Bluetooth {
private:
	int buffer;
	bool full;
	mkl_HC06BluetoothSlave bt;
public:
	Bluetooth(uart_PinTx_t pinTx,uart_PinRx_t pinRx);
	bool wasData();
	int read();
};

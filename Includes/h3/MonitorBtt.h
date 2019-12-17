#include "h3/DigitalFactory.h"
#include "h3/CookingService.h"
#include "h3/OperationService.h"
#include "h3/Bluetooth.h"
#include "h3/Led.h"
#include <stdio.h>

typedef enum{
	NoService = 0,
	Cooking,
	Operation,
}sid_t;

class MonitorBtt{
private:
	//sid_t sid;
	Led *ptrledon;//Led Verde
	Led *ptrledoff;//Led Vermelho
	OperationService *ops;
	CookingService *coz;
	DigitalFactory *factory;
	Bluetooth *bluetooth;
	int buff0;
	int buff1;
	int buff2;
	int buff3;
	int onoff;

public:
	MonitorBtt();
	void setup();
	void readInputs();
	sid_t selectService();
	void doService(sid_t next);
	void writeOutputs(sid_t sid);
	void doServiceFromIntr(sid_t sid);

};

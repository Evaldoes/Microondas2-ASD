//#include "digitalFactory.h"
#include "../digitais/registrador.h"
#include "dispositivos/decoder.h"

typedef enum{
	wait_for_full2=0,
	ask_permission=1,
	wait_permission2=2,
	load_value=3,
	end_state=4
}estados_incremento;


class IncrementService{

public:

	explicit IncrementService();
	void recebeIncremento(registrador *reg4,registrador *reg3,registrador *reg2,registrador *reg1);
	void machineState(bool b3, bool b7, bool arrived_permission);
	void selectService();
	void doService(registrador *reg4,registrador *reg3,registrador *reg2,registrador *reg1);


private:

	bool endService;
	bool permission;
	estados_incremento stateService;
	int valueIncrement;

	int servico;

};

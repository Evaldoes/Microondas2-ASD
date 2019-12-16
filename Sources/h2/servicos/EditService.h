#include "../digitais/registrador.h"
typedef enum{
	wait_for_full=0,
	wait_for_fim_full=1,
	sent_permission=2,
	wait_permission=3,
	arrived_permission=4,
	final=5,
}estados_service;

class controlador {
	public:
		explicit controlador();
		void maq_est(bool press, bool permission);
		void select_service();
		void do_service(registrador *four,registrador *three,registrador *two,registrador *one, int key);
	private:
		estados_service atual;
		int servico;
		bool pede_permissao;
		bool finish;
		bool contagem;
};

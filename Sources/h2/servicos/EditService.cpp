#include "EditService.h"

controlador::controlador() {
	atual=wait_for_full;
	servico=0;
	pede_permissao=0;
	finish=0;
	contagem=0;
}

void controlador::maq_est(bool press, bool permission){
	switch(atual){
		case wait_for_full:
			if(press){
				atual=wait_for_fim_full;
			}
			else{
				atual=wait_for_full;
			}
			break;
		case wait_for_fim_full:
			if(press){
				atual=wait_for_fim_full;
			}
			else{
				atual=sent_permission;
			}
			break;
		case sent_permission:
			atual=wait_permission;
			break;
		case wait_permission:
			if(permission){
				atual=arrived_permission;
			}
			else{
				atual=wait_permission;
			}
			break;
		case arrived_permission:
			atual=final;
			break;
		case final:
			atual=wait_for_full;
			break;
	}
}

void controlador::select_service(){
	if(atual==wait_for_full || atual==wait_for_fim_full){
		servico=0;
	}
	else if(atual==sent_permission || atual==wait_permission){
		servico=1;
	}
	else if(atual==arrived_permission){
		servico=2;
	}
	else{
		servico=3;
	}
}

void controlador::do_service(registrador *four,registrador *three,registrador *two,registrador *one,int key){
	if(servico==0){
		pede_permissao=0;
		finish=0;
	}
	else if(servico==1){
		pede_permissao=1;
		finish=0;
	}
	else if(servico==2){
		pede_permissao=0;
		finish=0;
		four->atualiza(three->leValor());
		three->atualiza(two->leValor());
		two->atualiza(one->leValor());
		one->atualiza(key);
	}
	else if(servico==3){
		pede_permissao=0;
		finish=1;
	}
}

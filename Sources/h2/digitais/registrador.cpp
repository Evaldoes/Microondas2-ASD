#include "registrador.h"

registrador::registrador(int valor){
	valor=0;
}

void registrador::atualiza (int valorNovo){
	valor = valorNovo;
}

int registrador::leValor(){
	return valor;
}

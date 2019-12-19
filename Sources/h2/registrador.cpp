#include "h2/registrador.h"

registrador::registrador(){}

registrador::registrador(int valor){
	valor=0;
}

void registrador::atualiza (int valorNovo){
	valor = valorNovo;
}

int registrador::leValor(){
	return valor;
}

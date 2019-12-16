
#ifndef REGISTRADOR_H_
#define REGISTRADOR_H_

class registrador {
	public:
		explicit registrador(int valor);
		void atualiza(int valorNovo);
		int leValor();

	private:
		int valor;
};

#endif


#ifndef REGISTRADOR_H_
#define REGISTRADOR_H_

class registrador {
	public:
		registrador();
		explicit registrador(int valor);
		void atualiza(int valorNovo);
		int leValor();

	private:
		int valor;
};

#endif

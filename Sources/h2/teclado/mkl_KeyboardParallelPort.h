/*!
 * @copyright   © 2019 Universidade Federal do Amazonas.
 *
 * @brief       Interface da API em C++ da classe mãe KeyboardParallelPort.
 *
 * @file        mkl_KeyboardParallelPort.h
 * @version     1.0
 * @date        04 março 2019
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (04 Março 2019): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Daniel Modesto de Souza <daniel.modesto.dmds@gmail.com>
 *
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "../bibliotecas/mkl_GPIOPort.h"
#include "MKL25Z4.h"

class mkl_KeyboardParallelPort{
 public:

	mkl_KeyboardParallelPort(gpio_Pin pL0, gpio_Pin pL1, gpio_Pin pL2,gpio_Pin pL3, gpio_Pin pC0, gpio_Pin pC1, gpio_Pin pC2, gpio_Pin pC3);

	 /*!
	   * Método que verifica se uma chave foi pressionada.
	   */
	bool keyIsPressed();

	 /*!
	   * Método que retorna a chave pressionada.
	   */
	char getKey();

	 /*!
	   * Método que atualiza a leitura do teclado.
	   */
	void update();

private:
	/*!
	  * Variável de armazenamento da chave.
	  */
	char key;

	/*!
	  * Objetos instanciados da classe mkl_GPIOPort.
	  */
	mkl_GPIOPort L0, L1, L2, L3, C0, C1, C2, C3;
};



/*!
 * @copyright   © 2019 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para  o System Tick Timer (MKL25Z).
 *
 * @file        mkl_Systick.h
 * @version     1.0
 * @date        31 Janeiro 2019
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   Systick - System Tick Timer.
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (31 Janeiro 2019): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Victoria da Silva Leite <victoria.vl73@gmail.com>
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


#ifndef MKL_SYSTICK_H_
#define MKL_SYSTICK_H_

#include <MKL25Z4.h>
#include <stdint.h>

/* !
 *	Definição dos possíveis valores de clock
 */
typedef enum {
    clock2Mhz = 0 ,  //!< System clock system divided by 16
    clock42Mhz = 1   //!< System clock
} systick_clockSource;


/*!
 *  @class    mkl_Systick
 *
 *  @brief    A classe mkl_Systick representa o periférico System Tick Timer da MKL25Z.
 *
 *  @details  Esta classe é usada para a geração temporizações.
 *
 *  @section  EXAMPLES USAGE
 *
 *   Uso dos métodos para o uso do Systick
 *     +fn setClockSource(systick_clockSource clock);
 *     +fn setReload(uint32_t reloadValue);
 *     +fn enableCounter();
 *     +fn disableCounter();
 *     +fn clearCounter();
 *     +fn enableInterrupt();
 *     +fn disableInterrupt();
 *     +fn setRegister();
 */
class mkl_Systick {
 public:
	/*!
	 * Métodos de configuração do systick
	 */
    void setClockSource(systick_clockSource clock);
    void setReload(uint32_t reloadValue);
    void enableCounter();
    void disableCounter();
    void clearCounter();
	/*!
	 * Métodos que configuram a interrupção
	 */
    void enableInterrupt();
    void disableInterrupt();

 private:
	/*!
     * Método interno para endereçar os registradores
	 */
    void setRegister();

	/*!
	 *  Endereço no mapa de memória do Control and Status Register
	 */
    volatile unsigned int *addrSTCSR;

	/*!
	 *  Endereço no mapa de memória do Reload Value Register
	 */
    volatile unsigned int *addrSTRVR;

	/*!
	 *  Endereço no mapa de memória do Current Value Register
     */
    volatile unsigned int *addrSTCVR;

	/*!
	 *  Endereço no mapa de memória do Calibration Value Register
	 */
    volatile unsigned int *addrSTCALIB;
};

#endif  // MKL_SYSTICK_H_

/*!
 * @copyright   © 2019 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para  o System Tick Timer (MKL25Z).
 *
 * @file        mkl_SystickPeriodicInterrupt.h
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
#ifndef MKL_SYSTICKPERIODICINTERRUPT_H_
#define MKL_SYSTICKPERIODICINTERRUPT_H_

#include <stdint.h>
#include "mkl_Systick.h"

/*!
 * Enum associado os níveis de prioridade do TPM.
 */
typedef enum {
  systick_priority0 = 0,
  systick_priority1 = 1,
  systick_priority2 = 2,
  systick_priority3 = 3
} st_Priority_t;

/*!
 *  @class    mkl_GPIOPort.
 *
 *  @brief    A classe implementa o periférico GPIO sem interrupção.
 *
 *  @details  Esta classe é derivada da classe mãe "mkl_GPIO" e implementa
 *            o periférico GPIO com o modo de operação sem interrupção.
 *
 */

/*!
 *  @class    mkl_Systick
 *
 *  @brief    A classe mkl_Systick representa o periférico System Tick Timer da MKL25Z.
 *
 *  @details  Esta classe é derivada da classe mãe "mkl_Systick.h" e implementa a interrupção
 *  		  do systick.
 *
 *  @section  EXAMPLES USAGE
 *
 *   Uso dos métodos para o uso do Systick
 *     +fn mkl_SystickPeriodicInterrupt(uint32_t time_ms, systick_clockSource clock);
 *     +fn enableInterruptRequest();
 *     +fn disableInterruptRequest();
 *     +fn setPriority(st_Priority_t priority);
 *     +fn getPriority();
 *     +fn reloadValue(uint32_t time_ms, systick_clockSource clock);
 */
class mkl_SystickPeriodicInterrupt: public mkl_Systick {
 public:
	/*!
	 * Construtor padrão da classe.
	 */
    mkl_SystickPeriodicInterrupt(uint32_t time_ms, systick_clockSource clock);
	/*!
	 * Métodos que configuram a interrupção
	 */
    void enableInterruptRequest();
    void disableInterruptRequest();
    void setPriority(st_Priority_t priority);
    st_Priority_t getPriority();

 private:
	/*!
	 * Método interno para calcular o valor de reload relativo ao tempo em milisegundos.
	 */
    uint32_t reloadValue(uint32_t time_ms, systick_clockSource clock);
};

#endif  // MKL_SYSTICKPERIODICINTERRUPT_H_

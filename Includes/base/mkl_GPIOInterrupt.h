/*!
* @copyright   © 2017 Universidade Federal do Amazonas.
*
* @brief       Uma API em C++ de interrupções para GPIO.
*
* @file        mkl_GPIOInterrupt.h
* @version     1.0
* @date        6 Julho 2017
*
* @section     HARDWARES & SOFTWARES
*              +board        FRDM-KL25Z da NXP.
*              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
*              +compiler     Kinetis® Design Studio IDE
*              +manual       L25P80M48SF0RM, Rev.3, September 2012
*              +revisions    Versão (data): Descrição breve.
*                             ++ 1.0 (30 Julho 2017): Versão inicial.
*
* @section     AUTHORS & DEVELOPERS
*              +institution  Universidade Federal do Amazonas
*              +courses      Engenharia da Computação / Engenharia Elétrica
*              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
*              +student      Versão inicial:
*                             ++ José Luis da Silva <joseluis70123@gmail.com>
*
* @section     LICENSE
*
*              GNU General Public License (GNU GPL)
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

#ifndef _HOME_GUILHERME_GPIOINTERRUPT_MKL_GPIOINTERRUPT_H_
#define _HOME_GUILHERME_GPIOINTERRUPT_MKL_GPIOINTERRUPT_H_

#include "mkl_GPIO.h"

typedef enum {
  gpio_whenLogicZero = 0b1000 << 16,
  gpio_onRisingEdge = 0b1001 << 16,
  gpio_onFallingEdge = 0b1010 << 16,
  gpio_onEitherEdge = 0b1011 << 16,
  gpio_whenLogicOne = 0b1100 << 16
} gpio_InterruptTrigger;

/*!
*  @class    mkl_GPIOInterrupt.
*
*  @brief    A classe implementa o periférico GPIO com interrupção.
*
*  @details  Esta classe é derivada da classe mãe "mkl_GPIO" e implementa
*            o periférico GPIO com o modo de operação com interrupção.
*
*/
class mkl_GPIOInterrupt: public mkl_GPIO {
 public:
 /*!
 * Construtor padrão classe.
 */
  explicit mkl_GPIOInterrupt(gpio_Pin pin = gpio_PTA1);
 /*!
 * Métodos que tratam da interrupção.
 */
  void getInterruptFlag();
  bool thisGpioTriggedIntr();
  void clearInterruptFlag();
  void enableInterrupt(gpio_InterruptTrigger interruptTrigger);
  void disableInterrupt();

 protected:
  volatile uint32_t *addressPortxISFR;

 private:
  uint32_t ISFR;
  IRQn_Type PORTx_IRQn;
  uint8_t bitPosition;
};
#endif  //  _HOME_GUILHERME_GPIOINTERRUPT_MKL_GPIOINTERRUPT_H_

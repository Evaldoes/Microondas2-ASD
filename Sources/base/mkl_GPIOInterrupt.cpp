/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Implementação da API de interrupção em C++ para GPIO.
 *
 * @file        mkl_GPIOInterrupt.cpp
 * @version     2.0
 * @date        4 Mar 2019
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (30 Julho 2017): Versão inicial.
 *                             ++ 2.0 (4 Março 2019): Versão final.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ José Luis da Silva <joseluis70123@gmail.com>
 *                            Versão final:
 *                             ++ Guilherme Souza da Silva
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
// CHANGE TO YOUR DIRECTORY!
#include "mkl_GPIOInterrupt.h"

/*!
 *   @brief    Construtor padrão da classe.
 *
 *   O construtor padrãa classe obtém o número do pino e do GPIO a partir
 *   do pino desejado, associa fisicamento o objeto de software ao periféco
 *   de hardware, habilita o clock do GPIO e seleciona o modo GPIO de operação
 *   do pino.
 *
 *   @remarks  Siglas e páginas do Manual de Referêia KL25:
 *             - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */

mkl_GPIOInterrupt::mkl_GPIOInterrupt(gpio_Pin pin) {
  uint32_t pinNumber;
  uint32_t gpio;
  setGPIOParameters(pin, gpio, pinNumber);

  bindPeripheral(gpio, pinNumber);
  enableModuleClock(gpio);
  selectMuxAlternative();

  // Configure the ISFR port address and the correspondent
  // bit number to the port
  // 0x000 -> gpio_GPIOA or
  // 0x300 -> gpio_GPIOD
  if ( gpio == 0x000 ) {
    addressPortxISFR =  (volatile uint32_t *)0x400490A0;
    PORTx_IRQn = PORTA_IRQn;
  } else if ( (pin & 0xFF0) == 0x300 ) {
    addressPortxISFR =  (volatile uint32_t *)0x4004C0A0;
    PORTx_IRQn = PORTD_IRQn;
  }

  bitPosition = pinNumber;
}

/*!
 *   @brief      Recupera a flag de interrupção, indicando quais pinos sofreram interrupção neste instante.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *                - PortxPCRn: Pin Control Register.Pág. 183(Mux) and 185(Pull).
 */
void mkl_GPIOInterrupt::getInterruptFlag() {
  ISFR = *addressPortxISFR;
}

/*!
 *   @brief      Limpa a fl	ag de interrupção
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *                - PortxPCRn: Pin Control Register.Pág. 183(Mux) and 185(Pull).
 */
void mkl_GPIOInterrupt::clearInterruptFlag() {
  *addressPortxISFR |= ~ISFR;
}

/*!
 *   @brief      Verifica se o gpio correspondente foi disparado
 *	 @return
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *                - PortxPCRn: Pin Control Register.Pág. 183(Mux) and 185(Pull).
 */
bool mkl_GPIOInterrupt::thisGpioTriggedIntr() {
  return *addressPortxISFR & ( 0x1 << bitPosition );
}


/*!
 *   @brief      habilita as interrupções das GPIOS para operar.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */
void mkl_GPIOInterrupt::enableInterrupt
  (gpio_InterruptTrigger interruptTrigger) {
  // Inicializa o campo IRQC e mantem o restante inalterado
  *addressPortxPCRn &= ~0xF0000;

  // Configura o tipo de interrupcao
  *addressPortxPCRn |= interruptTrigger;

  // Habilita a interrupcaoo para a porta correspondente
  NVIC_EnableIRQ(PORTx_IRQn);
}

/*!
 *
 *   @brief      Desabilita as interrupções das GPIOS para pararem de funcionar.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */
void mkl_GPIOInterrupt::disableInterrupt() {
  // Zera o campo IRQC;
  *addressPortxPCRn |= 0x00000;

  // Desabiliza a interrupcao
  NVIC_DisableIRQ(PORTx_IRQn);
}

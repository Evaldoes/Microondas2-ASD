/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       API em C++ para o periférico TPM, no modo delay.
 *
 * @file        dsf_Delay_ocp.h
 * @version     1.0
 * @date        31 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   TPM.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (6 Julho 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas.
 *              +courses      Engenharia da Computação / Engenharia Elétrica.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Hamilton Nascimento <hdan_neto@hotmail.com>
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

 
#include <stdint.h>
#include "dsf_Delay_ocp.h"


/*!
 *   @fn       dsf_Delay_ocp
 *
 *   @brief    Método construtor da classe.
 *
 *   Método construtor da classe, que inicializa os atributos do objeto.
 *
 *   @param[in]  tpm - periférico TPM a ser associado ao objeto de software.
 */
dsf_Delay_ocp::dsf_Delay_ocp(TPM_t::TPMNumber_t tpm) {
  uint8_t *baseAddress;

  baseAddress = (uint8_t *)(TPM0_BASE + 0x1000*tpm);
  bindPeripheral(baseAddress);
  enablePeripheralClock(tpm);
}


/*!
 *   @fn       setFrequency
 *
 *   @brief    Método de ajuste da frequência de operação.
 *
 *   Método que ajusta a frequência de operação do delay.
 *
 *   @param[in]  divBase - constante de divisão do divisor de frequência.
 */
void dsf_Delay_ocp::setFrequency(TPMDiv_t::TPMDiv divBase) {
  freqDiv = divBase;
}


/*!
 *   @fn       startDelay
 *
 *   @brief    Inicia a operação do periférico TPM no modo delay.
 *
 *   Método que inicia um delay de duração especificada.
 *
 *   @param[in] cycles - número de ciclos de relógio da operação.
 *
 *   @details   Este método não "prende", i.e., o método apenas inicia a
 *              contagem do temporizador.
 *
 *              O parâmetro "cycles" não corresponde ao tempo, em segundos,
 *              da temporização iniciada.
 *              A equação que relaciona o parâmetro "cycles" ao tempo,
 *              em segundos, é dada por:
 *
 *              cycles = T*(20.97*10^6)/divBase,
 *
 *              onde:
 *              - T       : tempo em segundos;
 *              - divBase : fator de divisão configurado no método
 *                          setFrequency;
 *              - cycles  : ciclos de relógio.
 *
 *              Note o maior valor do parâmetro deverá ser de 65535, que
 *              é o maior valor em decimal que se obtém com 16 bits.
 *              65535 é o fundo de escala do registrador TPM_CNT.
 */
void dsf_Delay_ocp::startDelay(uint16_t cycles) {
  /*!
   * Desabilita a contagem.
   */
  *addressTPMxSC = 0;
  /*!
   * Reseta o contador CNT.
   */
  *addressTPMxCNT = 0;
  /*!
   * Ajusta o fundo de escala do registrador "Modulo".
   */
  *addressTPMxMOD = cycles;
  /*!
   * Ajusta o valor de divisão.
   */
  *addressTPMxSC |= freqDiv;
  /*!
   * Limpa a flag de término TOF do registrador Status Counter.
   */
  *addressTPMxSC |= 0x80;
  /*!
   * Habilita a contagem.
   */
  *addressTPMxSC |= 0x08;
}


/*!
 *   @fn       timeoutDelay
 *
 *   @brief    Indica a ocorrência do término de temporização.
 *
 *   Método que indica se o tempo especificado pelo
 *
 *   @param[in]  divBase - constante de divisão do divisor de frequência.
 */
int dsf_Delay_ocp::timeoutDelay() {
  if (*addressTPMxSC & 0x80) {
    return 1;
  }
  return 0;
}


/*!
 *   @fn       waitDelay
 *
 *   @brief    Inicia a operação do periférico TPM no modo delay.
 *
 *   Método que inicia um delay de duração especificada.
 *
 *   @param[in] cycles - número de ciclos de relógio da operação.
 *
 *   @details   Este método aguarda até que o valor de temporização desejado
 *              se esgote.
 *
 *              O parâmetro "cycles" não corresponde ao tempo, em segundos,
 *              da temporização iniciada.
 *              A equação que relaciona o parâmetro "cycles" ao tempo,
 *              em segundos, é dada por:
 *
 *              cycles = T*(20.97*10^6)/divBase,
 *
 *              onde:
 *              - T       : tempo em segundos;
 *              - divBase : fator de divisão configurado no método
 *                          setFrequency;
 *              - cycles  : ciclos de relógio.
 *
 *              Note o maior valor do parâmetro deverá ser de 65535, que
 *              é o maior valor em decimal que se obtém com 16 bits.
 *              65535 é o fundo de escala do registrador TPM_CNT.
 */
void dsf_Delay_ocp::waitDelay(uint16_t cycles) {
  startDelay(cycles);
  do {} while (timeoutDelay() != 1);
}


/*!
 *   @fn       cancelDelay
 *
 *   @brief    Cancela uma temporização em andamento.
 *
 *   Método que cancela uma temporização iniciada, parando o contador.
 */
void dsf_Delay_ocp::cancelDelay() {
  *addressTPMxSC = 0;
}


/*!
 *   @fn       getCounter
 *
 *   @brief    Método que informa o valor atual da contagem.
 *
 *   Método que informa o valor atual do contador do temporizador.
 *
 *   @param[in]  value - variável passada por referência que será atualizada
 *                       com o valor corrente do contador do temporizador.
 */
void dsf_Delay_ocp::getCounter(uint16_t *value) {
  *value = *addressTPMxCNT;
}

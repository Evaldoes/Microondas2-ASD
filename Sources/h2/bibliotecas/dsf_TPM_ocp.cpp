/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Implementação da classe mãe "dsf_TPMPeripheral_ocp".
 *
 * @file        dsf_TPM_ocp.cpp
 * @version     1.0
 * @date        02 Agosto 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   TPM.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (02 Agosto 2017): Versão inicial.
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

#include "dsf_TPM_ocp.h"

/*!
 *   @fn         bindPeripheral
 *
 *   @brief      Associa o objeto de software ao periférico de hardware.
 *
 *   Este método associa ao objeto de software o periférico de hardware,
 *   utilizando a inicialização dos ponteiros para os endereços de memória
 *   dos registradores correspondentes.
 *
 *   @param[in]  baseAddress - o endereço base do periférico TPM.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxSC: Status Control Register. Pág. 552.
 *               - TPMxCNT: Counter Register. Pág.554.
 *               - TPMxMOD: Modulo Register. Pág. 554.
 */

void dsf_TPMPeripheral_ocp::bindPeripheral(uint8_t *baseAddress) {
  addressTPMxSC = (volatile uint32_t *)(baseAddress);
  addressTPMxCNT = (volatile uint32_t *)(baseAddress + 0x4);
  addressTPMxMOD = (volatile uint32_t *)(baseAddress + 0x8);
}

/*!
 *   @fn         bindChannel
 *
 *   @brief      Associa o canal do objeto de software ao hardware
 *
 *   Este método associa os atributos do canal do objeto de software ao
 *   seu correspondente do periférico hardware.
 *
 *   @param[in]  baseAddress - o endereço base do periférico TPM.
 *               chnNumber - o número do canal do periférico TPM.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - TPMxCnV: Channel Value Register. Pág.557.
 *               - TPMxCnSC: Channel Status Control Register. Pág.555.
 */
void dsf_TPMPeripheral_ocp::bindChannel(uint8_t *baseAddress,
                                        uint8_t chnNumber) {
  addressTPMxCnV = (volatile uint32_t *)(baseAddress + 0x10 + 8*chnNumber);
  addressTPMxCnSC = (volatile uint32_t *)(baseAddress + 0xC + 8*chnNumber);
}


/*!
 *   @fn         bindPin
 *
 *   @brief      Associa o pino do objeto ao periférico de hardare.
 *
 *   Este método associa o pino do objeto de software ao pino do periférico.
 *
 *   @param[in]  pinNumber - o número do pino do objeto de software.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. Pág.183.
 */
void dsf_TPMPeripheral_ocp::bindPin(uint8_t GPIONumber, uint8_t pinNumber) {
  addressPortxPCRn = (volatile uint32_t *)(0x40049000
                                          + 0x1000*GPIONumber + 4*pinNumber);
}


/*!
 *   @fn         enablePeripheralClock
 *
 *   @brief      Habilita o clock do periférico de hardware.
 *
 *   Este método habilita o clock do periférico TPM solicitado.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - SCGC6: System Control Gating Clock Register 6. Pág.207.
 *               - SOPT2: System Options Register 2. Pág.195.
 */
void dsf_TPMPeripheral_ocp::enablePeripheralClock(uint8_t TPMNumber) {
  SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK << TPMNumber;
  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
}

/*!
 *   @fn         enableGPIOClock
 *
 *   @brief      Habilita o clock do GPIO do pino.
 *
 *   Este método habilita o clock do periférico GPIO do pino passado por
 *   parâmetro.
 *
 *   @param[in]  GPIONumber - o número do GPIO correspondente ao pino.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - SCGC5: System Control Gating Clock Register 5. Pág.199.
 */
void dsf_TPMPeripheral_ocp::enableGPIOClock(uint8_t GPIONumber) {
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK << GPIONumber;
}

/*!
 *   @fn         selectMuxAlternative
 *
 *   @brief      Seleciona a alternativa de trabalho do pino.
 *
 *   Este método seleciona o modo de operação do pino correspondente para o
 *   modo de operação TPM.
 *
 *   @param[in]  muxAlt - alternativa de operação do pino para o canal e TPM
 *                        especificados.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PCR: Pin Control Register. Pág.183.
 */
void dsf_TPMPeripheral_ocp::selectMuxAlternative(uint8_t muxAlt) {
  *addressPortxPCRn = PORT_PCR_MUX(muxAlt);
}

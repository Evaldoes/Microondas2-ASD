/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Interface da classe mãe "dsf_TPMPeripheral_ocp".
 *
 * @file        dsf_TPM_ocp.h
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

#ifndef DSF_TPM_OCP_H_
#define DSF_TPM_OCP_H_

#include <MKL25Z4.h>
#include <stdint.h>

/*!
 * Namespace associado à mascara do GPIO, canal, TPM e alternativa do mux PCR.
 */
namespace Pin {
  enum GPIOMask_t {
    dsf_GPIOA = 0,
    dsf_GPIOB = 1<<5,
    dsf_GPIOC = 2<<5,
    dsf_GPIOD = 3<<5,
    dsf_GPIOE = 4<<5
  };

  enum TPMChnMask_t {
    dsf_CH0 = 0,
    dsf_CH1 = 1<<8,
    dsf_CH2 = 2<<8,
    dsf_CH3 = 3<<8,
    dsf_CH4 = 4<<8,
    dsf_CH5 = 5<<8
  };

  enum TPMMask_t {
    dsf_TPM0 = 0,
    dsf_TPM1 = 1<<11,
    dsf_TPM2 = 2<<11
  };

  enum muxAltMask {
    dsf_Alt3 = 3<<13,
    dsf_Alt4 = 4<<13
  };
}  //  namespace Pin

/*!
 * Namespace associado ao fator de divisão do divisor de frequência.
 */
namespace TPMDiv_t {
  enum TPMDiv {Div1 = 0, Div2, Div4, Div8, Div16, Div32, Div64, Div128};
}

/*!
 * Namespace associado à borda de transição de detecção.
 */
namespace TPMEdge_t {
  enum TPMEdge {Falling = 1, Rising, Both};
}  //  namespace TPMEdge_t

/*!
 * Namespace associado ao periférico TPM e seus pinos correspondentes.
 */
namespace TPM_t {
  enum TPMNumber_t {
    dsf_TPM0 = 0,
    dsf_TPM1 = 1,
    dsf_TPM2 = 2
  };

  enum Pin_t {
    dsf_TPM0_PTA0 = 0|Pin::dsf_GPIOA|Pin::dsf_CH5|Pin::dsf_Alt3,
    dsf_TPM0_PTA3 = 3|Pin::dsf_GPIOA|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM0_PTA4 = 4|Pin::dsf_GPIOA|Pin::dsf_CH1|Pin::dsf_Alt3,
    dsf_TPM0_PTA5 = 5|Pin::dsf_GPIOA|Pin::dsf_CH2|Pin::dsf_Alt3,
    dsf_TPM0_PTC1 = 1|Pin::dsf_GPIOC|Pin::dsf_CH0|Pin::dsf_Alt4,
    dsf_TPM0_PTC2 = 2|Pin::dsf_GPIOC|Pin::dsf_CH1|Pin::dsf_Alt4,
    dsf_TPM0_PTC3 = 3|Pin::dsf_GPIOC|Pin::dsf_CH2|Pin::dsf_Alt4,
    dsf_TPM0_PTC4 = 4|Pin::dsf_GPIOC|Pin::dsf_CH3|Pin::dsf_Alt4,
    dsf_TPM0_PTC8 = 8|Pin::dsf_GPIOC|Pin::dsf_CH4|Pin::dsf_Alt3,
    dsf_TPM0_PTC9 = 9|Pin::dsf_GPIOC|Pin::dsf_CH5|Pin::dsf_Alt3,
    dsf_TPM0_PTD0 = 0|Pin::dsf_GPIOD|Pin::dsf_CH0|Pin::dsf_Alt4,
    dsf_TPM0_PTD1 = 1|Pin::dsf_GPIOD|Pin::dsf_CH1|Pin::dsf_Alt4,
    dsf_TPM0_PTD2 = 2|Pin::dsf_GPIOD|Pin::dsf_CH2|Pin::dsf_Alt4,
    dsf_TPM0_PTD3 = 3 |Pin::dsf_GPIOD|Pin::dsf_CH3|Pin::dsf_Alt4,
    dsf_TPM0_PTD4 = 4|Pin::dsf_GPIOD|Pin::dsf_CH4|Pin::dsf_Alt4,
    dsf_TPM0_PTD5 = 5|Pin::dsf_GPIOD|Pin::dsf_CH5|Pin::dsf_Alt4,
    dsf_TPM0_PTE29 = 29|Pin::dsf_GPIOE|Pin::dsf_CH2|Pin::dsf_Alt3,
    dsf_TPM0_PTE30 = 30|Pin::dsf_GPIOE|Pin::dsf_CH3|Pin::dsf_Alt3,
    dsf_TPM1_PTA12 = 12|Pin::dsf_GPIOA|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM1_PTA13 = 13|Pin::dsf_GPIOA|Pin::dsf_CH1|Pin::dsf_Alt3,
    dsf_TPM1_PTB0 = 0|Pin::dsf_GPIOB|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM1_PTB1 = 1|Pin::dsf_GPIOB|Pin::dsf_CH1|Pin::dsf_Alt3,
    dsf_TPM1_PTE20 = 20|Pin::dsf_GPIOE|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM1_PTE21 = 21|Pin::dsf_GPIOE|Pin::dsf_CH1|Pin::dsf_Alt3,
    dsf_TPM2_PTA1 = 1|Pin::dsf_GPIOA|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM2_PTA2 = 2|Pin::dsf_GPIOA|Pin::dsf_CH1|Pin::dsf_Alt3,
    dsf_TPM2_PTE22 = 22|Pin::dsf_GPIOE|Pin::dsf_CH0|Pin::dsf_Alt3,
    dsf_TPM2_PTE23 = 23|Pin::dsf_GPIOE|Pin::dsf_CH1|Pin::dsf_Alt3
  };
}  //  namespace TPM_t

/*!
 *  @class    dsf_TPMPeripheral_ocp.
 *
 *  @brief    A classe mãe "dsf_TPMPeripheral_ocp" representa o periférico TPM.
 *
 *  @details  Esta classe é utilizada como classe mãe para os periféricos que
 *            estão associados ao TPM, como o dsf_Delay_ocp, dsf_Measure_ocp,
 *            dsf_EventCounter_ocp, dsf_PWM_ocp.
 */
class dsf_TPMPeripheral_ocp {
 protected:
  /*!
   * Endereços dos registradores associados ao periférico TPM e seus canais.
   */
  volatile uint32_t *addressTPMxSC;
  volatile uint32_t *addressTPMxMOD;
  volatile uint32_t *addressTPMxCNT;
  volatile uint32_t *addressTPMxCnV;
  volatile uint32_t *addressTPMxCnSC;
  volatile uint32_t *addressPortxPCRn;

  /*!
   * Métodos de bind do periférico, dos seus canais e do pino escolhido.
   */
  void bindPeripheral(uint8_t*);
  void bindChannel(uint8_t*, uint8_t);
  void bindPin(uint8_t, uint8_t);

  /*!
   * Métodos de habilitação de clock do periférico e da porta.
   */
  void enablePeripheralClock(uint8_t);
  void enableGPIOClock(uint8_t);
  /*!
   * Método de seleção do mux do pino.
   */
  void selectMuxAlternative(uint8_t);
};

#endif

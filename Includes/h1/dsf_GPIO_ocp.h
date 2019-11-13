/*!
 * @copyright   � 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programa��o de aplica��es em C++ para GPIO.
 *
 * @file        dsf_GPIO_ocp.h
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +peripheral   GPIO.
 *              +compiler     Kinetis� Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Vers�o (data): Descri��o breve.
 *                             ++ 1.0 (30 Julho 2017): Vers�o inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computa��o / Engenharia El�trica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Vers�o inicial:
 *                             ++ Hamilton Nascimento <hdan_neto@hotmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa � um software livre; Voc� pode redistribu�-lo
 *              e/ou modific�-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              vers�o 3 da licen�a, ou qualquer vers�o posterior.
 *
 *              Este programa � distribu�do na esperan�a de que seja �til,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia impl�cita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROP�SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#ifndef DSF_GPIO_OCP_H_
#define DSF_GPIO_OCP_H_

#include <stdint.h>
#include <MKL25Z4.h>

/*!
 * Namespace de defini��o dos GPIOs e pinos implementados.
 */
namespace GPIO_t {
  enum dsf_GPIO {
    dsf_GPIOA = 0,
    dsf_GPIOB = 1,
    dsf_GPIOC = 2,
    dsf_GPIOD = 3,
    dsf_GPIOE = 4
  };
  enum dsf_Pin {
    dsf_PTA1 = 1,
    dsf_PTA2 = 2,
    dsf_PTA4 = 4,
    dsf_PTA5 = 5,
    dsf_PTA12 = 12,
    dsf_PTA13 = 13,
    dsf_PTA17 = 17,
    dsf_PTB0 = 0,
    dsf_PTB1 = 1,
    dsf_PTB2 = 2,
    dsf_PTB3 = 3,
    dsf_PTB8 = 8,
    dsf_PTB9 = 9,
    dsf_PTB10 = 10,
    dsf_PTB11 = 11,
    dsf_PTB18 = 18,
    dsf_PTB19 = 19,
    dsf_PTC0 = 0,
    dsf_PTC1 = 1,
    dsf_PTC2 = 2,
    dsf_PTC3 = 3,
    dsf_PTC4 = 4,
    dsf_PTC5 = 5,
    dsf_PTC6 = 6,
    dsf_PTC7 = 7,
    dsf_PTC8 = 8,
    dsf_PTC9 = 9,
    dsf_PTC10 = 10,
    dsf_PTC11 = 11,
    dsf_PTC12 = 12,
    dsf_PTC13 = 13,
    dsf_PTC14 = 14,
    dsf_PTC15 = 15,
    dsf_PTC16 = 16,
    dsf_PTC17 = 17,
    dsf_PTD0 = 0,
    dsf_PTD1 = 1,
    dsf_PTD2 = 2,
    dsf_PTD3 = 3,
    dsf_PTD4 = 4,
    dsf_PTD5 = 5,
    dsf_PTD6 = 6,
    dsf_PTD7 = 7,
    dsf_PTE0 = 0,
    dsf_PTE1 = 1,
    dsf_PTE3 = 3,
    dsf_PTE4 = 4,
    dsf_PTE5 = 5,
    dsf_PTE20 = 20,
    dsf_PTE21 = 21,
    dsf_PTE22 = 22,
    dsf_PTE23 = 23,
    dsf_PTE29 = 29
  };
}  // namespace GPIO_t

/*!
 * Namespace de defini��o dos tipos de pull resistor.
 */
namespace PullResistor_t {
  enum dsf_PullResistor {
    PullNoneResistor = 0,
    PullUpResistor = 3
  };
}  //  namespace PullResistor_t

/*!
 * Namespace de defini��o dos modos de opera��o do pino.
 */
namespace PortMode_t {
  enum dsf_PortMode {
    Input  = 0,
    Output = 1
  };
}  //  namespace PortMode_t

/*!
 *  @class    dsf_GPIO_ocp
 *
 *  @brief    Classe de implementa��o do perif�rico GPIO para a placa KL25Z128.
 *
 *  @details  Esta classe � usada para leitura ou escrita de dados bin�rios
 *            e usa o perif�rico on-chip GPIOA a GPIOE.
 *
 *  @section  EXAMPLES USAGE
 *
 *            Uso dos m�todos como porta de entrada.
 *	           +fn setPortMode(PortMode_t::Input);
 *	           +fn setPullResistor(PullResistor_t::PullNoneResistor);
 *             +fn setPullResistor(dsf_PullUp);
 *             +fn data = readBit();
 *
 *            Uso dos m�todos como porta de sa�da.
 *	           +fn setPortMode(PortMode_t::Output);
 *             +fn writeBit(data);
 */
class dsf_GPIO_ocp {
 public:
  /*!
   * M�todo construtor padr�o da classe.
   */
  explicit dsf_GPIO_ocp(GPIO_t::dsf_GPIO GPIOName, GPIO_t::dsf_Pin pin);
  /*!
   * M�todos de configura��o do pino.
   */
  void setPortMode(PortMode_t::dsf_PortMode mode);
  void setPullResistor(PullResistor_t::dsf_PullResistor pull);
  /*!
   * M�todos de escrita no pino.
   */
  void writeBit(int bit);
  void toogleBit();
  /*!
   * M�todo de leitura do pino.
   */
  int readBit();

 private:
  /*!
   * Endere�o do registrador PDDR no mapa de mem�ria.
   */
  volatile uint32_t *addressPDDR;
  /*!
   * Endere�o do registrador PDOR no mapa de mem�ria.
   */
  volatile uint32_t *addressPDOR;
  /*!
   * Endere�o do registrador PDIR no mapa de mem�ria.
   */
  volatile uint32_t *addressPDIR;
  /*!
   * Endere�o do registrador PTOR no mapa de mem�ria.
   */
  volatile uint32_t *addressPTOR;
  /*!
   * Endere�o do registrador Port PCR no mapa de mem�ria.
   */
  volatile uint32_t *addressPortxPCRn;
  /*!
   * M�scara do pino correspondente para uso nas opera��es de
   * configura��o, leitura e escrita.
   */
  volatile uint32_t pinPort;
  /*!
   * M�todos privados de inicializa��o do perif�rico.
   */
  void bindPeripheral(uint8_t GPIONumber, uint8_t pinNumber);
  void enableModuleClock(uint8_t GPIONumber);
  void selectMuxAlternative();
};

#endif  //  GPIO_OCP_H_

/*
 * Monitor.h
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_MONITOR_H_
#define SOURCES_H1_MONITOR_H_

#include "base/DebouncedButton.h"
//#include "h1/mkl_GPIOPort.h"

//FRAMEWORK E DEBOUNCE PARA AS HISTORIAS
#include "base/mkl_GPIOPort.h"
#include "base/mkl_TPMDelay.h"
#include "base/mkl_TPMPulseWidthModulation.h"
#include "base/DebouncedButton.h"
#include "base/mkl_KeyboardParallelPort.h"
#include "base/mkl_SystickPeriodicInterrupt.h"

#include "base/variables.h"


//---------------------------------------------------------------------- MOTOR H1 ---------------------------------------------------
#include "h1/Motor.h"
//#include "h1/Monitor.h"
#include "h1/SinalizationServiceController.h"
#include "h1/MotorServiceController.h"


//---------------------------------------------------------------------- TECLADO H2 -------------------------------------------------
#include "h2/led.h"
#include "h2/switch.h"
#include "h2/displaySegments.h"
#include "h2/EditService.h"
#include "h2/IncrementService.h"


//---------------------------------------------------------------------- BTT H3 ------------------------------------------------------
//#include "h3/MonitorBtt.h"


//---------------------------------------------------------------------- LCD H4 ------------------------------------------------------
#include "h4/srvShow.h"
#include "h4/LED.h"
#include "h4/temp_divFreq.h"
#include "h4/srvTemp.h"
#include "h4/types.h"

#define KBD 1
#define BTT 0
#define WAIT 2

enum opStates{
	offOp,
	onOp,
	standbyOp,			//aguardando inicio ou retomada da operacao
	operatingOp,			// temporizador em decrescimo
	pausedOp				//botão de pause ou porta aberta
};

class Monitor {
public:
	Monitor(DebouncedButton _onOff,DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
			SinalizationServiceController _sinalizationCtrl,
			MotorServiceController _motorCtrl, mkl_GPIOPort _ledOp);
	virtual ~Monitor();
	void readInputs(opStates situation);
	void doOff(),doOn(),doStandBy(),doOperating(),doPaused();
	void setState(opStates operationState), setValor(int value);
	opStates getState();

	void setKeyboardObjects(mkl_KeyboardParallelPort _keyboard, registrador _uS,registrador _uM,registrador _dS,
			registrador _dM,controlador _editService,IncrementService _incService, int _valor);
//	void setBluetoothObjects(MonitorBtt _monitorBtt);
	void setLCDObjects(srvShow _screenLCD, srvTemp _timerCounter, temp_divFreq _frequency);
	int editingPermission, getValue();

private:
	int valor;
	DebouncedButton onOff,startPause, cancel, endOp;
	opStates status;

	SinalizationServiceController sinalizationCtrl;
	MotorServiceController motorCtrl;

	mkl_GPIOPort ledOp;

	mkl_KeyboardParallelPort keyboard;
	registrador uS, uM, dS, dM;
	controlador editService;
	IncrementService incService;

//	MonitorBtt monitorBtt;

	srvShow screenLCD;
	srvTemp timerCounter;
	temp_divFreq frequency;
};

#endif /* SOURCES_H1_MONITOR_H_ */

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

#include "h1/Motor.h"
#include "h1/SinalizationServiceController.h"
#include "h1/MotorServiceController.h"

#include "h2/displaySegments.h"
#include "h2/EditService.h"
#include "h2/IncrementService.h"

enum operationStates{
	off,
	standby,			//aguardando inicio ou retomada da operacao
	operating,			// temporizador em decrescimo
	paused				//botão de pause ou porta aberta
};
class Monitor {
public:
	Monitor(DebouncedButton _onOff,DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
			SinalizationServiceController _sinalizationCtrl,
			MotorServiceController _motorCtrl, mkl_GPIOPort _ledOp);
	virtual ~Monitor();
	void readInputs(operationStates situation);
	void doOff(),doStandBy(),doOperating(),doPaused();
	void setState(operationStates operationState);
	operationStates getState();

	void setKeyboardObjects(mkl_KeyboardParallelPort _keyboard, registrador _uS,registrador _uM,registrador _dS,
			registrador _dM,controlador _editService,IncrementService _incService);

private:
	DebouncedButton onOff,startPause, cancel, endOp;
	operationStates status;

	SinalizationServiceController sinalizationCtrl;
	MotorServiceController motorCtrl;

	mkl_GPIOPort ledOp;

	mkl_KeyboardParallelPort keyboard;
	registrador uS, uM, dS, dM;
	controlador editService;
	IncrementService incService;
};

#endif /* SOURCES_H1_MONITOR_H_ */

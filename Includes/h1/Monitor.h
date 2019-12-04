/*
 * Monitor.h
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_MONITOR_H_
#define SOURCES_H1_MONITOR_H_

#include "h1/DebouncedButton.h"
#include "h1/mkl_GPIOPort.h"
#include "h1/Motor.h"

#include "h1/SinalizationServiceController.h"
#include "h1/MotorServiceController.h"

enum operationStates{
	standby,			//aguardando inicio ou retomada da operacao
	operating,			// temporizador em decrescimo
	paused				//botão de pause ou porta aberta
};
class Monitor {
public:
	Monitor(DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
			SinalizationServiceController _sinalizationCtrl,
			MotorServiceController _motorCtrl, mkl_GPIOPort _ledOp);
	virtual ~Monitor();
	void readInputs(operationStates situation);
	void doStandBy(),doOperating(),doPaused();
	void setState(operationStates operationState);
	operationStates getState();
private:
	DebouncedButton startPause, cancel, endOp;
	operationStates status;

	SinalizationServiceController sinalizationCtrl;
	MotorServiceController motorCtrl;

	mkl_GPIOPort ledOp;

};

#endif /* SOURCES_H1_MONITOR_H_ */

/*
 * Monitor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Monitor.h"

Monitor::Monitor(DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
		SinalizationServiceController _sinalizationCtrl,MotorServiceController _motorCtrl, mkl_GPIOPort _ledOp) {
	// TODO Auto-generated constructor stub
	startPause = _startPause;
	cancel = _cancel;
	endOp = _endOp;
	sinalizationCtrl = _sinalizationCtrl;
	motorCtrl = _motorCtrl;
	ledOp = _ledOp;

	status = standby;
}

Monitor::~Monitor() {
	// TODO Auto-generated destructor stub
}

operationStates Monitor::getState() {
	return status;
}

void Monitor::setState(operationStates operationState) {
	status = operationState;
}

void Monitor::readInputs(operationStates situation) {
	switch (situation) {
	case standby:
		ledOp.writeBit(1);
		doStandBy();
		break;
	case operating:
		ledOp.writeBit(0);
		doOperating();
		break;
	case paused:
		ledOp.writeBit(1);
		doPaused();
		break;
	default:
		break;
	}
}

void Monitor::doStandBy() {
	motorCtrl.getMotor().disable();
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = operating;
		}
	}
}

void Monitor::doOperating(){
	motorCtrl.getMotor().powerConfig();
	motorCtrl.getMotor().keepEnable(true);
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = paused;
		}
		if (cancel.getActivity()) {
			status = standby;
		}
		if (endOp.getActivity()) {
			motorCtrl.getMotor().disable();
			sinalizationCtrl.callEndOfOperation();
			status = standby;
		}
	}
	else {
		status = paused;
	}
}

void Monitor::doPaused() {
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = operating;
		}
		else if (cancel.getActivity()) {
			status = standby;
		}
	}
	else {
		sinalizationCtrl.getDoorLed().writeBit(1);
		if (cancel.getActivity()) {
			status = standby;
		}
	}
	motorCtrl.getMotor().disable();
}



/*
 * Monitor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Monitor.h"

Monitor::Monitor(DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
		SinalizationServiceController _sinalizationCtrl,MotorServiceController _motorCtrl) {
	// TODO Auto-generated constructor stub
	startPause = _startPause;
	cancel = _cancel;
	endOp = _endOp;
	sinalizationCtrl = _sinalizationCtrl;
	motorCtrl = _motorCtrl;
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
		doStandBy();
		break;
	case operating:
		doOperating();
		break;
	case paused:
		doPaused();
		break;
	default:
		break;
	}
}

void Monitor::doStandBy() {
	motorCtrl.getMotor().disable();
	if (sinalizationCtrl.isDoorClosed()) {
		sinalizationCtrl.getDoorLed().writeBit(0);
		if (startPause.getActivity()) {
			status = operating;
		}
	}
	else {sinalizationCtrl.getDoorLed().writeBit(1);}
}

void Monitor::doOperating(){
	motorCtrl.getMotor().powerConfig();
	motorCtrl.getMotor().keepEnable(true);
	if (sinalizationCtrl.isDoorClosed()) {
		sinalizationCtrl.getDoorLed().writeBit(0);
		if (startPause.getActivity()) {
			status = paused;
		}
		else if (cancel.getActivity()) {
			status = standby;
		}
		else if (endOp.getActivity()) {
			sinalizationCtrl.callEndOfOperation();
			status = standby;
		}
	}
	else {
		sinalizationCtrl.getDoorLed().writeBit(1);
		status = paused;
	}
}

void Monitor::doPaused() {
	motorCtrl.getMotor().disable();
	if (sinalizationCtrl.isDoorClosed()) {
		sinalizationCtrl.getDoorLed().writeBit(0);
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
}



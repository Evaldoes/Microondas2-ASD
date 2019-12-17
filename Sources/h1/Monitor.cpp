/*
 * Monitor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Monitor.h"
#include "../../main.cpp"

Monitor::Monitor(DebouncedButton _onOff,DebouncedButton _startPause, DebouncedButton _cancel, DebouncedButton _endOp,
		SinalizationServiceController _sinalizationCtrl,MotorServiceController _motorCtrl, mkl_GPIOPort _ledOp) {
	// TODO Auto-generated constructor stub
	onOff = _onOff;
	startPause = _startPause;
	cancel = _cancel;
	endOp = _endOp;
	sinalizationCtrl = _sinalizationCtrl;
	motorCtrl = _motorCtrl;
	ledOp = _ledOp;

	status = off;
}

void Monitor::setKeyboardObjects(mkl_KeyboardParallelPort _keyboard, registrador _uS,registrador _uM,registrador _dS,
			registrador _dM,controlador _editService,IncrementService _incService) {
	keyboard = _keyboard;
	uS = _uS;
	uM = _uM;
	dS = _dS;
	dM = _dM;
	editService = _editService;
	incService = _incService;
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
	case off:
		ledOp.writeBit(1);
		doOff();
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

void Monitor::doOff(){
	if(onOff.getActivity()) {
		status = standby;
	}
}

void Monitor::doStandBy() {
	motorCtrl.getMotor().disable();
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = operating;
		}
	}
	if (onOff.getActivity()) {
		status = off;
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



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
	status = operationStates::standby;
}

Monitor::~Monitor() {
	// TODO Auto-generated destructor stub
}

void Monitor::readInputs() {
	switch (status) {
		case standby:
			if (startPause.getState()==startPause.Pressed && sinalizationCtrl.isDoorClosed()) {
				//enableTimer();
				motorCtrl.enableDisablePower();
				status = operationStates::operating;
			}
			// SE CLICAR EM CANCEL MANDA UM CLEAR();
			break;
		case operating:
			if (!sinalizationCtrl.isDoorClosed()) {
				status = paused;
			}
			else {
				if (startPause.getState()==startPause.Pressed) {
					//disableTimer();
					status = paused;
				}
				if (cancel.getState()==cancel.Pressed) {
					//disableTimer();
					//clear();
					status = standby;
				}
				if (endOp.getState()==endOp.Pressed) {
					//disableTimer();
					sinalizationCtrl.callEndOfOperation();
					status = standby;
				}
			}
			motorCtrl.enableDisablePower();
			break;
		case paused:
			if (startPause.getState()==startPause.Pressed && sinalizationCtrl.isDoorClosed()) {
				//enableTimer();
				motorCtrl.enableDisablePower();
				status = operating;
			}
			if (cancel.getState()==cancel.Pressed) {
				//disableTimer();
				//clear();
				status = standby;
			}
			break;
		default:
			status = standby;
			break;
	}
}




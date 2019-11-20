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
			if (sinalizationCtrl.isDoorClosed()) {
				//enableTimer();
				motorCtrl.enableDisablePower(startPause.getActivity());
				status = operationStates::operating;
			}
			// SE CLICAR EM CANCEL MANDA UM CLEAR();
			break;
		case operating:
			if (!sinalizationCtrl.isDoorClosed()) {
				status = paused;
				motorCtrl.enableDisablePower(true);
			}
			else {
				if (startPause.getActivity()) {
					//disableTimer();
					status = paused;
				}
				if (cancel.getActivity()) {
					//disableTimer();
					//clear();
					status = standby;
				}
				if (endOp.getActivity()) {
					//disableTimer();
					sinalizationCtrl.callEndOfOperation();
					status = standby;
				}
				motorCtrl.enableDisablePower(true);
			}
			break;
		case paused:
			if (sinalizationCtrl.isDoorClosed()) {
				//enableTimer();
				motorCtrl.enableDisablePower(startPause.getActivity());
				status = operating;
			}
			if (cancel.getActivity()) {
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




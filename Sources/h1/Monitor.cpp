/*
 * Monitor.cpp
 *
 *  Created on: 16/11/2019
 *      Author: caio_
 */

#include "h1/Monitor.h"

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

	status = offOp;

	editingPermission = WAIT;
}

void Monitor::setKeyboardObjects(mkl_KeyboardParallelPort _keyboard, registrador _uS,registrador _uM,registrador _dS,
			registrador _dM,controlador _editService,IncrementService _incService, int _valor) {
	keyboard = _keyboard;
	uS = _uS;
	uM = _uM;
	dS = _dS;
	dM = _dM;
	editService = _editService;
	incService = _incService;
	valor = _valor;
}

//void Monitor::setBluetoothObjects(MonitorBtt _monitorBtt) {
//	monitorBtt = _monitorBtt;
//}

void Monitor::setLCDObjects(srvShow _screenLCD, srvTemp _timerCounter, temp_divFreq _frequency) {
	screenLCD = _screenLCD;
	timerCounter = _timerCounter;
	frequency = _frequency;
}

Monitor::~Monitor() {
	// TODO Auto-generated destructor stub
}

opStates Monitor::getState() {
	return status;
}

void Monitor::setState(opStates operationState) {
	status = operationState;
}

void Monitor::readInputs(opStates situation) {
	switch (situation) {
	case offOp:
		ledOp.writeBit(1);
		doOff();
	case onOp:
		ledOp.writeBit(1);
		doOn();
	case standbyOp:
		ledOp.writeBit(1);
		doStandBy();
		break;
	case operatingOp:
		ledOp.writeBit(0);
		doOperating();
		break;
	case pausedOp:
		ledOp.writeBit(1);
		doPaused();
		break;
	default:
		break;
	}
}

void Monitor::doOff(){
	if(onOff.getActivity()) {
		status = onOp;
	}
}

void Monitor::doOn() {
	screenLCD.clean();
	screenLCD.printOp(sinalizationCtrl.isDoorClosed(),off);
	if (keyboard.keyIsPressed()){
		status = standbyOp;
		editingPermission = KBD;
	}
	else {
//		monitorBtt.readInputs();
//		estado = monitorBtt.selectService();
//		if (estado != NoService) {
//			status = standby;
//			editingPermission = BTT;
		}

}

void Monitor::doStandBy() {
	motorCtrl.getMotor().disable();
	screenLCD.clean();
	screenLCD.printOp(sinalizationCtrl.isDoorClosed(),off);
	if (editingPermission == KBD) {
		screenLCD.printCoz(edicao);
		editService.maq_est(true,true);
		editService.select_service();
		editService.do_service(&dM,&uM,&dS,&uS,valor);
	}
	else if (editingPermission == BTT) {
//		monitorBtt.doService(estado);
//		monitorBtt.writeOutputs(estado);
	}

	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = operatingOp;
		}
	}
	if (onOff.getActivity()) {
		status = onOp;
	}
}

void Monitor::doOperating(){
	motorCtrl.getMotor().powerConfig();
	motorCtrl.getMotor().keepEnable(true);
	timerCounter.play();
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = pausedOp;
		}
		if (cancel.getActivity()) {
			status = standbyOp;
		}
		if (timerCounter.isEot()) {
			motorCtrl.getMotor().disable();
			sinalizationCtrl.callEndOfOperation();
			status = standbyOp;
		}
	}
	else {
		status = pausedOp;
	}
}

void Monitor::doPaused() {
	timerCounter.pause();
	if (sinalizationCtrl.isDoorClosed()) {
		if (startPause.getActivity()) {
			status = operatingOp;
		}
		else if (cancel.getActivity()) {
			status = standbyOp;
		}
	}
	else {
		if (cancel.getActivity()) {
			status = standbyOp;
		}
	}
	motorCtrl.getMotor().disable();
}



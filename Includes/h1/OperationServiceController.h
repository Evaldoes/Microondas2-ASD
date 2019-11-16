/*
 * OperationServiceController.h
 *
 *  Created on: 12/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_OPERATIONSERVICECONTROLLER_H_
#define SOURCES_H1_OPERATIONSERVICECONTROLLER_H_

enum operation_State{
	inOperation,
	paused,
	standBy,
};

class OperationServiceController {
public:
	OperationServiceController();
	virtual ~OperationServiceController();
};

#endif /* SOURCES_H1_OPERATIONSERVICECONTROLLER_H_ */

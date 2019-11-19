/*
 * OperationServiceController.h
 *
 *  Created on: 17/11/2019
 *      Author: caio_
 */

#ifndef SOURCES_H1_OPERATIONSERVICECONTROLLER_H_
#define SOURCES_H1_OPERATIONSERVICECONTROLLER_H_

#include "h1/Motor.h"

enum Status {
	waiting,
	working
};

class OperationServiceController {
public:
	OperationServiceController();
	virtual ~OperationServiceController();
};

#endif /* SOURCES_H1_OPERATIONSERVICECONTROLLER_H_ */

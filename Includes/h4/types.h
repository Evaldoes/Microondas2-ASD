/*
 * types.h
 *
 *  Created on: 12/12/2019
 *      Author: Nader Hauache
 */

#ifndef SOURCES_TYPES_H_
#define SOURCES_TYPES_H_

typedef enum{
	edicao = 0,
	pizza = 1,
	pipoca = 2,
	lasanha = 3,
	inc3 = 4,
	inc5 = 5,
	inc7 = 6
}cozimentotype;

typedef enum {
	on = true,
	off = false
}onOfftype;

typedef enum{
	setTime = 0,
	setPreCoz = 1,
	setInc = 2,
	printTime = 3,
	printOp = 4,
	printState = 5
}sid ;

enum operationStates{
	standby,			//aguardando inicio ou retomada da operacao
	decrementing,		// temporizador em decrescimo
	paused				//botão de pause ou porta aberta
};

/*
 * typedef enum{
	piz = 1,
	pip = 2,
	las = 3,
}cozimento;
 */





#endif /* SOURCES_TYPES_H_ */

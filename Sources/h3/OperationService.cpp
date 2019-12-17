#include "OperationService.h"
#include "DigitalFactory.h"

int temp2;

OperationService::OperationService(void* ptrf){
	ptrfac = ptrf;
}
void OperationService::setup(int* ptronoff){
	ptrdec = (*(DigitalFactory*)ptrfac).getptrdec();
	ptrreg = (*(DigitalFactory*)ptrfac).getptrreg();
	result = ptronoff;
}

void OperationService::doService(int data) {
	temp2 = (*(Decoder*)ptrdec).doDecode(data);
	(*(Register*)ptrreg).loadQ(temp2);
	*result=((*(Register*)ptrreg).getQ3());
}

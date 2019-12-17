#include "CookingService.h"
#include "DigitalFactory.h"

int temp;

CookingService::CookingService(void* ptrf){
	ptrfac = ptrf;
}
void CookingService::setup(int* data0,int* data1,int* data2,int* data3){
	ptrdec = (*(DigitalFactory*)ptrfac).getptrdec();
	ptrreg = (*(DigitalFactory*)ptrfac).getptrreg();
	buffer0 = data0;
	buffer1 = data1;
	buffer2 = data2;
	buffer3 = data3;
}

void CookingService::doService(int data) {
	temp = (*(Decoder*)ptrdec).doDecode(data);
	(*(Register*)ptrreg).loadQ(temp);
	*buffer0 = (*(Register*)ptrreg).getQ0();
	*buffer1 = (*(Register*)ptrreg).getQ1();
	*buffer2 = (*(Register*)ptrreg).getQ2();
	*buffer3 = (*(Register*)ptrreg).getQ3();
}

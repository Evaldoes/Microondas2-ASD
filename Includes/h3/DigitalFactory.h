#include "Decoder.h"
#include "Register.h"

class DigitalFactory {
private:
	Decoder* ptrdec;
	Register* ptrreg;
public:
	DigitalFactory();
	bool createDecoder();
	bool createRegister();
	Decoder* getptrdec();
	Register* getptrreg();
};

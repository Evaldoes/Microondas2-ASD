class OperationService{
private:
	void* ptrfac;
	void* ptrdec;
	void* ptrreg;
	int *result; //LIGA-DESLIGA
public:
	OperationService(void* ptrf);
	void setup(int* ptronoff);
	void doService(int data);
};

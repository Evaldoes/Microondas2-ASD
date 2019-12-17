class CookingService{
private:
	void* ptrfac;
	void* ptrdec;
	void* ptrreg;
	int* buffer0;//MENOS SIGNIFICATIVO
	int* buffer1;
	int* buffer2;
	int* buffer3;//MAIS SIGNIFICATIVO
public:
	CookingService(void* ptrf);
	void setup(int* data0,int* data1,int* data2,int* data3);
	void doService(int data);
};


//#include "lcd_Led.h"
#include <MKL25Z4.H>
#include <stdio.h>
#include "h4/srvShow.h"
#include "h4/LED.h"
#include "h4/temp_divFreq.h"
#include "h4/srvTemp.h"
#include "h4/types.h"

LED redLed(gpio_PTB18);
LED blueLed(gpio_PTD1);
LED greenLed(gpio_PTB19);

srvShow lcdm;
srvTemp tempr;
temp_divFreq f1Hz;
int i = 0;

extern "C" {
    void SysTick_Handler(void){

    	lcdm.printTime(tempr.int2Char(tempr.getMD()), tempr.int2Char(tempr.getMU()), tempr.int2Char(tempr.getSD()),
    			tempr.int2Char(tempr.getSU()));
    	lcdm.printOp(off,on);

    	f1Hz.increment();

    	if(f1Hz.isCarryOut() == true && tempr.isExecute() == true){
    		blueLed.turnOn();
    		tempr.decrement();
    		if(i < 40){
    		    		i++;
    		    	}

    		    	if (i == 40){
    		    		tempr.putPreCoz(pizza);
    		    		lcdm.printCoz(pizza);
    		    		i++;
    		    	}
    	}

        else{
   	        blueLed.turnOff();
        }
    }
}

int main() {

	tempr.putTime(0,1,3,0);
	tempr.play();
	lcdm.printCoz(edicao);

	while(true){

		if(tempr.isEot() == true){
			redLed.turnOn();
		}

	}


  return 0;
}

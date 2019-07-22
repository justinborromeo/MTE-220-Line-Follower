#include "mte220.c"

void rampDown(void){
    SetLeft(2700);
    SetRight(4300);
    Delay(50);
    SetLeft(2900);
    SetRight(4100);
    Delay(50);
    SetLeft(3100);
    SetRight(3900);
    Delay(50);
    SetLeft(3300);
    SetRight(3700);
    Delay(50);
    SetLeft(3530);
    SetRight(3520);
}

void rampUp(void){    
    SetLeft(3500);
    SetRight(3500);
	LongDelay(8);
	SetLeft(3300);
    SetRight(3700);
	LongDelay(8);
    SetLeft(3100);
    SetRight(3900);
	LongDelay(8);
    SetLeft(2900);
    SetRight(4100);
	LongDelay(8);
	SetLeft(2700);
    SetRight(4300);
}

void main(void)
{
    uns8 ir_analog_value; 
    uns8 hall_effect_analog_value; 
    
    Initialization();

    // both servos are turned on
    UseServos         // (syntax of "call" is correct without () or ;)
    uns8 high_count = 0;
    uns8 low_count = 0;
    WaitForButton();  // wait until the button is pushed
    while (1)
    {
        ir_analog_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp
        hall_effect_analog_value = AnalogConvert(ADC_HALL_EFFECT);
        if ( ir_analog_value < 0x55 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
        {
            // left servo only
            LeftServoOn
            RightServoOff
        }
        else if ( ir_analog_value > 0x80 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
        {
            // right servo only
            RightServoOn
            LeftServoOff
        }
        else
        {
            // both servos on
            LeftServoOn
	    LongDelay(2);
	    RightServoOn
        }
	if (hall_effect_analog_value > 156) {
	    high_count = high_count + 1;
	    low_count = 0;
	} else if (hall_effect_analog_value < 110) {
 	    low_count = low_count + 1;
	    high_count = 0;
	} else {
	    high_count = 0;
	    low_count = 0;
	}
	
	if (low_count >= 12) {
	    low_count = 0;
	    // positive polarity - on for 7 seconds
	    LeftServoOff
	    LongDelay(2);
	    RightServoOff
            OnLED
	    LongDelay(56);
            OffLED
	    uns8 isOffMagnet = 0;
	    while(isOffMagnet == 0) {   
		ir_analog_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp
       	    	hall_effect_analog_value = AnalogConvert(ADC_HALL_EFFECT);
		if ( ir_analog_value < 0x55 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
        	{
            		// left servo only
            		LeftServoOn
            		RightServoOff
        	}
        	else if ( ir_analog_value > 0x80 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
        	{
            		// right servo only
            		RightServoOn
         	   	LeftServoOff
        	}
        	else
        	{
            		// both servos on
  			LeftServoOn
	    		LongDelay(2);
	    		RightServoOn
        	}
		if (hall_effect_analog_value < 156 && hall_effect_analog_value > 110) {
			isOffMagnet = 1;
		}
	    }
            // Move forward off magnet
	} else if (high_count >= 12) {
	    high_count = 0;
	    rampDown();
            uns8 count = 0;
	    while (count<4) {
	        OnLED
		LongDelay(8);
		OffLED;
		LongDelay(8);
		count = count+1;
	    }
	    uns8 isOffMagnet = 0;
	    while(isOffMagnet == 0) {   
		ir_analog_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp
       	    	hall_effect_analog_value = AnalogConvert(ADC_HALL_EFFECT);
		if ( ir_analog_value < 0x55 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
        	{
            		// left servo only
            		LeftServoOn
            		RightServoOff
        	}
        	else if ( ir_analog_value > 0x80 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
        	{
            		// right servo only
            		RightServoOn
         	   	LeftServoOff
        	} else {
            		// both servos on
            		LeftServoOn
	    		LongDelay(2);
	    		RightServoOn
        	}
		if (hall_effect_analog_value < 156 && hall_effect_analog_value > 110) {
			isOffMagnet = 1;
		}
	    }
	    // Move forward off magnet
	} else {
	    OffLED
	}       
    }
}














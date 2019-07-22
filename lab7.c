//
// Created by jborromeo on 2018-11-19.
//

void main(void)
{
    uns8 ir_analog_value; 
    uns8 hall_effect_analog_value; 
    
    Initialization();

    // both servos are turned on
    UseServos         // (syntax of "call" is correct without () or ;)
    
    WaitForButton();  // wait until the button is pushed

    while (1)
    {
        ir_analog_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp
        hall_effect_analog_value = AnalogConvert(ADC_HALL_EFFECT);
        if ( ir_analog_value < 0x66 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
        {
            // left servo only
            LeftServoOn
            RightServoOff
        }
        else if ( ir_analog_value > 0x99 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
        {
            // right servo only
            RightServoOn
            LeftServoOff
        }
        else
        {
            // both servos on
            BothServosOn
        }
    }

    }
}

// TODO Write Magnet Delay Code
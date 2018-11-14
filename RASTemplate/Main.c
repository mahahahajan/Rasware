#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>


#include <RASLib/inc/adc.h>
#include <RASLib/inc/motor.h>

// Blink the LED to show we're on
tBoolean blink_on = true;
static tBoolean initialized = false;
static tMotor *left1;
static tMotor *right1;
static tMotor *left2;
static tMotor *right2;

static tADC *adc[4];





// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    left1 = InitializeServoMotor(PIN_B6, true);
    left2 = InitializeServoMotor(PIN_B7, true);
    right1 = InitializeServoMotor(PIN_D6, true);
    right2 = InitializeServoMotor(PIN_D7, true);

    /* this keeps going forward 
        SetMotor(left1, 1.0);
        SetMotor(left2, 1.0);
        SetMotor(right2, -1.0);
        SetMotor(right1, -1.0);
    */



    initGPIOLineSensor();

    lineSense();


    gpioLineSensorDemo();
   
}

void lineSense() {
    while(1){
        if(ADCRead(adc[1]) > 0){
            SetPin(PIN_F2, true);
            Printf(
            "Line Sensor values: %1.3f,  %1.3f,  %1.3f\r",
            ADCRead(adc[1]),
            ADCRead(adc[2]),
            ADCRead(adc[3])
            );
    Printf("\n");
        }

        
        else if(ADCRead(adc[1]) > .4){
             SetPin(PIN_F1, true);
             Printf(
            "Line Sensor values:  %1.3f\r",
            ADCRead(adc[1])
            );
    Printf("\n");
        }

    
    }
}

void initGPIOLineSensor(){
    if(initialized){
        return;
    }
    initialized = true;

    //set four pins for ADC input - you can use these 4 I/O pins or select your own
    adc[0] = InitializeADC(PIN_D0);
    adc[1] = InitializeADC(PIN_D1);
    adc[2] = InitializeADC(PIN_D2);
    adc[3] = InitializeADC(PIN_D3);
}


void gpioLineSensorDemo(){
    Printf("Press any key to quit\n");

    //loop until key is pressed
    while(!KeyWasPressed()){
        Printf(
            "Line Sensor values:  %1.3f,  %1.3f,  %1.3f,  %1.3f\r",
            ADCRead(adc[0]),
            ADCRead(adc[1]),
            ADCRead(adc[2]),
            ADCRead(adc[3])
            );
    }
    Printf("\n");
}
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
    
    right1 = InitializeServoMotor(PIN_B7, true);
    right2 = InitializeServoMotor(PIN_B6, true);

    left1 = InitializeServoMotor(PIN_C6, true);
    left2 = InitializeServoMotor(PIN_C7, true);
    

    initGPIOLineSensor();   
    //initDistanceSensor
    //IRSensorDemo();
    sumoBot();

    /* this keeps going forward 
        
    */



    

    //lineSense();


    //gpioLineSensorDemo();
   
}
void IRSensorDemo(void){
    Printf("Press any key to quit\n");
    
    //loop until key is pressed
    while(!KeyWasPressed()){
        Printf(
            "Line Sensor values:  %1.3f\r",
            ADCRead(adc[1]) * 100);
    }
    Printf("\n");
}
void lineSense() {
    while(1){
        if( ADCRead(adc[2]) > .998 ) {
	  

      Printf("forwards");

      Wait(0.05);
      
        }
       /* else if(ADCRead(adc[2]) > 0 && ADCRead(adc[2]) < .4  ){
          SetMotor(left1, -1.0);
      SetMotor(left2, -1.0);
      SetMotor(right2, -1.0);
      SetMotor(right1, -1.0);  
        }
        */
        else {
        SetMotor(left1, 0);
      SetMotor(left2, 0);
      SetMotor(right2, 0);
      SetMotor(right1, 0);
             SetPin(PIN_F1, true);
             Printf(
            "Line Sensor values:  %1.3f\r",
            ADCRead(adc[2])
            );
	    Printf("\n");
        }


    
    }
}

void sumoBot(){
    int start = 0;
    Printf("hello");
    Printf("\n");
    while(1){
       
      

       if(start == 0){
         Straight();
         Printf("Straight");
         Printf("\n");
         start = 1;
       }

       if(start > 0 ){

        if( (ADCRead(adc[2]) * 100 ) < 85 ){ //// threshold for white
            Printf("back");
            Printf("\n");
            Back();
            Wait(1);
            Spin();
            Wait(1.5);
            Straight();
        }
       } 

         
    
    }
    

}

void Straight(){
    
    SetMotor(right1, -1.0);
    SetMotor(right2, -1.0);

    SetMotor(left1,  1.0);
    SetMotor(left2,  1.0);
    
    
    
    Printf("Done");
    Printf("\n");
}

void Spin() {
    SetMotor(left1, -1.0);
    SetMotor(left2, -1.0);
    SetMotor(right2, -1.0);
    SetMotor(right1, -1.0); 
}

void Back() {
    
    SetMotor(left1,  -1.0);
    SetMotor(left2,  -1.0);
    SetMotor(right2, 1.0);
    SetMotor(right1, 1.0);
    
}


void initGPIOLineSensor(){
    if(initialized){
        return;
    }
    initialized = true;

    //set four pins for ADC input - you can use these 4 I/O pins or select your own
    adc[1] = InitializeADC(PIN_E1);
    adc[2] = InitializeADC(PIN_E2);

    
}

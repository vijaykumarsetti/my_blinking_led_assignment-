//defining pin for lm35 sesnor(based on requirement it is A0)
const int lm35 = A0;

//defining pin for led. In this(arduino uno) case the onboard LED is connected to pin 13
const int led=13;

//taking a variable for storing temparature 
float temparature=0;

//taking variables for controlling delay of LED blinking
unsigned long int delay_count=0, current_count=0;

/* NOTE:- -> I didnt used any inbuilt functions for producing delay as per the requirement.
          -> Instead i am using non blocking delay(increament based approach)
          -> I have done neccassary calculations for this approach and they are explained below
          -> I have considered every line of code as O(1) for conivence, expect the non blocking delay code */


void setup() {
  // Setting the pin modes
  pinMode(led, OUTPUT); //setting led pin as output 
  pinMode(lm35, INPUT); //setting lm35(A0) as input as we have to read from it (As per the requirement i assumed that lm35 sensor is connected to A0) 
}

void loop() {
  // put your main code here, to run repeatedly:

  //initialising a variable to hold the return value(sensor value(lm35))
  int sensor_value=analogRead(lm35); // reading analog value at from the pin

  temparature=sensor_value*0.488; //actual value is 0.48828125 but i took whole value 
  /* Calculating temp sensor value(lm35)
  -> it is analog sensor and analog sensor are 10 bit in our case means they can hold upto 2^10-1 values
  -> supplying voltage is 5v so, 5/1024 = 0.0048828125(in millivolts)
  -> in volts 0.0048828125*1000 = 4.8828125  
  -> but our lm35 10mv will represnt 1 degree centigrade(as per the data sheet) so 4.8828125/10 = 0.48828125
  -> whole value 0.488 was taken*/

  //if temparature is less than 30 degree LED should blink for every 230 milliseconds
  //if temparature is greater than 30 degree it should blink for every 500 milliseconds
  //condition checking
  if(temparature >= -50 && temparature <= 150) // condition checking for expected values
  {
    if(temparature <= 30.0)
    {
      delay_count=184000; //if temparature is less than 30 degree making our variable delay as 250 in milliseconds(calculations are provided below)
    }
    else if(temparature > 30.0)
    {
      delay_count=4000000; //if temparature is above 30 degree making our delay as 500 in milliseconds(calculation are provided below)
    }
  }


  // actual logic for delay controlling witghout using any inbuilt function
  // Here i am using non blocking delay approach
  // assuming only this code takes time. and remaing code runs in O(1) only
  if(current_count++ <= delay_count)
  {
    current_count=0;
    digitalWrite(led,!digitalRead(led));
  }

  /* NOTE :- I followed non blocking delay approach and done neccassary calculations they are provided below
  -> frequency of arduino uno is 16MHZ and in arduino microcontroller 1 instruction cycle takes only 1 clock pulse
  -> so either increament or decrement happens in single clock pulse
  -> frequency = 16MHz,  TIME = 1/f; TIME=1/16000000 == 62.5 nanoseconds approxiamatley(1 instruction cycle)
  -> one tick(increament or decreament takes 62.5 nanoseconds in our microcontroller)
  -> converting to milliseconds(as our requirement is in milliseconds)
  -> 1 millisecond = 1000000 nanoseconds
  -> so 1 tick in milliseconds = 0.0000625 milliseconds( this is the time taken for 1 tick in milliseconds)
  -> now based on this we can calculate how many ticks can happen in 1 millisecond
  -> total ticks in 1 millisecond = 1 / ( time taken for 1 millisecond) == 1/0.0000625 ==16,000.
  -> 16,000 ticks can happen for 1 millisecond. by this we can calculate how many ticks for 250 & 500 milliseconds
  -> total ticks for 250 millisecond = (250 * total ticks in 1 millisecond) == (250 * 16000) == 3680000
  -> total ticks for 500 milliseconds = (500 * total ticks in 1 millisecond) == (250 * 16000) == 8000000
  -> but i considered half of them as reference delays because our microcontroller takes 1 instruction cycle for one operation
  -> if(current_count++ <= delay_count) so, in this line we are doing 2 operations 1) increamenting 
                                                                                   2) comparing
  -> so 2 instruction cycles were being completed here so we need half of the original time only                                                                               
   */

}

# my_blinking_led_assignment-
Blinked LED based on the temparature read by lm35 sensor
based on the requirement Onboard LED of the arduino uno should be blinked
if temparature falls less than 30 degree centigrade LED blinking interval should be 230 milliseconds
if it raises more than 30 degree centigrade LED blinking interval should be 500 millisecond
According to requiremtn we should not use any inbuilt functions like delay(), millis(), macros() functions
so i have done neccassary calculations and followed non blocking delay approach(without using timers)


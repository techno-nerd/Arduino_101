# Simple Burglar Alarm

This project combines what you have learnt in the Actuators and Sensors lessons. The goal is to create an alarm with flashing lights and a buzzer if a person gets too close.

You will need:
1. Arduino Mega 2560 R3
2. LEDs
3. Buzzer
4. Ultrasonic sensor
5. Push button
6. Breadboard
7. Jumper wires
8. Computer with Arduino IDE and USB cable

## Algorithm

You will need to continuously check the distance from the closest object using an ultrasonic sensor. If an object is less than 5 cm away, start the alarm! The buzzer and LED should beep and flash respectively for the next 5 seconds, unless the button is pressed, which turns off the alarm immediately.
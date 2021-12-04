/* In theory, this will control an LED in two modes,
    Mode 0 = off - will set the LED to a dimmer program
    Mode 1 = switch on will set the LED to be controlled by a potentiometer.
    Accomplished by a 2 pin toggle switch, pot, and an led
    the switch is connected to ground and digital pin, that pin is passed digitalwrite high
    this turns on the internal resistor of the arduino (in threory) 
    when the switch is in the off position, the pin reads HIGH, when it is on, the pin reads LOW
    Fade/dimmer was lifted off examples mostly
*/

const int ledPin = 8;    // led is set to digital pin8
const int switchPin = 7; // switch is set to digital pin7
const int pot = A3;      // sets the pot pin in
const int off = 0;       //variables for mode off and on
const int on = 1;
int mode = off;     //initialize mode as off for dimmer program to be defualt
int brightness = 0; //start the LED off basically
int fadeamount = 5; //percentage for the dimmer program to lower the LED by

void setup()
{
    pinMode(switchPin, INPUT);     //sets switch pin as an input
    digitalWrite(switchPin, HIGH); //sets switch pin to push V out, turning on the internal resistor
    pinMode(ledPin, OUTPUT);       //setse the led pin to an output
}

void loop()
{
    if (digitalRead(switchPin) == HIGH)
    { //if the switch is off, then execute case off
        mode = off;
    }
    if (digitalRead(switchPin) == LOW)
    { // the opposite of above
        mode = on;
    }
    switch (mode)
    {
    case off:
        analogWrite(ledPin, brightness);
        brightness = brightness + fadeamount;

        if (brightness <= 0 || brightness >= 255)
        {
            fadeamount = -fadeamount;
        }
        delay(30);
        break;

    case on:
        int potValue = analogRead(pot); //sets the value of the pot
        potValue = map(potValue, 0, 1023, 0, 255);
        analogWrite(ledPin, potValue);
        break;
    }
}

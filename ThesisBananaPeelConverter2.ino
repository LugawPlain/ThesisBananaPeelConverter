#include <Servo.h>
#include <LCD-I2C.h>
#include <Wire.h>

Servo servo1;
LCD_I2C lcd(0x27, 16, 2);
char c;
const int relay2 = A0;
const int relay3 = A1;
const int pumpRelay = 2;
const int pump2Relay = 3;
const int stepperRelay = 4;
const int stepper2Relay = 5;
const int servo2Relay = 6;
const int servo3Relay = 7;
const int servo2 = 9;
const int servo3 = 10;
const int stepper1step = 11;
const int stepper1dir = 12;
const int stepper2step = 13;
const int stepper2dir = ;
const int cookerRelay = ;

void setup()
{
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    Serial.begin(9600);
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    delay(1000);
}
void loop()
{
}
void receiveEvent(int numBytes)
{
    while (1 < Wire.available())
    {
        c = Wire.read();
        switch (c)
        {
        case 'G':
            pinMode(grinderRelay, OUTPUT);
            digitalWrite(grinderRelay, HIGH);
            break;
        case 'M':
            break;
        case 'C':
            break;
        }
    }
}
void requestEvent()
{
    // switch (c)
    //     {
    //     case 'G':
    //         Wire.write('G');
    //         break;
    //     case 'M':
    //         Wire.write('M');
    //         break;
    //     case 'C':
    //         Wire.write('C');
    //         break;
    //     }
}
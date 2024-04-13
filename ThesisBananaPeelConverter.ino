#include <Servo.h>
#include <LCD-I2C.h>
#include <Wire.h>

Servo servo1;
LCD_I2C lcd(0x27, 16, 2);

const int dehydratorButton = 2; // Pin ng mga Buttons
const int grinderButton = 3;
const int mixerButton = 4;
const int cookerButton = 5;
const int StartButton = 6;
const int StopButton = 7;

const int heatlampRelay = 8; // Pin ng mga Relays
const int servoPWM = 9;
const int servoRelay = 10;
const int ceramicheaterRelay = 11;
const int fanRelay = 12;
const int relay1 = A0;
const int grinderRelay = 13;
int servo1angle = 0;

int state = 0;

void setup()
{
    Serial.begin(9600);
    lcd.begin();
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    pinMode(dehydratorButton, INPUT_PULLUP);
    pinMode(grinderButton, INPUT_PULLUP);
    pinMode(mixerButton, INPUT_PULLUP);
    pinMode(cookerButton, INPUT_PULLUP);
    lcd.setCursor(0, 1);
    lcd.print("Buttons");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    pinMode(heatlampRelay, OUTPUT);
    pinMode(servoRelay, OUTPUT);
    pinMode(servoPWM, OUTPUT);
    pinMode(ceramicheaterRelay, OUTPUT);
    pinMode(fanRelay, OUTPUT);
    pinMode(relay1, OUTPUT);

    servo1.attach(servoPWM);
    digitalWrite(heatlampRelay, HIGH);
    digitalWrite(servoRelay, HIGH);
    digitalWrite(ceramicheaterRelay, HIGH);
    digitalWrite(fanRelay, HIGH);
    digitalWrite(relay1, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Dehydrator");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    pinMode(grinderRelay, OUTPUT);
    digitalWrite(grinderRelay, HIGH);
    //
    // Wire.beginTransmission(8);
    // Wire.write('G');
    // Wire.requestFrom(8, 1);
    // while (!(Wire.available()))
    //     // {
    //     //     if (Wire.available())
    //     //     {
    //     //         char c = Wire.read();
    //     //         if (c == 'G')
    //     //         {
    //     //             lcd.setCursor(0, 1);
    //     //             lcd.print("Grinder");
    //     //             break;
    //     //         }
    //     //         else
    //     //         {
    //     //             lcd.setCursor(0, 1);
    //     //             lcd.print("Failed G");
    //     //             while (1)
    //     //                 ;
    //     //         }
    //     //     }
    //     // }
    //     Wire.endTransmission();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    Wire.beginTransmission(8);
    Wire.write('M');
    // Wire.requestFrom(8, 1);
    // while (!(Wire.available()))
    // {
    //     if (Wire.available())
    //     {
    //         char c = Wire.read();
    //         if (c == 'M')
    //         {
    //             lcd.setCursor(0, 1);
    //             lcd.print("Mixer");
    //             break;
    //         }
    //         else
    //         {
    //             lcd.setCursor(0, 1);
    //             lcd.print("Failed M");
    //             while (1)
    //                 ;
    //         }
    //     }
    // }
    Wire.endTransmission();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    Wire.beginTransmission(8);
    Wire.write('C');
    // Wire.requestFrom(8, 1);
    // while (!(Wire.available()))
    // {
    //     if (Wire.available())
    //     {
    //         char c = Wire.read();
    //         if (c == 'C')
    //         {
    //             lcd.setCursor(0, 1);
    //             lcd.print("Cooker");
    //             break;
    //         }
    //         else
    //         {
    //             lcd.setCursor(0, 1);
    //             lcd.print("Failed C");
    //             while (1)
    //                 ;
    //         }
    //     }
    // }
    Wire.endTransmission();

    lcd.clear();
    lcd.print("Converter");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
}

void loop()
{
    while (!state)
    {
        if (digitalRead(dehydratorButton == LOW))
        {
            state = 1;
        }
        if (digitalRead(grinderButton == LOW))
        {
            state = 2;
        }
        if (digitalRead(mixerButton == LOW))
        {
            state = 3;
        }
        if (digitalRead(cookerButton == LOW))
        {
            state = 4;
        }
    }
    switch (state)
    {
    case (1):
        dehydratorOn();
        dehydratorOff();
        break;
    case (2):
        grinderOn();
        grinderOff();
        break;
    case (3):
        break;
    case (4):
        break;
    }
    state = 0;
}

void dehydratorOn()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo ON");
    servo1.write(servo1angle);
    digitalWrite(servoRelay, LOW);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan ON");
    digitalWrite(fanRelay, LOW);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heat Lamp ON");
    digitalWrite(heatlampRelay, LOW);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ceramic     ON");
    lcd.setCursor(0, 1);
    lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, LOW);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrating");
    lcd.setCursor(0, 1);
    threedots();
    delay(1000 * 60 * 60 * 8); // delay 8 hours
    servo1.write(45);
}
void dehydratorOff()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo OFF");
    servo1.write(45);
    digitalWrite(servoRelay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan OFF");
    digitalWrite(fanRelay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heat Lamp OFF");
    digitalWrite(heatlampRelay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ceramic     OFF");
    lcd.setCursor(0, 1);
    lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, HIGH);
    delay(1000);
}

void grinderOn()
{
    for (int i = 0; i < 60; i++)
    {
        digitalWrite(grinderRelay, LOW);
        delay(1500);
        digitalWrite(grinderRelay, HIGH);
        delay(1500);
    }
}
void grinderOff()
{
    digitalWrite(grinderRelay, HIGH);
}
void mixerOn()
{
    digitaWrite(waterDispenser, HIGH);
    delay(waterDuration * 1000);
    digitaWrite(waterDispenser, LOW);

    delay(2000);

    digitaWrite(waterDispenser, HIGH);
    delay(waterDuration * 1000);
    digitaWrite(waterDispenser, LOW);

    delay(2000);

    digitaWrite(waterDispenser, HIGH);
    delay(waterDuration * 1000);
    digitaWrite(waterDispenser, LOW);

    delay(2000);

    digitaWrite(waterDispenser, HIGH);
    delay(waterDuration * 1000);
    digitaWrite(waterDispenser, LOW);

    delay(2000);

    digitaWrite(mixerRelay, HIGH);

    delay(mixingTime * 1000);
}
void mixerOff()
{
    digitaWrite(mixerRelay, LOW);
}
void CookerOn()
{
    analogWrite(cookerServo, ANGLE);
    delay();
    analogWrite(cookerServo, ANGLE);
    delay();
    analogWrite(cookerServo, DEFAULT ANGLE)

        digitaWrite(cookerRelay, HIGH);
    delay(cookingTime * 1000);
}
void CookerOff()
{
    digitaWrite(cookerRelay, LOW);
}
void threedots()
{
    lcd.setCursor(0, 1);
    millis();
    for (int i = 0; i < 3; i++)
    {
        lcd.setCursor(0, 1);
        lcd.print(".");
        delay(500);
    }
    for (int i = 0; i < 3; i++)
    {
        lcd.setCursor(0, 1);
        lcd.print("");
    }
}
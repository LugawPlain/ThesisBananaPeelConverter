#include <Servo.h>
#include <LCD-I2C.h>
#include <AccelStepper.h>

Servo servo1;
Servo servo2;
Servo servo3;
LCD_I2C lcd(0x27, 16, 2);
AccelStepper stepper1(1, 31, 33);
AccelStepper stepper2(1, 32, 34);

int servo1angle = 0;
int servo2Pos1Angle = 0;
int servo2Pos2Angle = 0;
int servo3OpenAngle = 0;
int servo3CloseAngle = 0;
int waterDuration = 0;
int eggDuration = 0;
int mixingTime = 0;
int cookingTime = 0;

const int dehydratorButton = 2; // Pin ng mga Buttons
const int grinderButton = 3;
const int mixerButton = 4;
const int cookerButton = 5;
const int StartButton = 6;
const int stopButton = 7;

const int heatlampRelay = 8; // Pin ng mga Relays
const int servoPWM = 9;
const int servoRelay = 29;
const int ceramicheaterRelay = 30;
const int fanRelay = 12;
const int grinderRelay = 13;
const int relay1 = A0;

const int relay2 = A1;
const int relay3 = A2;

const int pumpRelay = 22;
const int pump2Relay = 23;
const int stepperRelay = 24;
const int stepper2Relay = 25;
const int mixerRelay = 26;
const int pump3Relay = 27;

const int stepper1step = 28;
const int stepper1dir = 29;
const int stepper2step = 30;
const int stepper2dir = 31;

const int servo2PWM = 10;
const int servo3PWM = 11;
const int servo2Relay = 32;
const int servo3Relay = 33;
const int cookerRelay = 34;

volatile int stopButton;
volatile int state = 0;
void stopInterrupt()
{
    
}

void setup()
{
    attachInterrupt(digitalPinToInterrupt(stopButton), stopInterrupt, CHANGE);
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
    pinMode(StartButton, INPUT_PULLUP);
    pinMode(stopButton, INPUT_PULLUP);
    lcd.setCursor(0, 1);
    lcd.print("Buttons");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(heatlampRelay, OUTPUT);
    pinMode(servoRelay, OUTPUT);
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

    // pinMode(relay2, OUTPUT);
    pinMode(grinderRelay, OUTPUT);
    digitalWrite(grinderRelay, HIGH);
    // digitalWrite(relay2, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Grinder");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(relay3, OUTPUT);
    pinMode(pumpRelay, OUTPUT);
    pinMode(pump2Relay, OUTPUT);
    pinMode(stepperRelay, OUTPUT);
    pinMode(stepper2Relay, OUTPUT);

    digitalWrite(pumpRelay, HIGH);
    digitalWrite(pump2Relay, HIGH);
    digitalWrite(stepperRelay, HIGH);
    digitalWrite(stepper2Relay, HIGH);
    digitalWrite(relay3, HIGH);
    stepper1.setMaxSpeed(1000);
    stepper2.setMaxSpeed(1000);

    lcd.setCursor(0, 1);
    lcd.print("Mixer");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    pinMode(servo2Relay, OUTPUT);
    pinMode(servo3Relay, OUTPUT);
    pinMode(cookerRelay, OUTPUT);

    servo2.attach(servo2PWM);
    servo3.attach(servo3PWM);

    digitalWrite(servo2Relay, HIGH);
    digitalWrite(servo3Relay, HIGH);
    digitalWrite(cookerRelay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Cooker");
    delay(1000);

    lcd.clear();
    lcd.print("Converter");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
}

void loop()
{
    while (!state)
    {
        lcd.clear();
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
        if (digitalRead(StartButton == LOW))
        {
            state = 5;
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
    case (5):
        dehydratorOn();
        dehydratorOff();
        delay(5000);
        grinderOn();
        grinderOff();
        delay(5000);
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
    lcd.print("Ceramic OFF");
    lcd.setCursor(0, 1);
    lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrator OFF");
    delay(1000);
}

void grinderOn()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinder ON");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinding");
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinding OFF");
    delay(1000);
}
void mixerOn()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water pump ON");
    digitalWrite(pumpRelay, LOW);
    delay(waterDuration * 1000);
    digitalWrite(pumpRelay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Egg pump ON");
    digitalWrite(pump2Relay, LOW);
    delay(eggDuration * 1000);
    digitalWrite(pump2Relay, HIGH);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Powder one ON");
    delay(1000);

    delay(2000);

    digitalWrite(mixerRelay, LOW);

    delay(mixingTime * 1000);
}
void mixerOff()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixer OFF");
    digitalWrite(pumpRelay, HIGH);
    digitalWrite(pump2Relay, HIGH);
    digitalWrite(mixerRelay, HIGH);
    delay(1000);
}
void CookerOn()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Open");
    servo3.write(servo3OpenAngle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS one");
    servo2.write(servo2Pos1Angle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, LOW);
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS two");
    servo2.write(servo2Pos2Angle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, LOW);
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Close");
    servo3.write(servo3CloseAngle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cooking");
    digitalWrite(cookerRelay, LOW);
    delay(cookingTime);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Open");
    servo3.write(servo3OpenAngle);
    delay(1000);
}
void CookerOff()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cooker OFF");
    digitalWrite(cookerRelay, HIGH);
    delay(cookingTime);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS one");
    servo2.write(servo2Pos1Angle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Open");
    servo3.write(servo3OpenAngle);
    delay(1000);
}
// void threedots()
// {
//     lcd.setCursor(0, 1);
//     millis();
//     for (int i = 0; i < 3; i++)
//     {
//         lcd.setCursor(0, 1);
//         lcd.print(".");
//         delay(500);
//     }
//     for (int i = 0; i < 3; i++)
//     {
//         lcd.setCursor(0, 1);
//         lcd.print("");
//     }
// }
#include <Servo.h>
#include <LCD-I2C.h>
// #include <AccelStepper.h>

Servo servo1;
Servo servo2;
Servo servo3;
LCD_I2C lcd(0x27, 16, 2);
// AccelStepper stepper1(1, 31, 33);
// AccelStepper stepper2(1, 32, 34);

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
// const int stopButton = 7;

const int heatlampRelay = 23; // Pin ng mga Relays
const int servoPWM = 9;
const int servoRelay = 27;
const int ceramicheaterRelay = 22;
const int fanRelay = 28;
const int grinderRelay = 20;
const int relay1 = 24;

const int relay2 = 29;
const int relay3 = 34;

const int pumpRelay = 25;
const int pump2Relay = 26;
// const int stepperRelay = ;
// const int stepper2Relay = ;
const int mixerRelay = 31;
const int pump3Relay = 30;

// const int stepper1step = ;
// const int stepper1dir = ;
// const int stepper2step = ;
// const int stepper2dir = ;

const int servo2PWM = 10;
const int servo3PWM = 11;
const int servo2Relay = 32;
const int servo3Relay = 33;
const int cookerRelay = 21;

// volatile int stopButton;
// void stopInterrupt()
// {
//     switch (state)
//     {
//     case 1:
//         dehydratorOff();
//         break;
//     case 2:
//         grinderOff();
//         break;
//     case 3:
//         mixerOff();
//         break;
//     case 4:
//         CookerOff();
//         break;
//     case 5:
//         dehydratorOff();
//         grinderOff();
//         mixerOff();
//         CookerOff();
//         break;
//     }
//     digitalWrite(resetPIN, LOW);
// }
int state = 0;
void setup()
{
    // attachInterrupt(digitalPinToInterrupt(stopButton), stopInterrupt, CHANGE);
    Serial.begin(9600);
    lcd.begin();
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    // digitalWrite(resetPIN, HIGH);
    // pinMode(resetPIN, OUTPUT);

    pinMode(dehydratorButton, INPUT);
    pinMode(grinderButton, INPUT);
    pinMode(mixerButton, INPUT);
    pinMode(cookerButton, INPUT);
    pinMode(StartButton, INPUT);
    // pinMode(stopButton, INPUT_PULLUP);
    digitalWrite(dehydratorButton, HIGH);
    digitalWrite(grinderButton, HIGH);
    digitalWrite(mixerButton, HIGH);
    digitalWrite(cookerButton, HIGH);
    digitalWrite(StartButton, HIGH);
    // digitalWrite(stopButton, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Buttons");
    // delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(relay1,OUTPUT);
    digitalWrite(relay1, HIGH);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Relay");
    // delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(heatlampRelay, OUTPUT);
    pinMode(servoRelay, OUTPUT);
    pinMode(ceramicheaterRelay, OUTPUT);
    pinMode(fanRelay, OUTPUT);
    // pinMode(relay1, OUTPUT);
    servo1.attach(servoPWM);
    digitalWrite(heatlampRelay, HIGH);
    digitalWrite(servoRelay, HIGH);
    digitalWrite(ceramicheaterRelay, HIGH);
    digitalWrite(fanRelay, HIGH);
    // digitalWrite(relay1, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Dehydrator");
    // delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(grinderRelay, OUTPUT);
    digitalWrite(grinderRelay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Grinder");
    // delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    

    pinMode(pumpRelay, OUTPUT);
    pinMode(pump2Relay, OUTPUT);
    // pinMode(stepperRelay, OUTPUT);
    // pinMode(stepper2Relay, OUTPUT);

    digitalWrite(pumpRelay, HIGH);
    digitalWrite(pump2Relay, HIGH);
    // digitalWrite(stepperRelay, HIGH);
    // digitalWrite(stepper2Relay, HIGH);
    // stepper1.setMaxSpeed(1000);
    // stepper2.setMaxSpeed(1000);

    lcd.setCursor(0, 1);
    lcd.print("Mixer");
    // delay(1000);

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
    // delay(1000);

    lcd.clear();
    lcd.print("Converter");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
    delay(2000);
    Serial.println(state);
}

void loop()
{
    while (state == 0)
    {
        lcd.clear();
        if (digitalRead(dehydratorButton)== LOW)
        {
            state = 1;
            Serial.print("dehydtrator: ");
            Serial.println(state);
            Serial.println(digitalRead(dehydratorButton));
            delay(500);
        }
        else if (digitalRead(grinderButton)== LOW)
        {
            state = 2;
            Serial.print("grinder: ");
            Serial.println(state);
            Serial.println(grinderButton);
            delay(500);
        }
        else if (digitalRead(mixerButton) == LOW)
        {
            state = 3;
            Serial.print("mixer: ");
            Serial.println(state);
            Serial.println(mixerButton);
            delay(500);
        }
        else if (digitalRead(cookerButton) == LOW)
        {
            state = 4;
            Serial.print("cooker: ");
            Serial.println(state);
            Serial.println(cookerButton);
            delay(500);
        }
        else if (digitalRead(StartButton) == LOW)
        {
            state = 5;
            Serial.print("start: ");
            Serial.println(state);
            Serial.println(StartButton);
            delay(500);
        }
        // lcd.clear();
        // lcd.write(state);
        // delay(2000);
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
        mixerOn();
        mixerOff();
        break;
    case (4):
        cookerOn();
        cookerOff();
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
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Servo OFF");
    servo1.write(45);
    digitalWrite(servoRelay, HIGH);
    // delay(1000);

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Fan OFF");
    digitalWrite(fanRelay, HIGH);
    // delay(1000);

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Heat Lamp OFF");
    digitalWrite(heatlampRelay, HIGH);
    // delay(1000);

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Ceramic OFF");
    // lcd.setCursor(0, 1);
    // lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, HIGH);
    // delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrator OFF");
    // delay(1000);
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
    // delay(1000);
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
    // delay(1000);
}
void cookerOn()
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
void cookerOff()
{
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Cooker OFF");
    digitalWrite(cookerRelay, HIGH);
    // delay(cookingTime);

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("ServoHose");
    // lcd.setCursor(0, 1);
    // lcd.print("POS one");
    servo2.write(servo2Pos1Angle);
    // delay(1000);

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Servo Open");
    servo3.write(servo3OpenAngle);
    // delay(1000);
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
// #include <Servo.h>
#include <LCD_I2C.h>
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
    // stepper_NEMA17.setSpeed(80);
    // stepper_NEMA17.step(STEPS_PER_REV / 100);

// Servo servo1;
// Servo servo2;
// Servo servo3;
LCD_I2C lcd(0x27, 16, 2);
const int STEPS_PER_REV = 200;

// Stepper bpfStepper(STEPS_PER_REV, 2, 3, 4, 5);
// Stepper flourStepper(STEPS_PER_REV,2,3,4,5);
 

int servo1AngleBefore = 35;
int servo2Pos1AngleBefore = 30;
int servo2Pos2AngleBefore = 75;
int servo3OpenAngleBefore = 15;
int servo3CloseAngleBefore = 135;

int servo2Pos1Angle = map(servo2Pos1AngleBefore, 0, 180, 100, 600);
int servo2Pos2Angle = map(servo2Pos2AngleBefore, 0, 180, 100, 600);
int servo1Angle = map(servo1AngleBefore, 0, 180, 100, 600);
int servo3OpenAngle = map(servo3OpenAngleBefore, 0, 180, 100, 600);
int servo3CloseAngle = map(servo3CloseAngleBefore, 0, 180, 100, 600);

int grindingTime = 180;
int waterDuration = 5;
int eggDuration = 5;
int bpfDuration = 5;
int flourDuration = 5;
int batterTime  = 5;
int mixingTime = 5;
int cookingTime = 5;

const int dehydratorButton = 2; // Pin ng mga Buttons
const int grinderButton = 3;
const int mixerButton = 4;
const int cookerButton = 5;
const int StartButton = 6;
const int stopButton = 7;

// const int servoPWM = 9;
// const int servo2PWM = 10;
// const int servo3PWM = 11;

const int relay1 = 30;

const int grinderRelay = 22;
const int cookerRelay = 24;
const int ceramicheaterRelay = 26;
const int heatlampRelay = 28; // Pin ng mga Relays

const int relay2 = 40;
const int pumpRelay = 32;
const int pump2Relay = 34;
const int servoRelay = 36;
const int fanRelay = 38;

const int relay3 = 31;
const int servo2Relay = 23;
const int servo3Relay = 25;
const int pump3Relay = 27;
const int mixerRelay = 29;

int state = 0;

// const int stepperRelay = 24;
// const int stepper2Relay = 25;
// const int stepper1step = 28;
// const int stepper1dir = 29;
// const int stepper2step = 30;
// const int stepper2dir = 31;

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
//     // digitalWrite(resetPIN, LOW);
// }

void setup()
{
    Serial.begin(9600);
    Serial.println(servo1Angle);
      Serial.println(servo2Pos1Angle);
      Serial.println(servo2Pos2Angle);
      Serial.println(servo3OpenAngle);
      Serial.println(servo3CloseAngle);
    pwm.begin();
    pwm.setPWMFreq(60);
    lcd.begin();
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");
    // digitalWrite(resetPIN, HIGH);
    // pinMode(resetPIN, OUTPUT);

    pinMode(dehydratorButton, INPUT_PULLUP);
    pinMode(grinderButton, INPUT_PULLUP);
    pinMode(mixerButton, INPUT_PULLUP);
    pinMode(cookerButton, INPUT_PULLUP);
    pinMode(StartButton, INPUT_PULLUP);
    pinMode(stopButton, INPUT_PULLUP);

    lcd.setCursor(0, 1);
    lcd.print("Buttons"); 
    // delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(relay1,OUTPUT);
    digitalWrite(relay1,HIGH);
    pinMode(relay2,OUTPUT);
    digitalWrite(relay2,HIGH);
    pinMode(relay3,OUTPUT);
    digitalWrite(relay3,HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Relay");
    // delay(1000);


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(servoRelay, OUTPUT);
    // servo1.attach(servoPWM);

    pinMode(heatlampRelay, OUTPUT);
    pinMode(ceramicheaterRelay, OUTPUT);
    pinMode(fanRelay, OUTPUT);
    digitalWrite(heatlampRelay, HIGH);
    digitalWrite(servoRelay, HIGH);
    digitalWrite(ceramicheaterRelay, HIGH);
    digitalWrite(fanRelay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Dehydrator");
    // delay(1000);

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
    pinMode(mixerRelay, OUTPUT);
    pinMode(pumpRelay, OUTPUT);
    pinMode(pump2Relay, OUTPUT);
    // pinMode(stepperRelay, OUTPUT);
    // pinMode(stepper2Relay, OUTPUT);
    digitalWrite(mixerRelay, HIGH);
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
    pinMode(pump3Relay, OUTPUT);

    // servo2.attach(servo2PWM);
    // servo3.attach(servo3PWM);

    digitalWrite(servo2Relay, HIGH);
    digitalWrite(servo3Relay, HIGH);
    digitalWrite(cookerRelay, HIGH);
    digitalWrite(pump3Relay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Cooker");
    // delay(1000);

    lcd.clear();
    lcd.print("Converter");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
}

void loop()
{
    while (!state)
    {
        if (digitalRead(dehydratorButton) == LOW)
        {
            state = 1;
        }
        if (digitalRead(grinderButton) == LOW)
        {
            state = 2;
        }
        if (digitalRead(mixerButton) == LOW)
        {
            state = 3;
        }

        if (digitalRead(cookerButton) == LOW)
        {
            state = 4;
        }
        if (digitalRead(StartButton) == LOW)
        {
            state = 5;
        }
    }
    switch (state)
    {
    case (1):
        Serial.print("1");
        dehydratorOn();
        dehydratorOff();
        break;
    case (2):
        Serial.print("2");
        grinderOn();
        grinderOff();
        break;
    case (3):
        Serial.print("3");
        mixerOn();
        mixerOff();
        break;
    case (4):
        Serial.print("4");    
        CookerOn();
        CookerOff();
        break;
    case (5):
        Serial.print("5");  
        dehydratorOn();
        dehydratorOff();
        grinderOn();
        grinderOff();
        mixerOn();
        mixerOff();
        CookerOn();
        CookerOff();
        break;
    }
    state = 0;
}
void dehydratorOn()
{
    Serial.println("DehydratorOn");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo ON");
    digitalWrite(servoRelay, LOW);
    // servo1.write(servo1Angle);
    pwm.setPWM(0,0,servo1Angle);
    delay(5000);

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
    lcd.print("Ceramic ON");
    lcd.setCursor(0, 1);
    lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, LOW);
    delay(10000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrating");
    delay(1000 * 60 * 60 * 8); // delay 8 hours
}
void dehydratorOff()
{
    Serial.println("DehydratorOff");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo OFF");
    // servo1.write(30);
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
    Serial.println("GrinderOn");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinder ON");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinding");
    for (int i = 0; i < 1; i++)
    {
        digitalWrite(grinderRelay, LOW);
        delay(1000);
        digitalWrite(grinderRelay, HIGH);
        delay(500);
    }
}
void grinderOff()
{
    Serial.println("DehydratorOff");
    digitalWrite(grinderRelay, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinding OFF");
    delay(1000);
}
void mixerOn()
{
    Serial.println("MixerOn");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water pump ON");
    digitalWrite(pumpRelay, LOW);
    delay(waterDuration * 1000);
    digitalWrite(pumpRelay, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Egg pump ON");
    digitalWrite(pump2Relay, LOW);
    delay(eggDuration * 1000);
    digitalWrite(pump2Relay, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Powder one ON");
    // bpfStepper.setSpeed(80);    
    // bpfStepper.step(STEPS_PER_REV / 100);

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Powder two ON");
    // flourStepper.setSpeed(80);    
    // flourStepper.step(STEPS_PER_REV / 100);

    delay(2000);

    digitalWrite(mixerRelay, LOW);
    delay (1000);
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
    digitalWrite(servo3Relay,LOW);
    pwm.setPWM(2,0,servo3OpenAngle);
    // servo3.write(servo3OpenAngle);
    delay(5000);
    digitalWrite(servo3Relay,HIGH);

    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS one");
    digitalWrite(servo2Relay,LOW);
    pwm.setPWM(1,0,servo2Pos1Angle);
    // servo2.write(servo2Pos1Angle);
    delay(5000);
    digitalWrite(servo2Relay,HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("On ");
    delay(5000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, HIGH); 
    lcd.setCursor(0, 1);
    lcd.print("OFF ");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS two");
    digitalWrite(servo2Relay,LOW);
    pwm.setPWM(1,0,servo2Pos2Angle);
    // servo2.write(servo2Pos2Angle);
    delay(5000);
    digitalWrite(servo2Relay,HIGH);   

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("On ");
    delay(5000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("OFF ");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Close ");
    digitalWrite(servo3Relay,LOW);
    pwm.setPWM(2,0,servo3CloseAngle);
    // servo3.write(servo3CloseAngle);
    delay(5000);
    digitalWrite(servo3Relay,HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cooking");
    digitalWrite(cookerRelay, LOW);
    delay(cookingTime);
    digitalWrite(cookerRelay,HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Open");
    digitalWrite(servo3Relay,LOW);
    pwm.setPWM(2,0,servo3OpenAngle);
    // servo3.write(servo3OpenAngle);
    delay(5000);
    digitalWrite(servo3Relay,HIGH);
    
}
void CookerOff()
{
    // // lcd.clear();
    // // lcd.setCursor(0, 0);
    // // lcd.print("Cooker OFF");
    // digitalWrite(cookerRelay, HIGH);
    // // delay(cookingTime);

    // // lcd.clear();
    // // lcd.setCursor(0, 0);
    // // lcd.print("ServoHose");
    // // lcd.setCursor(0, 1);
    // // lcd.print("POS one");
    // servo2.write(servo2Pos1Angle);
    // // delay(1000);

    // // lcd.clear();
    // // lcd.setCursor(0, 0);
    // // lcd.print("Servo Open");
    // servo3.write(servo3OpenAngle);
    // // delay(1000);
}
void delayPrint(String name,int count){
    Serial.print(name);
    Serial.println(":");
    for (int i = 1; i <= count; i++)
    {
        Serial.println(i);
        delay(1000);
    }
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
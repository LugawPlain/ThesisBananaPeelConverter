#include <Servo.h>
#include <LCD_I2C.h>
#include <Stepper.h>
 
    // stepper_NEMA17.setSpeed(80);
    // stepper_NEMA17.step(STEPS_PER_REV / 100);

Servo servo1;
Servo servo2;
Servo servo3;
LCD_I2C lcd(0x27, 16, 2);
const int STEPS_PER_REV = 200;

Stepper bpfStepper(STEPS_PER_REV, 2, 3, 4, 5);
Stepper flourStepper(STEPS_PER_REV,2,3,4,5);
 

int servo1angle = 20;
int servo2Pos1Angle = 15;
int servo2Pos2Angle = 90;
int servo3OpenAngle = 15;
int servo3CloseAngle = 135;
int grindingTime = 180;
int waterDuration = 5;
int eggDuration = 5;
int bpfDuration = 5;
int flourDuration = 5;
int batterTime  = 5;
int mixingTime = 5;
int cookingTime = 5;

// const int resetPIN = 35;
const int dehydratorButton = 2; // Pin ng mga Buttons
const int grinderButton = 3;
const int mixerButton = 4;
const int cookerButton = 5;
const int StartButton = 6;
const int stopButton = 7;

const int servoPWM = 9;
const int servo2PWM = 10;
const int servo3PWM = 11;

const int relay1 = 26;

const int grinderRelay = 22;
const int cookerRelay = 23;
const int ceramicheaterRelay = 24;
const int heatlampRelay = 25; // Pin ng mga Relays

const int relay2 = 31;
const int pumpRelay = 27;
const int pump2Relay = 28;
const int servoRelay = 29;
const int fanRelay = 30;

const int relay3 = 36;
const int pump3Relay = 32;
const int servo2Relay = 33;
const int servo3Relay = 34;
const int mixerRelay = 35;

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
    delay(1000);

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
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(servoRelay, OUTPUT);
    servo1.attach(servoPWM);

    pinMode(heatlampRelay, OUTPUT);
    pinMode(ceramicheaterRelay, OUTPUT);
    pinMode(fanRelay, OUTPUT);
    digitalWrite(heatlampRelay, HIGH);
    digitalWrite(servoRelay, HIGH);
    digitalWrite(ceramicheaterRelay, HIGH);
    digitalWrite(fanRelay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Dehydrator");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(grinderRelay, OUTPUT);
    digitalWrite(grinderRelay, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Grinder");
    delay(1000);

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
    lcd.print("Ceramic ON");
    lcd.setCursor(0, 1);
    lcd.print("Heater");
    digitalWrite(ceramicheaterRelay, LOW);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrating");
    delay(1000 * 60 * 60 * 8); // delay 8 hours
}
void dehydratorOff()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo OFF");
    servo1.write(30);
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
    for (int i = 0; i < grindingTime; i++)
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
    // bpfStepper.setSpeed(80);    
    // bpfStepper.step(STEPS_PER_REV / 100);
    timerPrint("bfp",3);

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Powder two ON");
    // flourStepper.setSpeed(80);    
    // flourStepper.step(STEPS_PER_REV / 100);

    timerPrint("bfp",3);

    delay(2000);

    digitalWrite(mixerRelay, LOW);

    timerPrint("Mixer",3);
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
    servo3.write(servo3OpenAngle);
    delay(2000);
    digitalWrite(servo3Relay,HIGH);

    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ServoHose");
    lcd.setCursor(0, 1);
    lcd.print("POS one");
    digitalWrite(servo2Relay,LOW);
    servo2.write(servo2Pos1Angle);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("On ");
    delay(batterTime * 1000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("OFF ");
    delay(batterTime * 1000);

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
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("On ");
    delay(batterTime * 1000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PumpHose");
    digitalWrite(pump3Relay, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("OFF ");
    delay(batterTime * 1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo Close ");
    digitalWrite(servo3Relay,LOW);
    servo3.write(servo3OpenAngle);
    digitalWrite(servo3Relay,HIGH);
    delay(2000);

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
    servo3.write(servo3OpenAngle);
    digitalWrite(servo3Relay,HIGH);
    delay(2000);

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
void timerPrint(String name,int count){
    Serial.print(name);
    Serial.print(":");
    for (int i = 0; i < count; i++)
    {
        Serial.println(count);
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
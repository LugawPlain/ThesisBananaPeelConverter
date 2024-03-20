#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Button = 2;
const int Fan = 3;
const int RelayServo = 4;
const int CeramicHeater = 5;
const int HeatLamp = 6;
const int RelayVcc = 7;
void setup()
{
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.print("Initializing.");
    lcd.print("Initializing..");
    lcd.print("Initializing...");
    delay(2000);
    servo1.attach(9);
    pinMode(Button, INPUT_PULLUP);
    pinMode(Fan, OUTPUT);
    pinMode(RelayServo, OUTPUT);
    pinMode(CeramicHeater, OUTPUT);
    pinMode(HeatLamp, OUTPUT);
    pinMode(RelayVcc, OUTPUT);
    digitalWrite(Fan, HIGH);
    digitalWrite(RelayServo, HIGH);
    digitalWrite(CeramicHeater, HIGH);
    digitalWrite(HeatLamp, HIGH);
    digitalWrite(RelayVcc, HIGH);
}

void loop()
{
    lcd.clear();
    lcd.print("Start");
    digitalWrite(Fan, LOW);
    digitalWrite(RelayServo, LOW);

    for (int i = 0; i <= 180; i += 15)
    {
        servo1.write(i);
        lcd.clear();

        lcd.setCursor(0, 1);
        lcd.print("Servo pos");
        lcd.print(i);
        delay(1000);
    }
}
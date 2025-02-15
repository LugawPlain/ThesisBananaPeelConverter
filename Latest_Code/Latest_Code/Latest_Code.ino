#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define ENABLE_DEBUG_OUTPUT
#include <Adafruit_PWMServoDriver.h>
#include <DHT.h>

//////////////////////////////////
// Button
const int dehydratorButton = 2; // Pin ng mga Buttons
const int grinderButton = 3;
const int mixerButton = 4;
const int cookerButton = 5;
const int StartButton = 6;
//const int stopButton = 7;
//////////////////////////////////
LiquidCrystal_I2C lcd(0x27, 16, 2);
//////////////////////////////////
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//////////////////////////////////
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//////////////////////////////////
// 220v relay
const int relayHeater = 30;
const int relayGrinder = 31;
const int relayMixer = 32;
const int relayCooker = 33;
// 12v relay
const int relayMixPump = 0;
// 5v relay 
const int relayTray = 29;
const int relayFan = 28;
const int relayWaterPump = 27;
const int relayFlour = 26;
const int relayBPF = 25;
const int relayHose = 24;
const int relayClose= 23;
//
const int relay1 = 34;
const int relay2 = 35;
const int relay3 = 36;
//
const int TrayAngle = 1;
const int servoBFPOpenAngle = 1;
const int servoBFPCloseAngle = 1;
const int servoFlourCloseAngle = 1;
const int servoFlourOpenAngle = 1;
const int servoHoseFirstAngle = 1;
const int servoHoseSecondAngle = 1;
const int servoCloseFirstAngle = 1;
const int servoCloseSecondAngle = 1;
//
const int grindingTime = 1;
const int waterTime = 1;
const int mixerTime = 1;
const int cooketTime = 1;

int state = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin(); 
    Serial.println("Serial Monitor On ");
    lcd.begin(16,2);
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.println("LCD ON");
    lcd.print("Initializing");
    // 
    dht.begin();
    Serial.println("DHT ON");
    // 
    // 
    pwm.begin();
    pwm.setPWMFreq(60);
    Serial.println("Servo Driver On");
    // 
    //  
    pinMode(dehydratorButton, INPUT_PULLUP);
    pinMode(grinderButton, INPUT_PULLUP);
    pinMode(mixerButton, INPUT_PULLUP);
    pinMode(cookerButton, INPUT_PULLUP);
    pinMode(StartButton, INPUT_PULLUP);
    // 
    lcd.setCursor(0, 1);
    lcd.print("Buttons"); 
    Serial.println("Buttons On");


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    pinMode(relayHeater,OUTPUT);
    digitalWrite(relayHeater,HIGH);
    pinMode(relayGrinder,OUTPUT);
    digitalWrite(relayGrinder,HIGH);
    pinMode(relayMixer,OUTPUT);
    digitalWrite(relayMixer,HIGH);
    pinMode(relayCooker,OUTPUT);
    digitalWrite(relayCooker,HIGH);
    pinMode(relayMixPump,OUTPUT);
    digitalWrite(relayMixPump,HIGH);
    pinMode(relayWaterPump,OUTPUT);
    digitalWrite(relayWaterPump,HIGH);
    pinMode(relayTray,OUTPUT);
    digitalWrite(relayTray,HIGH);
    pinMode(relayFlour,OUTPUT);
    digitalWrite(relayFlour,HIGH);
    pinMode(relayBPF,OUTPUT);
    digitalWrite(relayBPF,HIGH);
    pinMode(relayHose,OUTPUT);
    digitalWrite(relayHose,HIGH);
    pinMode(relayClose,OUTPUT);
    digitalWrite(relayClose,HIGH);

    pinMode(relay1,OUTPUT);
    digitalWrite(relay1,HIGH);
    pinMode(relay2,OUTPUT);
    digitalWrite(relay2,HIGH);
    pinMode(relay3,OUTPUT);
    digitalWrite(relay3,HIGH);

    

    lcd.setCursor(0, 1);
    lcd.print("Relays");
    Serial.println("Relays On");

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
        Serial.println("Button 1 pressed");
        dehydratorOn();
        dehydratorOff();
        break;
    case (2):
        Serial.println("Button 2 pressed");
        grinderOn();
        grinderOff();
        break;
    case (3):
        Serial.println("Button 3 pressed");
        mixerOn();
        mixerOff();
        break;
    case (4):
        Serial.println("Button 5 pressed");    
        CookerOn();
        CookerOff();
        break;
    case (5):
        Serial.println("Button 6 pressed");    
        dehydratorOn();
        dehydratorOff();
        grinderOn();
        grinderOff();
        mixerOn();
        mixerOff();
        CookerOn();
        CookerOff();
        Serial.println("Pancake Ready");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pancake Ready"); 
        break;
    case (6):

        break;  
    }
  
      
    state = 0;
}
void dehydratorOn()
{
    Serial.println("Dehydrator Starting");


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrator On");

    digitalWrite(relayTray, LOW);
    Serial.println("relayTray On");
  
    pwm.setPWM(0,0,TrayAngle);
    Serial.println("Tray Initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tray Initiated");

    delay(200);

    lcd.clear();
    lcd.setCursor(0, 0);
    digitalWrite(relayFan, LOW);
    lcd.print("Fan ON");    
    Serial.println("Fan Initiated");

    delay(200);

    lcd.clear();
    lcd.setCursor(0, 0);

    digitalWrite(relayHeater, LOW);
    lcd.print("Heater ON");
    Serial.println("Heater Initiated");

    delay(200);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydration");
    lcd.setCursor(0, 1);
    lcd.print("Starting");
    delay(1000);
    displayTempHumid(2);
}
void displayTempHumid(int time){
  time = time/2;

  for(int i = 0; i < time;i++){
    lcd.clear();  
    int Temp = (int)dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.println(Temp);

    lcd.setCursor(0,0);
    lcd.print("Temperature:");
    lcd.setCursor(0,1);
    lcd.print(Temp);
    delay(1000);

    lcd.clear();  
 
    int Humidity = (int)dht.readHumidity();
    Serial.print("Humidity: ");
    Serial.println(Humidity);

    lcd.setCursor(0,0);
    lcd.print("Humidity:");
    lcd.setCursor(0,1);
    lcd.print(Humidity);  
    delay(1000);
  }
}
void dehydratorOff()
{
    digitalWrite(relayTray, HIGH);
    Serial.println("Tray Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Servo OFF");
    delay(1000);

    digitalWrite(relayFan, HIGH);
    Serial.println("Fan off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan OFF");
    delay(1000);

  
    digitalWrite(relayHeater, HIGH);
    Serial.println("Heater off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heater OFF");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dehydrator OFF");
    delay(500);
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
    for (int i = 0; i < grindingTime; i++)
    {
        digitalWrite(relayGrinder, LOW);
        delay(500);
        digitalWrite(relayGrinder, HIGH);
        delay(1000);
    }
}

void grinderOff()
{
    digitalWrite(relayGrinder, HIGH);
    Serial.println("Grinder Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Grinding OFF");
    delay(500);
}
void mixerOn()
{
    digitalWrite(relayWaterPump, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water pump ON");
    Serial.println("Water On");
    delay(waterTime * 1000);

    digitalWrite(relayWaterPump, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water pump Off");
    Serial.println("Water Off");

    delay(500);

    digitalWrite(relayBPF, LOW);
    Serial.println("servoBFP On");
  
    pwm.setPWM(0,0,servoBFPOpenAngle);
    Serial.println("servo BFP initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BFP Initiated");

    delay(500);

    pwm.setPWM(0,0,servoBFPCloseAngle);
    Serial.println("servo BFP uninitiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BFP UnInitiated");

    digitalWrite(relayBPF, HIGH);
    Serial.println("servoBFP Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoBFP off");

    delay(500);

    digitalWrite(relayFlour, LOW);
    Serial.println("servoFlour On");
  
    pwm.setPWM(0,0,servoFlourOpenAngle);
    Serial.println("servo Flour initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flour Initiated");

    delay(500);

    pwm.setPWM(0,0,servoFlourCloseAngle);
    Serial.println("servo Flour unInitiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flour Closed");

    digitalWrite(relayFlour, HIGH);
    Serial.println("servoFlour Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoFlour off");

    delay(500);

    digitalWrite(relayMixer, LOW);
    Serial.println("mixer On");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("mixer on");

    delay(mixerTime * 1000);

    digitalWrite(relayMixer, HIGH);
    Serial.println("mixer Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("mixer off");

    delay (500);
}
void mixerOff()
{
    digitalWrite(relayWaterPump, HIGH);
    digitalWrite(relayBPF, HIGH);
    digitalWrite(relayFlour, HIGH);
    digitalWrite(relayMixer, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixing OFF");
    Serial.println("mixing Off");
    delay(1000);
}
void CookerOn()
{
    digitalWrite(relayClose, LOW);
    Serial.println("servoClose On");
  
    pwm.setPWM(0,0,servoCloseFirstAngle);
    Serial.println("servo Open initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Open Initiated");

    delay(500);

    digitalWrite(relayClose, HIGH);
    Serial.println("servoOpen Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoOpen off");

    delay(500);

    digitalWrite(relayHose, LOW);
    Serial.println("servoHose On");
  
    pwm.setPWM(0,0,servoHoseFirstAngle);
    Serial.println("servo Hose initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hose Initiated");

    delay(500);

    digitalWrite(relayHose, HIGH);
    Serial.println("servoHose Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoHose off");

    delay(500);

    digitalWrite(relayMixPump, LOW);
    Serial.println("Mixed Pump On");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixed Pump On");

    delay(500);

    digitalWrite(relayMixPump, HIGH);
    Serial.println("Mixed Pump Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixed Pump Off");

    delay(500);

    digitalWrite(relayHose, LOW);
    Serial.println("servoHose On");
  
    pwm.setPWM(0,0,servoHoseSecondAngle);
    Serial.println("servo Hose 2 initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hose 2 Initiated");

    delay(500);
    
    digitalWrite(relayHose, HIGH);
    Serial.println("servoHose 2 Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoHose 2 off");

    delay(500);

    digitalWrite(relayMixPump, LOW);
    Serial.println("Mixed Pump 2 On");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixed Pump 2 On");

    delay(500);

    digitalWrite(relayMixPump, HIGH);
    Serial.println("Mixed Pump 2 Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mixed Pump 2 Off");

    delay(500);

    digitalWrite(relayCooker, LOW);
    Serial.println("Cooker On");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cooker On");

    delay(500);

    digitalWrite(relayClose, LOW);
    Serial.println("servoClose On");
  
    pwm.setPWM(0,0,servoCloseSecondAngle);
    Serial.println("servo Close initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Close Initiated");

    delay(500);

    digitalWrite(relayClose, HIGH);
    Serial.println("servoClose Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoClose off");

    delay(500);
}
void CookerOff()
{
    lcd.clear();
    digitalWrite(relayCooker, HIGH);
    Serial.println("Cooker Off");
    lcd.setCursor(0, 0);
    lcd.print("Cooker OFF");

    digitalWrite(relayClose, LOW);
    Serial.println("servoClose On");
  
    pwm.setPWM(0,0,servoCloseFirstAngle);
    Serial.println("servo Open initiated");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Open Initiated");

    delay(500);

    digitalWrite(relayClose, HIGH);
    Serial.println("servoOpen Off");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("servoOpen off");

    delay(500);
}
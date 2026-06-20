#include <SoftwareSerial.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <LCD.h>
#include <LiquidCrystal.h>
int sensorValue, sensorValue1;
float voltageMax = 4.7;
int sensorMax = 50;
float variabel,kpa, voltage, tekanan_darah, darah1,selisih, darah2, sistole, diastole;
float kpa1, voltage1, tekanan_darah1;
int kpaRangeTopVoltage = 50;
bool tanda;
SoftwareSerial BTserial(0, 1); // RX | TX
LiquidCrystal_I2C lcd(0X3F ,2,1,0,4,5,6,7,3, POSITIVE);


void setup() {
Serial.begin(9600);
BTserial.begin(9600);
tanda = false;
lcd.begin(16,2);
lcd.clear();
}

void loop() {
  //lcd.backlight();
  lcd.setCursor(0,0);

sensorValue = analogRead(A1);
voltage=sensorValue*(voltageMax/sensorMax);
kpa=((voltage/kpaRangeTopVoltage)-0.04)/0.018;
tekanan_darah=kpa*7.500617;


  if (tekanan_darah>180)
     {
     digitalWrite(9,HIGH);
     Serial.print("OPEN THE TUBE");
     lcd.print("OPEN THE TUBE");
     tanda= true;
     }
     
   if ((tekanan_darah < 140) && (tanda == true))
            {
               darah1= tekanan_darah;
               selisih= darah2-darah1;
               darah2= darah1;
                  if (selisih<-0.5)
                     {
                        sistole = darah1;
                        diastole = sistole-40;
                     }
              tanda = false;
           }
 Serial.print('\n');
 Serial.print("  Sistole = ");
 Serial.print(sistole);
 Serial.print('\n');
 delay(300);
 Serial.print("  Diastole = ");
 Serial.print(diastole);
 Serial.print('\n');
 delay(300);
  lcd.print("Sistole =:");
  lcd.print(sistole);
  lcd.setCursor(0,1);
  lcd.print("Diastole =:");
  lcd.print(diastole);
 
  // put your main code here, to run repeatedly:
}

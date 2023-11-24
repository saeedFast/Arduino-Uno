// /*
//  * PIR sensor tester
//  */
 
// int ledPin = 2;                // choose the pin for the LED
// int inputPin = 4;               // choose the input pin (for PIR sensor)
// int pirState = LOW;             // we start, assuming no motion detected
// int val = 0;                    // variable for reading the pin status
 
// void setup() {
//   pinMode(ledPin, OUTPUT);      // declare LED as output
//   pinMode(inputPin, INPUT);     // declare sensor as input
 
//   Serial.begin(9600);
// }
 
// void loop(){
//   val = digitalRead(inputPin);  // read input value
//   if (val == HIGH) {            // check if the input is HIGH
//     digitalWrite(ledPin, HIGH);  // turn LED ON
//     if (pirState == LOW) {
//       // we have just turned on
//       Serial.println(val);
//       Serial.println("Motion detected!");

//       // We only want to print on the output change, not state
//       pirState = HIGH;
//     }
//   } else {
//     digitalWrite(ledPin, LOW); // turn LED OFF
//     if (pirState == HIGH){
//       // we have just turned of
//       Serial.println("Motion ended!");
//       // We only want to print on the output change, not state
//       pirState = LOW;
//     }
//   }
// }




///Original code



#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

// #define buzzer pin
#define buzzer 13

int Input=A1;    //for LPG Sensor
int val;
int max=400;

// int pir=5;    //PIR
// int pirval;

int inputPin = 5;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirval = 0;  

int ldrPin = A0; // 
int LDRReading=0;
int ldrmax=700;
int lEDBrightness=0;

const int ledPin1 = 3; // digital pin 3   for LPG
const int ledPin2 = 2; // digital pin 2   for PIR
const int ledPin3 = 6; // digital pin 6   for LDR



void setup() 
{
  
  pinMode(Input, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin1, OUTPUT); // Here LED is determined as an output or an indicator.
  pinMode(ledPin2, OUTPUT); // Here LED is determined as an output or an indicator.
  pinMode(ledPin3, OUTPUT);
  pinMode(ldrPin, INPUT); // Here LDR sensor is determined as input.
  lcd.begin(16, 2);
  lcd.print("LPG Gas Detector");
  lcd.setCursor(0,1);
  lcd.print("  Ubaid Ullah ");
  delay(2000);

  //Serial.begin(9600);
}

void loop() 
{
  pirval = digitalRead(inputPin);
  if (pirval == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin2, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println(pirval);
      Serial.println("Motion detected!");

      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin2, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }





  LDRReading = analogRead(ldrPin);
  val = analogRead(Input);    //LPG reading
  pirval = analogRead(inputPin);   // PiR Reading
  if (val >= max )
  //|| ldrStatus <= 200
  {
    if (LDRReading > ldrmax){                   // Condition to make LED ON.
      lEDBrightness = map(LDRReading, 0, 1023, 0, 255); // Converting LDR to LED Brightness.
      analogWrite(ledPin3, lEDBrightness); // Writing Brightness to LED.
    }
    else{
      analogWrite(ledPin3, 0);             // If LDR is below threshold make LED OFF.
  }
    if (pirval>50){
     // digitalWrite(ledPin3, HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledPin1, HIGH); // If LDR senses darkness led pin high that means led will glow.    lcd.clear();
      digitalWrite(ledPin2, LOW);
      lcd.print("LPG Leak,PIR:");
      lcd.print(pirval);
      //lcd.print("LPG Leak, Human P");
      //lcd.print(ldrStatus);
      lcd.setCursor(0, 1);
      lcd.print("LPG:");
      lcd.print(val);
      lcd.print(", LDR:");
      lcd.print(LDRReading);
      // delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1500);
      lcd.clear();
      delay(500);
    }
    else{
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledPin1, HIGH); // If LDR senses darkness led pin high that means led will glow.    lcd.clear();
      digitalWrite(ledPin2, LOW);
      lcd.print("LPG Leak");
      //lcd.print(ldrStatus);
      lcd.setCursor(0, 1);
      lcd.print("LPG:");
      lcd.print(val);
      lcd.print(", LDR:");
      lcd.print(LDRReading);
      // delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1500);
      lcd.clear();
      delay(500);
      }
  }
    // Serial.println("NORMAL");
    // Serial.println(val);
    // Serial.println("GAS LEAKING");
    // Serial.println(val);
  else 
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    lcd.clear();
    lcd.print("No LPG Gas");
    lcd.print(pirval);
   // lcd.print(ldrStatus);
    lcd.setCursor(0, 1);
    lcd.print("LPG:");
    lcd.print(val);
    lcd.print(", LDR:");
    lcd.print(LDRReading);
    delay(1500);
    lcd.clear();
    delay(500);
  }
}
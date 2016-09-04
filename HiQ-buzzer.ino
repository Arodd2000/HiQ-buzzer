
#include <SoftwareSerial.h> //include the needed libraries
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/*
HiQ buzzer practice program
written By Alex Rodgers
I wrote this due to the HiQ team I am part of needing practice buzzers.

    ***********************************
    *                                 *
    *       LCD D14 pin------D2       *
    *       LCD D13 pin------D3       *
    *       LCD D12 pin------D4       *
    *       LCD D11 pin------D5       *
    *       P1's button------D6       *
    *       P2's button------D7       *
    *       Blue led(rgb)----D9       *
    *       Green led(rgb)---D10      *
    *       LCD enable pin---D11      *
    *       LCD RS pin-------D12      *
    *       7 seg RX pin-----D13      *
    *                                 *
    ***********************************

*/
const int softwareTx = 13; //define what pin to use for tx to 7 seg display


SoftwareSerial s7s(0, softwareTx); //define what pins to use for 7 seg display serial
const int p1=6; //define all needed variables
const int p2=7; 
const int led1=9;
const int led2=10;
int p1answ=1;
int p2answ=1;
int reading1;
int previous1=HIGH;
int reading2;
int previous2=HIGH;
long p1time=0;
long p2time=0;
long debounce=200;
int timeansw=16;
int led1read=LOW;
int led2read=LOW;
int p1timex=0;
int p2timex=0;
//button 2

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  pinMode(p1, INPUT_PULLUP); //buttons configured as inputs but with a pullup
  pinMode(p2, INPUT_PULLUP);
  pinMode(led1, OUTPUT); //leds configured as outputs
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW); //make sure leds are off
  digitalWrite(led2, LOW);
  
  s7s.begin(9600); //begin communication with display
  Serial.begin(9600); //begin serial communication
  lcd.begin(16, 2); //define how many characters are on the lcd

s7s.write(0x76); //clear display
  s7s.print("-HI-");  //print hi on display
   lcd.setCursor(0, 0);
 lcd.print("HiQ buzzers"); //print to lcd
 lcd.setCursor(0, 1); 
 lcd.print("Written: Alex R");
 Serial.println(""); //now we are printing to serial
 Serial.println("HiQ buzzer practice program");
 Serial.println("Written by Alex Rodgers March, 2016");
 delay(2000); //delay so the message can be read
 s7s.write(0x76); //clear 7 seg display
 lcd.clear(); //clear lcd

}

void loop() {
  reading1=digitalRead(p1); //check pin modes
  reading2=digitalRead(p2);
  led1read=digitalRead(led1);
  led2read=digitalRead(led2);
  if (reading1 == LOW && previous1 == HIGH && p1answ == 1){
    lcd.setCursor(0,0);
    p1answ=2;
    if (timeansw==0){
      p1timex=(millis()-previousMillis);
      if(led2read==LOW){
        digitalWrite(led1, HIGH);
      }
   
   lcd.print("p1 ");
   lcd.print(p1timex/1000);
   lcd.print(".");
   lcd.print(p1timex%1000);
   lcd.println("s late");
   Serial.print("p1 is ");
   Serial.print(p1timex/1000);
   Serial.print(".");
   Serial.print(p1timex%1000, 4);
   Serial.println(" seconds late");
    } else{
      p1timex=((millis()-previousMillis)+((timeansw-1))*1000);
         lcd.print("p1 ");
   lcd.print(p1timex/1000);
   lcd.print(".");
   lcd.print(p1timex%1000);
   lcd.println("s early");
   Serial.print("p1 is ");
   Serial.print("p1 is ");
   Serial.print(p1timex/1000);
   Serial.print(".");
   Serial.print(p1timex%1000, 4);
   Serial.println(" seconds early");
    }
    }
     if (reading2 == LOW && previous2 == HIGH && p2answ == 1){
    p2answ=2;
    if (timeansw==0){
      p2timex=(millis()-previousMillis);
      if(led1read==LOW){
        digitalWrite(led2, HIGH);
      }
      lcd.setCursor(0,1);
   lcd.print("p2 ");
   lcd.print(p2timex/1000);
   lcd.print(".");
   lcd.print(p2timex%1000);
   lcd.print("s late");
   Serial.print("p2 is ");
   Serial.print(p2timex/1000);
   Serial.print(".");
   Serial.print(p2timex%1000, 4);
   Serial.println(" seconds late");
    } else{
      p2timex=((millis()-previousMillis)+((timeansw-1))*1000);
      lcd.setCursor(0,1);
   lcd.print("p2 ");
   lcd.print(p2timex/1000);
   lcd.print(".");
   lcd.print(p2timex%1000);
   lcd.print("s early");
   Serial.print("p2 is ");
   Serial.print(p2timex/1000);
   Serial.print(".");
   Serial.print(p2timex%1000, 4);
   Serial.println(" seconds early");
    }
    }
    
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval && timeansw>0) {
     
        if (timeansw>0){
  timeansw = timeansw-1;
    }
    
    previousMillis = currentMillis;// save the last time you blinked the LED
    
    s7s.write(0x76); //clear display
    s7s.write(0x79); //set cursor
    s7s.write(0x2); //cursor position
    s7s.write(timeansw/10); //write the tens place of time
    if (timeansw >= 10){ //check if time left is more than 10
    s7s.write(0x79); //set cursor
    s7s.write(0x3); //cursor position
    s7s.write(timeansw - 10); //write the one's place of time
    } else{ //if time left is less than 10
    s7s.write(0x79); //set cursor
    s7s.write(0x3); //cursor position
    s7s.write(timeansw); //set time
    }


  }
}

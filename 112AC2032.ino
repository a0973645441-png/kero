/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

const int buttonpin = 2;
const int rLEDPin = 3;
const int gLEDPin = 4;
const int bLEDPin = 5;

int buttonstate = 0;
int ledState = LOW; 
int ledcolor = 0;

bool ButtonPressed = false;
String currentcolor = "led";
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
  pinMode(buttonpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonstate = digitalRead(buttonpin);
  Serial.print("Current Color:");
  Serial.println(currentcolor);

  if (buttonstate == HIGH && !ButtonPressed) {
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
  }
  if (buttonstate == LOW && ButtonPressed) { 
    ButtonPressed = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }

 
  if (ledcolor == 0) {
    currentcolor = "LED off";
    digitalWrite(rLEDPin, HIGH);
    digitalWrite(gLEDPin, HIGH);
    digitalWrite(bLEDPin, HIGH); 
  }
  else if (ledcolor == 1) { 
    // red
    currentcolor = "Red";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, LOW);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 2) {
    // green
    currentcolor = "Green";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, LOW);
      digitalWrite(bLEDPin, HIGH); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 3) {
    // blue
    currentcolor = "Blue";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, LOW); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 4) {
    // yellow
    currentcolor = "Yellow";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, LOW);
      digitalWrite(gLEDPin, LOW);
      digitalWrite(bLEDPin, HIGH); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 5) {
    // purple
    currentcolor = "Purple";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, LOW);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, LOW); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 6) {
    // cyan
    currentcolor = "Cyan";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, LOW);
      digitalWrite(bLEDPin, LOW); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor == 7) {
    // white
    currentcolor = "White";
    if (ledState == LOW) {
      digitalWrite(rLEDPin, LOW);
      digitalWrite(gLEDPin, LOW);
      digitalWrite(bLEDPin, LOW); 
    } else {
      digitalWrite(rLEDPin, HIGH);
      digitalWrite(gLEDPin, HIGH);
      digitalWrite(bLEDPin, HIGH); 
    }
  }
  else if (ledcolor >= 8) {
    ledcolor = 0;
  }
}





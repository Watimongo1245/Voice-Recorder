/*
  LED Toggle with Delay & Interrupt
  led-toggle-interrupt.ino
  Use pushbutton switch to toggle LED with interrupt
 
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#include <avr/sleep.h>

#define SD_ChipSelectPin 53 

TMRpcm audio;
// Define LED and switch connections
const byte ledPin = 6;
const byte buttonPin = 2;
 
// Boolean to represent toggle state
 
volatile bool toggleState = false;
 
void checkSwitch() {
  // Check status of switch
  // Toggle LED if button pressed
 
  if (digitalRead(buttonPin) == LOW) {
    // Switch was pressed
    // Change state of toggle
    toggleState = !toggleState;
    // Indicate state on LED
    //digitalWrite(ledPin, toggleState);
    switch(toggleState){
        case HIGH: sleep_disable();
        digitalWrite(ledPin, HIGH);
        audio.startRecording("testTMR.wav", 16000, A0);
        break;   
        case LOW:digitalWrite(ledPin, LOW);
        audio.stopRecording("testTMR.wav");
        sleep_enable(); sei();sleep_cpu();
        break;
    }
  }
}
 
void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // Set switch pin as INPUT with pullup
  pinMode(buttonPin, INPUT_PULLUP);
 
  // Attach Interrupt to Interrupt Service Routine
  attachInterrupt(digitalPinToInterrupt(buttonPin),checkSwitch, FALLING); 
  Serial.begin(115200);
  
  if (!SD.begin(SD_ChipSelectPin)) {  
    Serial.println("There might be a problem");
    return;
  }else{
    Serial.println("SD OK"); 
  }
  
  audio.CSPin = SD_ChipSelectPin;
}
 
void loop() {
  
interrupts();
}

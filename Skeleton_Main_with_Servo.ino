#include <Servo.h>
#include <SoftwareSerial.h>      // Library Name
#include <DFRobotDFPlayerMini.h> // Library Name

int track = 1;
int rxPin = 2;
int txPin = 3;
int pirPin = 12;
int currentState = LOW;
int servoPin = 9;
int pos = 0;

Servo myServo;                // create Servo object to control a servo. Twelve Servo objects can be created on most boards
SoftwareSerial mySerial(2,3); // Set up and name a new SoftwareSerial object
DFRobotDFPlayerMini myPlayer; // Set up serial com with MP3 player

void setup() {
  pinMode (pirPin, INPUT);    // Checks for PIR motion 
  pinMode (rxPin, INPUT);     // Virtual serial port -- SoftwareSerial library (Digital pin 2)
  pinMode (txPin, OUTPUT);
  Serial.begin(9600);         // Initialize onboard serial monitor to look at PIR readings
  mySerial.begin(9600);       // Sets the Baud rate) for SoftwareSerial serial ports 
  myPlayer.begin(mySerial);   // Initialize DFPlayer 
  myPlayer.volume(20);        // Set DFPlayer volume
  myServo.write(180);
  myServo.attach(9);          // attaches the servo on pin 9 to the Servo object
 }

void loop() {
currentState = digitalRead(12); 

    if (currentState == LOW) {
     Serial.println("MOTION NOT DETECTED");
     Serial.print("Position ");
     Serial.println(pos);
    }
    
    else {
      if (currentState == HIGH) {
        Serial.print("MOTION DETECTED, Playing Track ");
        Serial.println(track);
        Serial.print("Position ");
        Serial.println(pos);
        myPlayer.play(track); 
        track ++;
         if (track == 6) {
           track = 1;
         }
    }
    
    for (pos = 180; pos > 45; pos--) { 
       myServo.write(pos);        
       delay(15);
    }
 
 delay(6000);

    for (pos = 45; pos < 180; pos++) {  
       myServo.write(pos);                 
       delay(20);      
    }
  }
}


   

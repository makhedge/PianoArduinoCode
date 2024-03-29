
#include <Servo.h>

Servo myservo1; //Left side, contols main room
Servo myservo2; //Right side, controls piano and lobby lights

int power = A0; //Voltage for input from piano
int input = A1; //Received input from piano
int trigger = 1000;
int output = 11; //Sends output to relay for music and lights
int elevator = 7 // sends output to elevator relay
int last = 0;
unsigned long timer = 0;

void setup() {
  pinMode(input, INPUT_PULLUP); //Trigger from piano keys
  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);
  pinMode(power, OUTPUT);
  digitalWrite(power, LOW);
  pinMode(elevator, OUTPUT);
  digitalWrite(elevator, LOW);


  myservo1.attach(13);//attachs the servo on pin 13 to servo object
  myservo2.attach(12);//attachs the servo on pin 12 to servo object
  myservo1.write(0); // testing lights are working
  myservo2.write(80);// testing lights are working
  delay(500);
  myservo1.write(45);// setting servos back to neutral position
  myservo2.write(45);// setting servos back to neutral position
  
  Serial.begin(9600); //opens serial port and sets data rate to 9600 bps

}

void loop() 

{
  
  trigger = analogRead(A1);
  Serial.println(analogRead(A1));

  if (trigger < 100 && last == 0)
  {
    Serial.println("Piano Triggered");
    digitalWrite(output, HIGH); //turn on trigger effects
    digitalWrite(elevator,HIGH);// open elevator 
    myservo2.write(0); //turn off piano lights
    delay(500);
    myservo2.write(45);
    last = 1;
    timer = millis();
  }

  if (trigger > 100 && last == 1)
  {
    Serial.println("Piano Trigger ended");
    digitalWrite(output, LOW); //turn off trigger effects
    myservo2.write(80); //turn piano lights back on
    delay(500);  
    myservo2.write(45); 
    last = 0;
    timer = millis();
  }

  if ((millis() - timer) > 9000) //This if statement turns off the trigger effects if the button is held for 10 seconds
  {
    Serial.println("10 second reset");
    digitalWrite(output, LOW); //turn off trigger effects
  }
}

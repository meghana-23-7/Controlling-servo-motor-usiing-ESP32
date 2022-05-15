#include <ESP32Servo.h> 
 
Servo myservo;  
 
int servoPin = 18;      //this is pin we give as control to servo
int potPin = 34;        
int ADC_Max = 4096;    

int val;    // variable to read the value from the analog pin
 
void setup()
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);   // attaches the servo on pin 18 to the servo object
                                         }
 
void loop() {
  val = analogRead(potPin);            
  val = map(val, 0, ADC_Max, 0, 180);     
  myservo.write(val);                  // set the servo position according to the scaled value
  delay(200);                          
}

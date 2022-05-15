# Controlling-servo-motor-usiing-ESP32
Using ESP32 to control the movement of the motor shaft.

## Task number: 04
## Task name: Controlling servo motor with ESP32.

## Reference
https://dronebotworkshop.com/esp32-servo/

## Components used
micro servo motor, ESP32, potentiometer, servo power supply, DC jack, jumper wires, breadboard.

## Connections
Sweep: connect ground and VCC wires of servo motor to ground and VCC of ESP32 respectively. Next, connect the control input pin of the servo to GPIO18 of the ESP32.

Knob: connect middle wire of potentiometer to GPIO34 of ESP32, and connect one of the other two to ground and 3V pins of ESP32. Connect the ground of the servo motor and ground of the ESP32 to the ground pins of the DC power supply. Connect control pin of servo to GPIO18 of ESP32.

Web remote controlled: connect ground and VCC wires of servo motor to ground and VCC of ESP32 respectively. Next, connect the control input pin of the servo to GPIO18 of the ESP32. Once the code is uploaded, it prints an IP address on the serial monitor. Copy this and open it on any device connected to the internet, now monitor the movement of the servo motor shaft based on the slider.

## Theory 
Servo motors have an inbuilt servomechanism with a feedback loop to allow precise positioning of the motor shaft. It has 3 pins, brown for ground, red for VCC and orange for PWM input, we use this pin to provide signal hence control the movement of the motor shaft. We are using ESP32 to provide PWM input to control input of the servo. 
In the knob sketch, we use a potentiometer to position the motor shaft. It moves as the position of the potentiometer is changed.
A web page was created with a slider on it, and is managed using the IP address. 

## Code
### Sweep
https://github.com/meghana-23-7/Controlling-servo-motor-usiing-ESP32/blob/main/sketch_task4sweepa.ino

### Knob
https://github.com/meghana-23-7/Controlling-servo-motor-usiing-ESP32/blob/main/sketch_task4knob.ino
 
### Web controlled
https://github.com/meghana-23-7/Controlling-servo-motor-usiing-ESP32/blob/main/sketch_task4WebControl.ino

## Problems faced
Servo was rotating full 360 degrees on its own, it was because of some loose connection, when connections were rechecked it worked as directed in the code.
When the server page was opened on the computer, there was no movement on the servo. Opened the same on mobile phone, it worked as the slider was slid.

## Output
Servo made a proper 180 degree rotation and then did the same in reverse direction.
https://drive.google.com/open?id=1DGTOdFvdRKjr1z-95rhBGvuoUigH5_NF&authuser=0

Servo motor shaft changed its position as potentiometer value was changed.
https://drive.google.com/open?id=1-WGQ87_-YVjjq_2hq1i2zRRYELsAY4VW&authuser=0

Motor shaft changed its position as directed on web page.
https://drive.google.com/open?id=1-Vwty4dQvmb-0hwrZtCaGimeaCquEa2h&authuser=0





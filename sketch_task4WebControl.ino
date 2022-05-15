#include <WiFi.h>
#include <ESP32Servo.h>
 
Servo myservo; 
 
static const int servoPin = 18;
 
const char* ssid     = "Marvel-Guest";
const char* password = "";
 
// Web server on port 80 (http)
WiFiServer server(80);
 
String header;  //stores http request

String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
 
unsigned long currentTime = millis(); //time right now
unsigned long previousTime = 0;       //time before
const long timeoutTime = 2000;         //time in milliseconds
 
void setup() {
  
  // Allow allocation of all timers for servo library
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  myservo.setPeriodHertz(50);  //PWM frequency
  
  myservo.attach(servoPin,500, 2400);    //500 is the minimum position and 2400 is the //maximum position
  
  Serial.begin(115200);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
 
void loop(){
  
  // Listen for incoming clients
  WiFiClient client = server.available();   
  
  // Client Connected
  if (client) {                             
    // Set timer references
    currentTime = millis();
    previousTime = currentTime;
   
    Serial.println("New Client."); 
    
    // String to hold data from client
    String currentLine = ""; 
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you get two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:

          if (currentLine.length() == 0) {
       
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
 
            // Display the HTML web page
            
            // HTML Header
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto; }");
            client.println(".slider { -webkit-appearance: none; width: 300px; height: 25px; border-radius: 10px; background: #ffffff; outline: none;  opacity: 0.7;-webkit-transition: .2s;  transition: opacity .2s;}");
            client.println(".slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; border-radius: 50%; background: #ff3410; cursor: pointer; }</style>");
            
            // Get JQuery
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Page title
            client.println("</head><body style=\"background-color:#70cfff;\"><h1 style=\"color:#ff3410;\">Servo Control</h1>");
            
            // Position display
            client.println("<h2 style=\"color:#ffffff;\">Position: <span id=\"servoPos\"></span>&#176;</h2>"); 
                     
            // Slider control
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
            
            // Javascript
            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
            
            // End page
            client.println("</body></html>");     
            
            // GET data
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              
              // String with motor position
              valueString = header.substring(pos1+1, pos2);
              
              // Move servo into this new position
              myservo.write(valueString.toInt());
              
              // Print value to serial monitor
              Serial.print("Val =");
              Serial.println(valueString); 
            }         
            // The HTTP response ends with another blank line
            client.println();
            
            // Break out of the while loop
            break;
          
          } else { 
            // New line is received, clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

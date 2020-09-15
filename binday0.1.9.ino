// binday 2020

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

int lastState = HIGH; // the previous state from the input pin
int currentState;

unsigned int loopcount;

// Change to suit your number of pixels and output pin on the ESP8266


//D1=5, D2 = 4, D7=13, D6 = 12

#define LEDWHITE 5
#define LEDRED 4
#define LEDBLUE 13
#define LEDGREEN 12

#define BTN_PIN 14

// Change to add in your WiFi SSID, Password
const char* ssid = "wifi-ssid";
const char* password = "wifi-pass";

int count;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LEDWHITE, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);

  pinMode(BTN_PIN, INPUT_PULLUP);

  // Boot up ESP8266, setup serial comms and try to connect to wifi
  Serial.begin(115200);
  Serial.println("Booting Up");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection to WiFi Failed! Retrying...");
      digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW
      delay(1000);                      // Wait for a second
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(1000);
  }

  // Set LED colour to dim white when booted and connected to your wifi with a valid IP, print the IP to serial
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
  
  digitalWrite(LED_BUILTIN, LOW);
  
}



void loop() {

    loopcount++;

    Serial.println("Running Loop");

    Serial.println("loopcount:");
    
    Serial.println(loopcount);


      currentState = digitalRead(BTN_PIN);

      delay(100);

      if(lastState == LOW && currentState == HIGH) {
        Serial.println("==== BUTTON PRESSED ====");
        
        // API clear
            

        HTTPClient http;
        const int httpPort = 1880;
        if (! http.begin("http://your-domain.com/api/v1/clear/hash")) {
      
        Serial.println("Connection Failed To Clear Endpoint");
      
        } else {


        Serial.println("Connected To Endpoint");
      
       int httpCode = http.GET();
      
        // Check we're getting a HTTP Code 200
      
        if (httpCode = HTTP_CODE_OK) {
          Serial.println("Connected To Endpoint: 200");    
          
          String payload = http.getString();

          Serial.println("payload: " + payload);

            if (payload == "cleared") {

            Serial.println("bin is cleared");

            digitalWrite(LEDWHITE, HIGH);   // set the LED on
            digitalWrite(LEDRED, LOW);
            digitalWrite(LEDGREEN, LOW);
            digitalWrite(LEDBLUE, LOW);
          
            }
          }

          else {

            Serial.println("FAILED Connect To Clear Endpoint");      

          }

        }

        // end API clear
        
        delay(5000);
      } 
      // save the the last state
      lastState = currentState;



    if (loopcount == 1) {

      HTTPClient http;

      const int httpPort = 1880;

      if (! http.begin("http://yourdomin.com/api/v1/schedule/hash")) {
      
      Serial.println("Connection Failed To Endpoint");
      
      digitalWrite(LEDRED, HIGH);   
      delay(500);
      digitalWrite(LEDRED, LOW);
      delay(500);
    
    } else {
      
      Serial.println("Connected To Endpoint");
      
      int httpCode = http.GET();
      
        // Check we're getting a HTTP Code 200
      
        if (httpCode = HTTP_CODE_OK) {
          Serial.println("Connected To Endpoint: 200");    
          
          String payload = http.getString();

          Serial.println("payload: " + payload);

          if (payload == "clear") {

          Serial.println("today is clear");

          digitalWrite(LEDWHITE, HIGH);   // set the LED on
          digitalWrite(LEDRED, LOW);
          digitalWrite(LEDGREEN, LOW);
          digitalWrite(LEDBLUE, LOW);
            
          }

          else if (payload == "both") {

          Serial.println("today is both");

          digitalWrite(LEDRED, HIGH);
          digitalWrite(LEDBLUE, HIGH);
          digitalWrite(LEDWHITE, LOW);
          digitalWrite(LEDGREEN, LOW);
            
            
          }

          else if (payload == "trash") {

          Serial.println("today is trash");
          

          digitalWrite(LEDRED, HIGH);
          digitalWrite(LEDWHITE, LOW);
          digitalWrite(LEDGREEN, LOW);
          digitalWrite(LEDBLUE, LOW);
   
          }          
          
          else if (payload == "yard") {

          Serial.println("today is yard");

          
          digitalWrite(LEDGREEN, HIGH);
          digitalWrite(LEDWHITE, LOW);
          digitalWrite(LEDRED, LOW);
          digitalWrite(LEDBLUE, LOW);
            
            
          }

           

        }

      
    

    // Test LEDs

    
    
    // Cleanup
    http.end();

    
    
  }

  } // loopcount == 1

  
  
  // > Delay in 0.5 Seconds to hit api
  if (loopcount > 10) {

  loopcount = 0;

  }

  // Loop Delay
  delay(500);

}
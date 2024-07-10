/*
TODO
- change cred to array
- fill cred.h.example
- add mac address
- add degugmode for println

 */



#include <Arduino.h>

#include <ESP8266WiFi.h>

// fill your webcredentials in this file
// see cred.h.example
#include <cred.h>  

// function declarations:
bool conWiFi();

void setup() {

  Serial.begin(115200);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Start setup.");

  conWiFi();  

  Serial.println("Setup complete");
  Serial.println("");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// function definitions:
bool conWiFi(){
  Serial.println(">");
  Serial.println(">");
  Serial.print("Connecting to ");
  WiFi.disconnect();
  delay(2000);

  WiFi.mode(WIFI_AP_STA);
  bool con = false;

  WiFi.begin(ssidA, pwA);

  Serial.println("  WiFi > Try to connect to default WiFi: ");
  Serial.print("  WiFi >   " + String(ssidA) + " ");
  for (int i = 0; i <=15; i++){
    delay(500);
    Serial.print(".");
    if(WiFi.status() == WL_CONNECTED){
      con = true;
      Serial.print("  WiFi > Connected to ");
      Serial.println(ssidA);
      break;
    }
  } 
  if(!con){
    Serial.println();
    
    WiFi.begin(ssidB, pwB);
    Serial.println("  WiFi > Try to Connect to alternative WiFi: ");
    Serial.print("  WiFi >   " + String(ssidB) + " ");
    for (int i = 0; i <=15; i++){
      delay(500);
      Serial.print(".");
      if(WiFi.status() == WL_CONNECTED){
        con = true;
        Serial.print("  WiFi > Connected to ");
      Serial.println(ssidB);
        break;
      }
    }
  }
  Serial.println();
  
  if(con){
    Serial.print("  WiFi > Station IP Address: ");
    Serial.println(WiFi.localIP());

    String s = WiFi.macAddress();
    s.replace(":", "");

    s.toCharArray(clientID, 13);
    Serial.println("ClientID: " + s);

    Serial.println();    
  }else{
    Serial.print("  WiFi > ERROR no connection!");
    Serial.println(); 
  }

  return con;
}
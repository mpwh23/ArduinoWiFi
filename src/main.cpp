#include <Arduino.h>

#include <ESP8266WiFi.h>

// fill your webcredentials in this file
// see cred.h.example
#include <cred.h>  

// replace
char clientID[18] = "esp_v1           ";

// networks
// u_int8_t num_nw = sizeof(nw)/sizeof(nw[0]);

// function declarations:
bool conWiFi();
int strongest(cred);

void setup() {

  Serial.begin(115200);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Start setup.");

  conWiFi();  

  Serial.println("Setup done");

    
    Serial.println("");

    Serial.println();

    


    Serial.println("blub");
 
    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();


  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}


// function definitions:
int strongest(cred lst[]){
  int s = -100;
  int pos = -1;

  for(u_int8_t j = 0; j < num_nw; j++){
    if(strength[j] != 0 && strength[j] > s){
      s = strength[j];
      pos = j;
    }
  }

  return pos;
}

bool conWiFi(){
  Serial.println(">");
  Serial.println(">");
  //Serial.print("Connecting to ");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("> start scan");
  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("> Scan done");

  bool con = false;

  if (n == 0) {
        Serial.println(">> no networks found");
    } else {
      Serial.print(">> ");
      Serial.print(n);
      Serial.println(" networks found");

      int count = 0;
      
      // store strength to networks
      for (int i = 0; i < n; ++i) {
        for(u_int8_t j = 0; j<(num_nw);j++){
          if (strcmp(WiFi.SSID(i).c_str(), nw[j].ssid) == 0) {
            strength[j] = WiFi.RSSI(i);
            count++;
          }
        }
      }

      Serial.print(">> ");
      Serial.print(count);
      Serial.println(" networks matching stored credentials");

      // try to connect
      
      int sel = strongest(nw);

      while(sel > -1){
        WiFi.begin(nw[sel].ssid, nw[sel].pw);
        Serial.print("  WiFi > Try to connect to: ");
        Serial.print(nw[sel].ssid);
        for (int i = 0; i <=15; i++){
          delay(500);
          Serial.print(".");
          if(WiFi.status() == WL_CONNECTED){
            con = true;
            Serial.println();
            Serial.print("  WiFi > Connected to ");
            Serial.print(nw[sel].ssid);
            sel = -1;
            break;
          }
        } 
        if(!con){
          // fail to connect, set strength to 0
          strength[sel] = 0;
          sel = strongest(nw);
          Serial.println();
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
      Serial.println("  WiFi > ClientID: " + s);

      Serial.println();    
    }else{
      Serial.print("  WiFi > ERROR no connection!");
      Serial.println(); 
    }

    return con;
}
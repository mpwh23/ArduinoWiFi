#include <Arduino.h>

#include <ESP8266WiFi.h>

// fill your webcredentials in this file
// see cred.h.example
#include <cred.h>  

// replace
char clientID[18] = "esp_v1           ";

// function declarations:
bool conWiFi();
int strongest();

void setup() {

  Serial.begin(115200);
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println();
  Serial.println();
  Serial.println("------ Start setup ------");
  Serial.println();

  conWiFi();  

  Serial.println("------ Setup done ------");
  Serial.println();
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}


// function definitions:
int strongest(){
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
  Serial.println("  ┌─[conWiFi]");
  //Serial.print("Connecting to ");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("  ├─┬─[start scan for available networks]");
  
  int n = WiFi.scanNetworks();  // return the number of networks found.
  
  bool con = false;

  if (n == 0) {
        Serial.println("  │ ├─> no networks found");
        Serial.println("  ├─┴─[scan done");
    } else {
      Serial.printf(   "  │ ├─> %2d networks found", n);
      Serial.println();

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

      Serial.printf( "  │ ├─> %2d networks matching stored credentials", count);
      Serial.println();
      Serial.println("  │ └─[scan done]");

      // Delete the scan result to free memory for code below.
      WiFi.scanDelete();

      // try to connect
      int sel = strongest();

      while(sel > -1){
        WiFi.begin(nw[sel].ssid, nw[sel].pw);
        Serial.printf("  ├───> Try to connect to: %-32.32s ", (nw[sel].ssid));

        for (int i = 0; i <=15; i++){
          delay(500);
          Serial.print(".");
          if(WiFi.status() == WL_CONNECTED){
            con = true;
            Serial.println(" OK");
            Serial.printf("  ├───> Connected to %s", nw[sel].ssid);
            sel = -1;
            break;
          }
        } 
        if(!con){
          // fail to connect, set strength to 0
          strength[sel] = 0;
          sel = strongest();
          Serial.println(" FAIL");
        }
      }
    }

    String s = WiFi.macAddress();
    s.replace(":", "");
    s.toCharArray(clientID, 13);
      
    if(con){
      Serial.println("");
      Serial.println("  └─┬─[conection successfull]");
      Serial.printf( "    ├─> Station ID: %s", clientID);
      Serial.println();
      Serial.print(  "    └─> Station IP: ");
      Serial.println(WiFi.localIP());

      Serial.println();    
    }else{
      Serial.println("  └─> ERROR no connection!");
    }

    return con;
}
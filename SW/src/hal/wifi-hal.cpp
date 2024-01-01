#include "hal/wifi-hal.h"

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <hal/SPIFFS-hal.h>

WiFiClient client;

extern char spotify_token[40];
extern char spotify_client_id[40];
extern char spotify_client_secret[40];
extern char spotify_redirect_uri[40];


void SetupWifiManager(){
  MountFileSystem();

  WiFiManagerParameter spotify_custom_client_id("id", "client id", spotify_client_id, 40);
  WiFiManagerParameter custom_spotify_token("token", "spotify token", spotify_token, 40);
  WiFiManagerParameter custom_spotify_client_secret("secret", "spotify client secret", spotify_client_secret, 40);
  WiFiManagerParameter custom_spotify_redirect_uri("Uri", "spotify redirect Uri", spotify_redirect_uri, 40);

  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  // wifiManager.setSTAStaticIPConfig(IPAddress(192, 168, 2, 164), IPAddress(192, 168, 2, 1), IPAddress(255, 255, 255, 0));
  wifiManager.addParameter(&spotify_custom_client_id);
  wifiManager.addParameter(&custom_spotify_token);
  wifiManager.addParameter(&custom_spotify_client_secret);
  wifiManager.addParameter(&custom_spotify_redirect_uri);

  
  // wifiManager.resetSettings(); //reset settings - for testing

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep in seconds
  // wifiManager.setTimeout(600);


  if (!wifiManager.autoConnect("AutoConnectAP", "password")) { //change to have different wifi name and default password
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  Serial.println("connected...");
  strcpy(spotify_client_id, spotify_custom_client_id.getValue());
  strcpy(spotify_token, custom_spotify_token.getValue());
  strcpy(spotify_client_secret, custom_spotify_client_secret.getValue());
  strcpy(spotify_redirect_uri, custom_spotify_redirect_uri.getValue());

 
  PrintParameterInformation(); 
  SaveConfig();


  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  
}

void PrintParameterInformation() {
 Serial.println("The values in the file are: ");
  Serial.println("\tspotify client id : "    + String(spotify_client_id));
  Serial.println("\tspotify token : "        + String(spotify_token));
  Serial.println("\tspotify client secret: " + String(spotify_client_secret));
  Serial.println("\tspotify redirect uri : " + String(spotify_redirect_uri));
}


void WifiLoop(){
  static unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  const uint16_t interval = 3000;
  // if WiFi is down, try reconnecting
  if ((   WiFi.status() != WL_CONNECTED) 
      && ((currentMillis - previousMillis) >=interval)) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    delay(1000);
    Serial.println("local ip");
    Serial.println(WiFi.localIP());

    previousMillis = currentMillis;
  }
}
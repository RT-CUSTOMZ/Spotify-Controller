#include <hal/SPIFFS-hal.h>
#ifdef ESP32
  #include <SPIFFS.h>
#endif

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

static bool shouldSaveConfig = false;
//define your default values here, if there are different values in config.json, they are overwritten.
extern char spotify_token[40];
extern char spotify_client_id[40];
extern char spotify_client_secret[40];
extern char spotify_redirect_uri[40];

void SaveConfig(){
  if (shouldSaveConfig) {
    Serial.println("saving config");

    DynamicJsonDocument json(1024);
    json["spotify_client_id"] = spotify_client_id;
    json["spotify_token"] = spotify_token;
    json["spotify_client_secret"] = spotify_client_secret;
    json["spotify_redirect_uri"] = spotify_redirect_uri;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    serializeJson(json, Serial);
    serializeJson(json, configFile);
    configFile.close();
  }
}

void MountFileSystem(){
  if (SPIFFS.begin(true)) {
    if (SPIFFS.exists("/config.json")) {
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);


        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if ( ! deserializeError ) {
          strcpy(spotify_client_id, json["spotify_client_id"]);
          strcpy(spotify_token, json["spotify_token"]);
          strcpy(spotify_client_secret, json["spotify_client_secret"]);
          strcpy(spotify_redirect_uri, json["spotify_redirect_uri"]);
        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }

    // SPIFFS.format();    //clean FS, for testing
}

void saveConfigCallback () {
  shouldSaveConfig = true;
}

#include <Arduino.h>

#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"

#include "pinconfig.h"

#include "spotify_functions/button-play-and-pause.h"
#include <SpotifyESP32.h>

char spotify_token[40];
char spotify_client_id[40];
char spotify_client_secret[40];
char spotify_redirect_uri[40];

void change_volume( uint8_t volume);
using namespace Spotify_types;

char refresh_token[] = "AQDq-bdIe6iL5z_88wkmpfFV-Yy2Zja_nu7WpjvM3hgegk_HbNDgdDaoEb_Y9Xk-JbOkPYzPwNRSWlPeh7SkyY7MAyNSArA0pQMqECGaEGSvfnVsVd3zUnLwVOWjT07jgxY";

Spotify sp(refresh_token, 
           spotify_redirect_uri, 
           spotify_client_id, 
           spotify_client_secret, 
           false
        );//Set last Parameter to true to get more debug information


void setup() {
  init_pins();
  Serial.begin(460800); 
  delay(100);
  InitButtons();
  ledOn(led_yellow_pin); //Just so I know flashing worked   
  SetupWifiManager();

  Serial.print("Current Track: ");
  Serial.print(sp.current_track_name());
  Serial.print(" by ");
  Serial.println(sp.current_artist_names());
  Serial.println("--------------------");
  
  auto reply = sp.available_devices();

  Serial.println(reply.reply);

  // auto reply2 = sp.currently_playing();
  // Serial.println(reply2.reply);
  Serial.println("--------------------");

  auto reply2 = sp.is_playing();
  Serial.println(reply2);

  
  // print_response(sp.shuffle(SHUFFLE_ON));
}

void loop() {
  readEncoder();
  printDelta();
  ButtonLoop();
  readEncoder();
  WifiLoop();
  readEncoder();

}



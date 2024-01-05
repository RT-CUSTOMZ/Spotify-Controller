#define SSD1306_NO_SPLASH
#include <Arduino.h>

#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"

#include "pinconfig.h"

#include "spotify_functions/button-play-and-pause.h"
#include "SpotifyESP32.h"
#include <TaskScheduler.h>

char spotify_token[40];
char spotify_client_id[40];
char spotify_client_secret[40];
char spotify_redirect_uri[40];

void change_volume( uint8_t volume);
using namespace Spotify_types;

// Scheduler
Scheduler ts;

char refresh_token[] = "AQDq-bdIe6iL5z_88wkmpfFV-Yy2Zja_nu7WpjvM3hgegk_HbNDgdDaoEb_Y9Xk-JbOkPYzPwNRSWlPeh7SkyY7MAyNSArA0pQMqECGaEGSvfnVsVd3zUnLwVOWjT07jgxY";

Spotify sp(refresh_token, 
           spotify_redirect_uri, 
           spotify_client_id, 
           spotify_client_secret, 
           false
        );//Set last Parameter to true to get more debug information

//Tasks
#define PERIOD1 500
#define DURATION1 20
Task tDisplay ( PERIOD1 * TASK_MILLISECOND, DURATION1 / PERIOD1, &DisplayLoop, &ts, true );

#define PERIOD2 1000
#define DURATION2 1
Task tWifi ( PERIOD2 * TASK_MILLISECOND, DURATION2 / PERIOD2, &WifiLoop, &ts, true );



void setup() {

  InitPins();
  Serial.begin(460800); 
  
  while (!Serial)
     delay(10);
  

  InitButtons(); 
  InitWifiManager();
  InitDisplay();
  
  auto is_playing = sp.is_playing();
  Serial.println((is_playing)?"currently playing":"not playing");

  if(is_playing){
  Serial.print("Current Track: ");
  Serial.print(sp.current_track_name());
  Serial.print(" by ");
  Serial.println(sp.current_artist_names());

  }
  
  auto reply = sp.available_devices();

  // Serial.println(reply.reply);

  // auto is_playing = sp.currently_playing();
  // Serial.println(is_playing.reply);
  Serial.println("--------------------");
}

void loop() {
  ts.execute();
  EncoderLoop();
  ButtonLoop();
}




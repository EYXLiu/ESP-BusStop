#include <Arduino.h>
#include <WiFi.h>
#include <lcd.hpp>
#include <schedule.hpp>
#include <scrolling.hpp>
#include <http.hpp>

const char* ssid = "Wokwi-GUEST";
LCD *lcd;
LCD *secondaryLcd;
Schedule* schedule;
Scrolling* scrolling;
Http* http;

enum DisplayState {
  STATE_WIFI_CONNECT,
  STATE_FETCH,
  STATE_DISPLAY,
  STATE_ERROR
};

DisplayState state = STATE_WIFI_CONNECT;

unsigned long lastFetch = 60000;
unsigned long lastDisplay = 2000;
unsigned long lastSecondary = 1000;

constexpr unsigned long FETCH_INTERVAL = 60000;
constexpr unsigned long DISPLAY_INTERVAL = 2000;
constexpr unsigned long DISPLAY_SECONDARY = 100;

bool fetchSchedule() {
  String response;

  if (!http->getRoute(BUS_STOP, response)) {
    Serial.println("http failure");
    return false;
  }

  if (schedule) delete schedule;
  if (scrolling) delete scrolling;
  schedule = new Schedule(response, 20);
  scrolling = new Scrolling(response, 16);

  if (schedule->getError() || scrolling->getError()) {
    Serial.println("schedule failure");
    if (schedule) delete schedule;
    if (scrolling) delete scrolling;
    schedule = nullptr;
    scrolling = nullptr;
    return false;
  }

  return true;
}

void setup() {
  Serial.begin(115200);

// setup wifi
  WiFi.begin(ssid);

  // setup lcd
  lcd = new LCD(0x27, 20, 4);
  secondaryLcd = new LCD(0x28, 16, 2);

  // setup http
  String url = String("http://") + MAC_IP + ":8080";
  http = new Http(url.c_str());
}

void loop() {
  unsigned long now = millis();

  switch (state) {
    case STATE_WIFI_CONNECT:
      if (WiFi.status() == WL_CONNECTED) {
        lcd->LCD_ClrScr();
        state = STATE_FETCH;
      }
      lcd->LCD_PrintLCD("WAITING FOR WIFI", "CONNECTION", "", "");
      secondaryLcd->LCD_PrintLCD("Waiting", "");
      break;

    case STATE_FETCH:
      if (now - lastFetch >= FETCH_INTERVAL) {
        lastFetch = now;

        if (fetchSchedule()) {
          state = STATE_DISPLAY;
        } else {
          state = STATE_ERROR;
        }
      }
      break;

    case STATE_DISPLAY:
      if (!schedule || !scrolling || now - lastFetch >= FETCH_INTERVAL) {
        state = STATE_FETCH;
        break;
      }

      if (now - lastDisplay >= DISPLAY_INTERVAL) {
        lastDisplay = now;

        lcd->LCD_PrintLCD(
          schedule->getFirstBuffer(),
          schedule->getSecondBuffer(),
          "",
          schedule->getBottomBuffer()
        );
        schedule->Update();
      }
      if (now - lastSecondary >= DISPLAY_SECONDARY) {
        lastSecondary = now;
        
        secondaryLcd->LCD_PrintLCD(
          scrolling->getFirstBuffer(),
          scrolling->getSecondBuffer()
        );
        scrolling->Update();
      }
      break;
    
    case STATE_ERROR:
      lcd->LCD_PrintLCD(
        "NO DATA",
        "RETRYING...",
        "",
        ""
      );
      secondaryLcd->LCD_PrintLCD(
        "NO DATA",
        "RETRYING..."
      );

      if (now - lastFetch >= FETCH_INTERVAL) {
        lastFetch = now;
        state = STATE_FETCH;
      }
      break;
  }
}

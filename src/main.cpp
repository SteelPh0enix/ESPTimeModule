#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <string_view>
#include "bsp.hpp"
#include "credentials.hpp"
#include "delayed_task.hpp"
#include "scheduler.hpp"
#include "time_requester.hpp"

constexpr std::string_view ENDPOINT_URL = "http://worldtimeapi.org/api/timezone/Europe/Warsaw";

void request_time(std::string_view endpoint) {
  WiFiClient wifi_client;
  HTTPClient http;
  http.setUserAgent("twoj stary pijany");
  http.begin(wifi_client, endpoint.data());

  int response_code = http.GET();
  Serial.print("Response code: ");
  Serial.println(response_code);

  Serial.print("Response: ");
  Serial.println(http.getString());
}

void connect_to_wifi(std::string_view ssid, std::string_view password) {
  WiFi.begin(ssid.data(), password.data());
  Serial.print("Connecting to ");
  Serial.print(ssid.data());

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    toggle_board_led();
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected! IP: ");

  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(74880);
  pinMode(LED_BUILTIN, OUTPUT);
  disable_board_led();
  Serial.println("Hello, world!");

  // connect_to_wifi(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  // request_time(ENDPOINT_URL);
}

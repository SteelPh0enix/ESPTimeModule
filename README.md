# Time module API

ESP communicates with external MCU via simple UART API.
Every request and response ends with standard UNIX newline character `\n`.

Available requests with possible responses from ESP:

## WIFI_STATUS command

Responds with `OK` if ESP is connected to WiFi

Responds with `NOT_CONNECTED` if ESP is not connected to WiFi.

## GET_TIME command

Responds with current time and date in format `YYYY-MM-DD HH:MM:SS` (with trailing zeros, if any) if connected to WiFi and request to the time server is successful.

Responds with `REQUEST_ERROR:X` if request fails, where `X` is replaced with error code (signed base-10 decimal, negative means internal ESP request error, positive means HTTP error).

Responds with `NO_WIFI` if not connected to wifi.

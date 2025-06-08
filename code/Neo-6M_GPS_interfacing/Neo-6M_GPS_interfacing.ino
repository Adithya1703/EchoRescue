#include <HardwareSerial.h>

/*
Serial output data :

| Field         | Value       | Description                                              |
| ------------- | ----------- | -------------------------------------------------------- |
| `$`           | `$`         | Every NMEA sentence starts with the `$` character        |
| Sentence ID   | `GPRMC`     | Global Positioning Recommended Minimum Coordinates       |
| Time          | `123519`    | UTC time: `12:35:19` (hhmmss)                            |
| Status        | `A`         | Status: `A = Active`, `V = Void`                         |
| Latitude      | `4807.038`  | Latitude: `48° 07.038′`                                  |
| N/S Indicator | `N`         | Hemisphere: `N = North`, `S = South`                     |
| Longitude     | `01131.000` | Longitude: `11° 31.000′`                                 |
| E/W Indicator | `E`         | Hemisphere: `E = East`, `W = West`                       |
| Speed         | `022.4`     | Speed over ground: `22.4 knots`                          |
| Track Angle   | `084.4`     | Course over ground: `84.4°` (in degrees from true north) |
| Date          | `230394`    | Date: `23rd March 1994` (DDMMYY)                         |
| Mag Variation | `003.1`     | Magnetic variation: `3.1°`                               |
| Mag Var Dir   | `W`         | Magnetic variation direction: `W = West`, `E = East`     |
| Checksum      | `*6A`       | Checksum: Optional, used for data integrity verification |

*/

HardwareSerial gpsSerial(1); // Use UART1 on ESP32

void setup() {
  Serial.begin(115200);        // Serial monitor
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // Baud rate, RX, TX pins

  Serial.println("Reading raw GPS data...");
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    Serial.write(c); // Print raw NMEA sentence
  }
}

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

String gpsData = "";

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
  Serial.println("Reading GPS raw data...");
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (c == '\n') {
      // End of sentence
      if (gpsData.startsWith("$GPRMC")) {
        parseGPRMC(gpsData);
      }
      gpsData = "";
    } else if (c != '\r') {
      gpsData += c;
    }
  }
}

void parseGPRMC(String sentence) {
  int fieldIndex = 0;
  String fields[12];
  int startIdx = 0;

  for (int i = 0; i < sentence.length(); i++) {
    if (sentence[i] == ',') {
      fields[fieldIndex++] = sentence.substring(startIdx, i);
      startIdx = i + 1;
    }
  }
  fields[fieldIndex] = sentence.substring(startIdx); // Last field

  // Now fields[3] = latitude, fields[4] = N/S, fields[5] = longitude, fields[6] = E/W
  if (fields[2] == "A") {  // Data is valid
    float rawLat = fields[3].toFloat();
    float rawLon = fields[5].toFloat();

    float latDegrees = int(rawLat / 100);
    float latMinutes = rawLat - (latDegrees * 100);
    float latitude = latDegrees + (latMinutes / 60.0);
    if (fields[4] == "S") latitude = -latitude;

    float lonDegrees = int(rawLon / 100);
    float lonMinutes = rawLon - (lonDegrees * 100);
    float longitude = lonDegrees + (lonMinutes / 60.0);
    if (fields[6] == "W") longitude = -longitude;

    Serial.print("Latitude: "); Serial.println(latitude, 6);
    Serial.print("Longitude: "); Serial.println(longitude, 6);
    Serial.println("---------------------------");
  } else {
    Serial.println("GPS data invalid ❌");
  }
}

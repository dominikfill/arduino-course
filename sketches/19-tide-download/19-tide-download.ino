#include <WiFiS3.h>

// ---------- change these ----------
const char WIFI_NAME[] = "your-hotspot";
const char WIFI_PASSWORD[] = "your-password";
// ----------------------------------

// The original file from the Comune di Venezia (Centro Maree), one line per hour:
//   12/11/2019;23:00;1.81      date ; hour ; water level in metres
const char HOST[] = "raw.githubusercontent.com";
const char FILE_PATH[] = "/dominikfill/arduino-course/main/data/valori_orari_puntasalute_Venezia_2019.csv";

const int MAX_DAYS = 400;
int tide[MAX_DAYS];   // highest level of each day, in cm
int days = 0;
int day = 0;

WiFiSSLClient client;

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
  while (WiFi.begin(WIFI_NAME, WIFI_PASSWORD) != WL_CONNECTED) {
    Serial.println("... trying again");
    delay(5000);
  }
  Serial.println("Connected.");

  readCsv();
  Serial.print("Read ");
  Serial.print(days);
  Serial.println(" days.");
}

void loop() {
  if (days == 0) {
    return;
  }
  Serial.println(tide[day]);
  day = day + 1;
  if (day == days) {
    day = 0;
  }
  delay(100);
}

// Downloads the CSV and goes through it line by line.
// For each day it keeps the highest of the 24 hourly values.
void readCsv() {
  if (!client.connect(HOST, 443)) {
    Serial.println("No connection to the server");
    return;
  }
  client.print("GET ");
  client.print(FILE_PATH);
  client.println(" HTTP/1.0");
  client.print("Host: ");
  client.println(HOST);
  client.println("Connection: close");
  client.println();

  // 1. skip the server's header lines, until the empty line
  while (client.connected() || client.available()) {
    String line = client.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) {
      break;
    }
  }

  // 2. skip the CSV's first line (the column names)
  client.readStringUntil('\n');

  // 3. read every line
  String today = "";
  int highest = 0;
  long lines = 0;
  while ((client.connected() || client.available()) && days < MAX_DAYS) {
    String line = client.readStringUntil('\n');
    line.trim();
    int first = line.indexOf(';');
    int last = line.lastIndexOf(';');
    if (first < 0 || last == first || last == line.length() - 1) {
      continue;                               // empty or broken line: skip it
    }
    String date = line.substring(0, first);   // "12/11/2019"
    int cm = round(line.substring(last + 1).toFloat() * 100);   // "1.81" → 181

    if (date != today) {                      // a new day starts
      if (today != "") {
        tide[days] = highest;                 // save yesterday's highest
        days = days + 1;
      }
      today = date;
      highest = cm;
    } else if (cm > highest) {
      highest = cm;
    }

    lines = lines + 1;
    if (lines % 1000 == 0) {
      Serial.print(lines);
      Serial.println(" lines ...");
    }
  }
  if (today != "" && days < MAX_DAYS) {       // save the last day
    tide[days] = highest;
    days = days + 1;
  }
  client.stop();
}

// Water level in Venice, hour by hour, in cm
// Data: Comune di Venezia, Centro Previsioni e Segnalazioni Maree (CC BY-NC-SA 3.0 IT)
#include "tide_data.h"

int hour = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(tide[hour]);
  hour = hour + 1;
  if (hour == HOURS) {
    hour = 0;
  }
  delay(1000);
}

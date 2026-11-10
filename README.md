# Arduino course · The Responsive Pavilion

Slides and Arduino sketches for the Arduino part of **259.172 Entwerfen Design for Adaptation 2: The Responsive Pavilion** (UE 8,0), winter semester 2026.

## Slides

**[dominikfill.github.io/arduino-course](https://dominikfill.github.io/arduino-course/)**

| Session | Topics |
|---|---|
| [Session 1](https://dominikfill.github.io/arduino-course/session-1/) | First sketch · the board · voltage, current, resistance · breadboard · external LED · button · potentiometer |
| [Session 2](https://dominikfill.github.io/arduino-course/session-2/) | Recap · PWM · sensors: light, temperature, distance · motors: servo, stepper |
| [Session 3](https://dominikfill.github.io/arduino-course/session-3/) | Data: the tide in Venice · from a file to a list with Python · RGB LED: the tide as colour |

Use the arrow keys or the space bar to step through the slides. Many slides build up click by click.

## Sketches

All Arduino sketches from the slides are in [`sketches/`](sketches/). To use one: open the `.ino` file here on GitHub, copy the code, paste it into a new sketch in the Arduino IDE.

| Sketch | What it does |
|---|---|
| `01-heartbeat` | The board's own LED blinks in a heartbeat rhythm |
| `02-heartbeat-external` | The same, with an LED on the breadboard |
| `03-button-heartbeat` | The heartbeat only while the button is pressed |
| `04-pot-heartbeat` | The knob sets the speed of the heartbeat |
| `04a-pot-serial` | Shows the knob's number in the Serial Monitor |
| `04b-check-circuit` | Checks LED and knob at once (start of session 2) |
| `05-pwm-dim` | Dims the LED with `analogWrite` |
| `06-pot-dim` | The knob sets the LED's brightness |
| `07-light-serial` | Shows the light sensor's number |
| `08-night-light` | The darker the room, the brighter the LED |
| `09-temperature` | Shows the temperature in °C |
| `10-warm-light` | The LED switches on above a temperature |
| `11-distance` | Shows the distance in cm |
| `12-come-closer` | The closer your hand, the brighter the LED |
| `13-servo-spin` | The 360° servo turns one way, stops, turns back |
| `14-servo-knob` | The knob sets the servo's speed and direction |
| `15-stepper-turn` | The stepper turns a quarter turn and back |
| `16-stepper-turn-by` | Type an angle: the stepper turns by that much |
| `17-stepper-go-to` | Type an angle: the stepper goes to that position |
| `18-tide-list` | Plays back one day of Venice's tide, hour by hour, in the Serial Plotter |
| `19-rgb-mix` | Mixes colours with the RGB LED |
| `20-tide-colour` | One day of Venice's tide as colour: low water blue, high water red |

The tide sketches read their data from `tide_data.h`, which the Python script writes (see below).

## Data and Python

- [`data/`](data/): `valori_orari_puntasalute_Venezia_2019.csv`, the hourly water level in Venice (Punta della Salute), 2019, in metres. Source: [Comune di Venezia, Centro Previsioni e Segnalazioni Maree](https://www.comune.venezia.it/it/content/archivio-storico-livello-marea-venezia-1).
- [`python/tide_to_arduino.py`](python/tide_to_arduino.py): picks one day from the file, converts it to cm and writes `tide_data.h` into the tide sketches. Change `DAY` at the top for another day. Needs only plain Python, no extra packages.

## Kit

Arduino UNO R4 WiFi · breadboard and jumper wires · LEDs · RGB LED (common cathode) · 470 Ω and 10 kΩ resistors · push buttons · 10 kΩ potentiometer · light sensor (LDR) · TMP36 temperature sensor · HC-SR04 distance sensor · SG90 360° servo · 28BYJ-48 stepper with ULN2003 driver board

## For the teacher: working on the slides

The slides are made with [Slidev](https://sli.dev/). Each session is one entry file (`session-1.md`, `session-2.md`, `session-3.md`) that imports its units from `units/`.

```
npm install
npm run dev:s1      # session 1 at http://localhost:3030
npm run dev:s2      # session 2
npm run dev:s3      # session 3
```

Every push to `main` builds all sessions and publishes them on GitHub Pages (`.github/workflows/deploy.yml`).

## Credits

- Breadboard images made with [Fritzing](https://fritzing.org/). Stepper and driver board parts by [mgesteiro/fritzing-parts](https://github.com/mgesteiro/fritzing-parts).
- Stepper photo: Kushagra Keshari, [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/), via Wikimedia Commons.
- Tide data: Comune di Venezia, Centro Previsioni e Segnalazioni Maree, [CC BY-NC-SA 3.0 IT](https://creativecommons.org/licenses/by-nc-sa/3.0/it/).

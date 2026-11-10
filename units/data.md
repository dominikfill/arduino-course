---
layout: section
---

# Data

The space reacts to what happened elsewhere.

---
clicks: 2
---

<p class="eyebrow">Data</p>

# A year in Venice

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/tide-2019.svg" alt="Highest water level of each day in Venice, 2019, between about 15 and 181 cm, with the peak on 12 November" credit="Data: Comune di Venezia, Centro Previsioni e Segnalazioni Maree · CC BY-NC-SA 3.0 IT" />

</div>
<div>

The highest water level of **each day**, 2019.

<div class="spec compact mt-4"><b><code>0 cm</code></b><span>the sea's average in <strong>1897</strong></span></div>
<div v-click="1" class="spec compact"><b><code>+110 cm</code></b><span>the city starts to <strong>flood</strong></span></div>
<div v-click="1" class="spec compact"><b><code>+140 cm</code></b><span><strong>half</strong> the footpaths under water</span></div>

<div v-click="2" class="note mt-4">

**12 November 2019:** 187 cm, the second-highest tide ever measured in Venice.

</div>

</div>
</div>

<!--
0 cm is not today's sea: it's the average of 1897 (Zero Mareografico di Punta della Salute). The city has sunk and the sea has risen: today's average is about +26 to +30 cm.
+110 cm: about 14 % of the public footpaths flooded. +140 cm: about 55 %. +80 cm: only the lowest spots, e.g. St Mark's Square. (Comune di Venezia, Venezia altimetria 2009.)
2019: 23 days above 110 cm, 5 above 140 cm. Calm in spring and summer, the floods come in autumn and winter.
The curve shows 181 cm for 12 November: the file has one value per hour, and the real peak (187 cm) came between two full hours.
Why this data: the pavilion is about adaptation. Venice adapts to water every day (MOSE barrier since 2020, raised paths, shops that move goods upstairs).
-->

---
clicks: 2
---

<p class="eyebrow">Data</p>

# One day in Venice

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/tide-day.svg" alt="Water level in Venice on 12 November 2019, hour by hour: low at 4:00, high at 10:00, low at 16:00, then rising to 181 cm at 23:00" credit="Data: Comune di Venezia, Centro Previsioni e Segnalazioni Maree · CC BY-NC-SA 3.0 IT" />

</div>
<div>

**12 November 2019**, hour by hour.

<div v-click="1">

Twice a day the water rises and falls: that's the **tide**.

</div>

<div v-click="2" class="note mt-4">

In the evening, a storm pushes the sea into the lagoon: **181 cm** at 23:00.

</div>

</div>
</div>

<!--
24 dots: the file has one value per hour.
Low tide around 4:00 and 16:00, high tide around 10:00 and around midnight: the normal rhythm, about 12 hours apart.
That evening, the sirocco (a strong south-east wind) and low air pressure pushed extra water into the lagoon on top of the high tide. The real peak, 187 cm, came at 22:50, between two full hours.
This is the day the board will play back: 24 numbers, one per second.
-->

---
class: code-large
clicks: 4
---

<p class="eyebrow">Data</p>

# The file

<div class="split">
<div>

```text {all|1|2-4|6|all}
GIORNO;ORA solare;Livello (m)
01/01/2019;01:00;-0.08
01/01/2019;02:00;-0.01
01/01/2019;03:00;0.14
…
12/11/2019;23:00;1.81
```

</div>
<div>

<div v-click="1" class="spec compact"><b>Line 1</b><span>the column names: <strong>day</strong>, <strong>hour</strong>, <strong>level</strong> in metres</span></div>
<div v-click="2" class="spec compact"><b><code>;</code></b><span>separates the columns. One line = <strong>one hour</strong></span></div>
<div v-click="3" class="spec compact"><b><code>1.81</code></b><span>metres: <strong>181 cm</strong></span></div>

<div v-click="4" class="task mt-4">

**Predict:** how many lines does the file have for the whole year?

</div>

</div>
</div>

<!--
The file as you download it: comune.venezia.it, "Archivio storico: livello di marea a Venezia", one file per year. It's also in the course repository, folder data/.
Line 1 shortened on the slide; the original reads "Livello P. Salute Canal Grande (m)". GIORNO = day, ORA solare = hour in solar time (UTC+1, no summer time).
CSV = "comma-separated values". Italian (and German) files use ; because the comma is the decimal sign there. This one uses . for decimals.
Negative values: lower than the 1897 average (low tide).
The Predict: 365 × 24 = 8760 lines (+ the column names). About 200 KB. Open it in a text editor first, not Excel: Excel may turn 1.81 into a date.
-->

---
class: code-compact
clicks: 4
---

<p class="eyebrow">Data</p>

# From the file to a list

<div class="split">
<div>

```python {all|3-4|5|6-7|all}
tide = []

for row in reader:
    day, hour, level = row
    if day == DAY:
        cm = round(float(level) * 100)
        tide.append(cm)
```

</div>
<div>

The board can't open files. **Python** prepares the data on the laptop.

<p class="chain">8760 lines → 24 numbers</p>

<div v-click="1" class="spec compact"><b>Split</b><span>every line at the <code>;</code>: day, hour, level</span></div>
<div v-click="2" class="spec compact"><b>Keep</b><span>only the lines of <code>DAY</code>, e.g. <code>"12/11/2019"</code></span></div>
<div v-click="3" class="spec compact"><b>Convert</b><span>metres → <strong>cm</strong>, and add it to the list</span></div>

<div v-click="4" class="task mt-3">

**Try:** run `python/tide_to_arduino.py` with **Python**. Then pick another day.

</div>

</div>
</div>

<!--
The slide shows only the heart of the script. The whole file: python/tide_to_arduino.py in the course repository.
Students don't need to learn Python here. The point: data from the web often needs preparing before a small board can use it, and Python is the usual tool for that.
tide is a list: it starts empty, and every line of DAY adds one number.
At the end the script writes data/tide_data.h and prints: Read 24 hours of 12/11/2019. Lowest: 38 cm Highest: 181 cm.
Another day: change DAY at the top (written like 12/11/2019), Run again, re-upload. Their birthday, the first day of the semester, a calm day in summer.
Another year: download that year's file into data/, change FILE_NAME.
The script needs only plain Python: no extra packages to install.
-->

---
class: code-compact
clicks: 4
---

<p class="eyebrow">Data</p>

# A list in the code

<div class="split">
<div>

```cpp
// tide_data.h, written by Python
const int HOURS = 24;
const int tide[HOURS] = {76, 60, 47, … 156, 181};
```

```cpp {all|1|6|7-10|all}
#include "tide_data.h"

int hour = 0;

void loop() {
  Serial.println(tide[hour]);
  hour = hour + 1;
  if (hour == HOURS) {
    hour = 0;
  }
  delay(1000);
}
```

</div>
<div>

<div v-click="1" class="spec compact"><b><code>#include</code></b><span>brings in the list Python wrote: a second <strong>tab</strong> in the IDE</span></div>
<div v-click="2" class="spec compact"><b><code>tide[hour]</code></b><span>the number at place <code>hour</code>. Counting starts at <strong>0</strong></span></div>

<div v-click="2">

<p class="chain">tide[0] → 76 · tide[23] → 181</p>

</div>

<div v-click="3" class="spec compact"><b><code>hour + 1</code></b><span>the next hour. After the last one: back to <code>0</code></span></div>

<div v-click="4" class="task mt-3">

**Try:** upload `18-tide-list`, open **Tools → Serial Plotter**. Find the two tides.

</div>

</div>
</div>

<!--
Python writes tide_data.h into data/: copy it into the sketch's folder, next to the .ino (18-tide-list, 20-tide-colour). If the tab doesn't show: close the sketch and open it again (the IDE only looks when it opens a sketch).
A list (array): many numbers under one name. tide[0] is 00:00, tide[23] is 23:00.
hour sits outside loop(): it remembers, as position did with the stepper.
setup() is not on the slide: Serial.begin(9600), as always.
delay(1000): one hour per second, the day in 24 seconds. Serial Plotter: the curve from "One day in Venice" appears point by point.
Run Python again for another day: re-upload, and the board plays the new day.
-->

---
clicks: 2
---

<p class="eyebrow">Colour</p>

# Three LEDs in one

<div class="split">
<div>

<Figure class="h-full" src="/images/rgb-led.svg" alt="RGB LED with four legs: red, the long shared minus leg, green, blue" />

</div>
<div>

Red, green and blue in one housing. Together they can mix **any colour**.

<div v-click="1" class="spec mt-4"><b>Long leg</b><span>the <strong>shared minus</strong> of all three → <strong>GND</strong></span></div>
<div v-click="2" class="spec"><b>R · G · B</b><span>each colour is its own LED: its own <strong>470 Ω</strong>, its own <strong>pin</strong></span></div>

<div v-click="2" class="note mt-4">

Find the **long leg** first: the colours sit around it.

</div>

</div>
</div>

<!--
Kit: RGB LED, common cathode: the long leg is the shared minus (cathode). There are also "common anode" LEDs where the long leg goes to 5V and the code is reversed: not ours.
Leg order in our kit: red, long leg, green, blue. Check one LED before the session.
Why one resistor per colour: three LEDs, three currents. One shared resistor on the long leg would make the colours steal current from each other.
Link back: session 1, an LED needs a resistor. Session 2: analogWrite dims. Now: three dimmers mix a colour.
-->

---

<p class="eyebrow">Colour</p>

# Build it

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-led4.svg" alt="RGB LED in the upper half of the breadboard; long leg to the − rail; each colour leg through a 470 Ω resistor across the middle gap, then wires to pins 9 (red), 10 (green) and 11 (blue)" credit="Made with Fritzing" />

</div>
<div>

1. **Unplug.** Empty breadboard, **GND** → **−** rail
2. RGB LED into **four different strips**
3. **Long leg**'s strip → **−** rail
4. Each colour leg: a **470 Ω** across the middle gap
5. Then to pins **9** (red), **10** (green), **11** (blue)

<div class="note mt-4">

Three LEDs in one: red, green, blue, sharing the long leg.

</div>

</div>
</div>

<!--
Kit: RGB LED, common cathode (the long leg is the shared minus). Leg order from the flat side: red, long leg, green, blue. Check one LED before the session.
Each colour is its own LED, so each needs its own resistor, as in session 1.
Pins 9, 10, 11: all three can dim (PWM, the ~ on the board).
If one colour stays dark: the leg is in the wrong strip, or two legs share a strip. Test without a sketch: long leg to −, one colour leg through 470 Ω to the + rail.
Green and blue need about 3 V, red about 2 V: with 470 Ω all three light, red a little weaker.
-->

---
class: code-compact
clicks: 2
---

<p class="eyebrow">Colour</p>

# Not equally bright

<div class="split">
<div>

```cpp
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  analogWrite(RED_PIN, 255);
  analogWrite(GREEN_PIN, 255);
  analogWrite(BLUE_PIN, 255);
}
```

</div>
<div>

<div class="task">

**Predict:** all three at `255`. Which colour do you see?

</div>

<div v-click="1" class="mt-4">

**Blue.** From the LED's listing:

<div class="spec compact mid-terms mt-3"><b>Red</b><span>1000 – 2000 mcd</span></div>
<div class="spec compact mid-terms"><b>Green</b><span>4000 – 5000 mcd</span></div>
<div class="spec compact mid-terms"><b>Blue</b><span>5000 – 7000 mcd</span></div>

</div>

<div v-click="2">

<p class="chain">green, blue: 3 to 5 × brighter → turn them down</p>

</div>

</div>
</div>

<!--
mcd (millicandela): how bright an LED shines straight ahead. It's printed in every LED listing or datasheet.
At the same value, green and blue outshine red: 255, 255, 0 looks green instead of yellow, 255, 255, 255 looks blue instead of white.
Nothing is broken: the wiring and the code are fine, the LED is just unbalanced. Cheap RGB LEDs almost always are.
The fix is in the code: give green and blue smaller numbers. Next slide.
A piece of paper or a ping-pong ball over the LED also helps: the clear housing shows the three colours side by side, scattered light mixes them.
-->

---
class: code-tiny
clicks: 2
---

<p class="eyebrow">Colour</p>

# Mix a colour

<div class="split">
<div>

<<< @/sketches/19-rgb-mix/19-rgb-mix.ino cpp {all|12-18|21-24|all}

</div>
<div>

<div v-click="1" class="spec"><b><code>colour(…)</code></b><span>a new <strong>function</strong>: a name, then red, green, blue</span></div>
<div v-click="2" class="spec"><b><code>255, 40, 0</code></b><span>yellow: a lot of red, only a <strong>little</strong> green</span></div>

</div>
</div>

<!--
The function colour() bundles the four lines that set one colour, so each colour is one line in loop(). Like setup() and loop(), only we wrote it ourselves, and it takes numbers.
The names ("yellow", …) go to the Serial Monitor: students see which mix is meant.
The numbers are balanced for our kit's LED: green and blue are turned down, so red can hold its own. With another LED they'd be different.
Paper over the LED: the colours blend. Without it, up close, you see three dots.
-->

---
class: code-tiny
clicks: 4
---

<p class="eyebrow">Colour</p>

# The tide in colour

<div class="split">
<div>

<<< @/sketches/20-tide-colour/20-tide-colour.ino cpp {all|14|16|17|21|all}{maxHeight:'380px'}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>constrain</code></b><span>the level of this hour, kept within <code>0</code> … <code>140</code> cm</span></div>
<div v-click="2" class="spec compact"><b>red</b><span><code>0</code> … <code>140</code> cm → <code>0</code> … <code>255</code></span></div>
<div v-click="3" class="spec compact"><b>blue</b><span><code>60</code> … <code>0</code>: the more red, the <strong>less blue</strong></span></div>

<div v-click="3">

<p class="chain">40 cm → blue · 70 cm → purple · 140 cm → red</p>

</div>

<div v-click="4" class="spec compact"><b><code>%</code></b><span>after the last hour: back to <code>0</code></span></div>

</div>
</div>

<!--
constrain first: everything above 140 cm counts as 140, so both maps stay within their ranges. No constrain needed after map.
map() straight inside analogWrite: the result goes to the pin without a variable.
Low water: blue. Rising: purple. From 140 cm: fully red.
Blue only goes up to 60, not 255: it's so much brighter than red that at full strength it would drown the red (see 'Not equally bright').
Green isn't used: its pin stays off.
% (modulo) is the remainder of a division: (23 + 1) % 24 = 0. It does the same as the if from "A list in the code", in one line.
The Serial Monitor shows the real level (tide[hour]), even above 140.
The Try: change both 140s to 110.
Run Python with another DAY, upload again: a calm day stays blue all day.
Architecture: a façade or a lagoon pavilion that shows the water's state as light, or plays back a day.
-->

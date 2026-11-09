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

# A list in the code

<div class="split">
<div>

```cpp {all|1-6|11|12-15|all}
const int DAYS = 365;
const int tide[DAYS] = {
  46, 58, 52, 59, 53, 51, 54, 60, 67,
  …
  118, 120, 143, 139, 119, 96, 101, 90, 60, 53, 54
};

int day = 0;

void loop() {
  Serial.println(tide[day]);
  day = day + 1;
  if (day == DAYS) {
    day = 0;
  }
  delay(100);
}
```

</div>
<div>

The **highest** value of each day, already worked out from the file.

<div v-click="1" class="spec compact mt-4"><b><code>tide[ ]</code></b><span>a <strong>list</strong>: 365 numbers, one per day</span></div>
<div v-click="2" class="spec compact"><b><code>tide[day]</code></b><span>the number at place <code>day</code>. Counting starts at <strong>0</strong></span></div>

<div v-click="2">

<p class="chain">tide[0] → 46 · tide[315] → 181</p>

</div>

<div v-click="3" class="spec compact"><b><code>day + 1</code></b><span>the next day. After the last one: back to <code>0</code></span></div>

<div v-click="4" class="task mt-3">

**Try:** upload `18-tide-list`, open **Tools → Serial Plotter**. Find November.

</div>

</div>
</div>

<!--
The slide shows a shortened list: the sketch has all 365 numbers (25 lines).
Where the numbers come from: the file has 24 values per day; for each day the highest was picked out on a laptop beforehand (a few lines of Python, or a spreadsheet). That's the weak spot of this approach: someone has to prepare the data. Next slide: the board does it itself.
tide[0] is 1 January, tide[315] is 12 November (day 316 of the year, but counting starts at 0).
day sits outside loop(): it remembers, as position did with the stepper.
setup() is not on the slide: Serial.begin(9600), as always.
delay(100): a year in about 37 seconds. Serial Plotter: the curve from the last slide appears line by line.
-->

---
clicks: 3
---

<p class="eyebrow">Light sensor</p>

# A resistor that reacts to light

<div class="split">
<div>

<Ldr :fixed="$clicks >= 2" :light="[1, 0, 1, 0][$clicks] ?? 0" />

</div>
<div>

The light sensor is a resistor: more light, **lower** resistance.

**Alone**, no current flows: A0 sees 5 V.

<div v-click="1" class="mt-3">

**Dark:** the resistance changes, A0 doesn't. 1023 either way.

</div>

<div v-click="2" class="mt-3">

With **10 kΩ** to GND, current flows. The two **share** the 5 V. Bright → A0 high.

</div>

<div v-click="3" class="mt-3">

**Dark:** the sensor takes most of the 5 V → A0 low.

</div>

<div v-click="3" class="note mt-4">

The 10 kΩ turns a change in **resistance** into a change in **voltage**.

</div>

</div>
</div>

<!--
A0 is like a probe touching the point between sensor and 10 kΩ: it only looks, no current goes in. All the current runs 5 V → sensor → point → 10 kΩ → GND.
Step by step, one click each:
0: sensor alone, bright. A0 only measures, nothing leads to GND: no current. No current, no drop: A0 sees the full 5 V, 1023. Same as the pull-up with the button open.
1: dark. The sensor's resistance jumps from about 1 kΩ to about 100 kΩ, but A0 still reads 1023. Without current, the resistance is invisible.
2: the 10 kΩ from A0 to GND gives the current a path. Now two parts share the 5 V, like LED and resistor, pull-up and button, the two halves of the knob. Bright: sensor about 1 kΩ, it takes little, the 10 kΩ takes most: A0 about 4.5 V, 930.
3: dark: sensor about 100 kΩ, it takes most, the 10 kΩ little: A0 about 0.5 V, 93.
Why 10 kΩ: it sits in the middle of the sensor's range (1 kΩ to 100 kΩ), so the share swings as far as possible. Much smaller: A0 stuck near 0 V. Much larger: stuck near 5 V.
It's called a pull-down: it connects A0 towards GND, the mirror image of the pull-up.
Values are typical, not exact: every sensor is a bit different. That's why students measure their own.
-->

---

<p class="eyebrow">Light sensor</p>

# Build it

<div class="split wide-left">
<div>

<div class="placeholder h-full">Wiring: LED on pin 9 as before + light sensor from 5V to A0, 10 kΩ from A0 to − rail (Fritzing)</div>

</div>
<div>

1. Take out the potentiometer
2. Light sensor: one leg → **5V**, the other → a free strip
3. That strip → **A0**
4. **10 kΩ** from that strip → **−** rail

<div class="note mt-4">

**10 kΩ** colour bands<br>
4 bands: brown · black · orange<br>
5 bands: brown · black · black · red

</div>

</div>
</div>

<!--
The sensor has no polarity: either way round works.
A0 and the 10 kΩ share one strip with the sensor's second leg: that strip is the point "between" the two parts.
-->

---

<p class="eyebrow">Light sensor</p>

# Read the light

<div class="split">
<div>

<<< @/sketches/07-light-serial/07-light-serial.ino cpp

</div>
<div>

Nothing new: `analogRead` and the Serial Monitor, as with the knob.

<div class="task mt-4">

**Try:** write down **two numbers**: the room as it is, and your hand over the sensor.

</div>

<div class="note mt-4">

You'll need both numbers on the next slide.

</div>

</div>
</div>

<!--
Typical: a few hundred to 900 in a bright room, below 200 covered. Every sensor and every room gives different numbers.
Let them compare: why are the numbers different on every table? Light, sensor, resistor tolerance.
-->

---
class: code-compact
---

<p class="eyebrow">Light sensor</p>

# Darker means brighter

<div class="split">
<div>

<<< @/sketches/08-night-light/08-night-light.ino cpp {all|13|14|15|all}

</div>
<div>

<MapScale :from="[100, 900]" :to="[255, 0]" :value="[800, 800, 950, 250, 250][$clicks] ?? 250"
          top="LIGHT · analogRead" bottom="BRIGHTNESS · analogWrite" />

<div v-click="1" class="spec compact mt-2"><b><code>map</code></b><span>lays one range onto another. <code>255, 0</code>: reversed</span></div>
<div v-click="2" class="spec compact"><b><code>constrain</code></b><span>keeps the result within <code>0</code> … <code>255</code></span></div>

<div v-click="4" class="task mt-3">

**Try:** replace `100` and `900` with your two numbers.

</div>

</div>
</div>

<!--
map(value, fromLow, fromHigh, toLow, toHigh): like laying one scale bar onto another. 100 on the light scale lands on 255, 900 lands on 0.
Reversed target range (255, 0): more light, less LED. That's the whole trick of the night light.
constrain: the room can get brighter than 900 or darker than 100. Then map() would give values outside 0–255 (below 0 or above 255), which analogWrite can't use. constrain cuts them off. Click 2 shows it: 950 lands at 0, not below.
Architecture: a façade that lights up at dusk, an entrance that brightens as daylight fades. The same 4 lines.
-->

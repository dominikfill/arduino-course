---
layout: section
---

# Sensors

The space starts to sense: light, warmth, distance.

---
clicks: 2
---

<p class="eyebrow">Light sensor</p>

# The pull-down

<div class="split">
<div>

<Ldr button :pressed="$clicks >= 1" />

</div>
<div>

The **mirror image** of the pull-up: the button goes to **5 V**, the 10 kΩ to **GND**.

**Released:** no current, so the resistor takes **0 V**. A0 sits on GND → `0`

<div v-click="1" class="mt-3">

**Pressed:** A0 is connected to 5 V → `1023`

</div>

<div v-click="2" class="mt-3">

The resistor **pulls** the pin **down** to 0 V, unless the button pulls it up.

<p class="example">the door closer again, the other way round</p>

</div>

</div>
</div>

<!--
Straight from the recap: same rules, mirrored. This time we read A0 with analogRead, so the numbers are 0 and 1023 instead of 0 and 1.
Released: the button is a gap, no loop, no current. A resistor without current takes nothing: A0 sits at the level of GND.
[click] Pressed: the button is a wire to 5 V. Current flows: 5 V ÷ 10 kΩ = 0.5 mA, the resistor takes all 5 V.
[click] The Arduino has built-in pull-ups, but no pull-downs: this one has to be a real 10 kΩ on the breadboard.
Why a pull-down here: the light sensor is about to take the button's place. On the next slide.
-->

---
clicks: 3
---

<p class="eyebrow">Light sensor</p>

# A resistor that reacts to light

<div class="split">
<div>

<Ldr :fixed="$clicks < 3" :light="[1, 0, 0.5, 0][$clicks] ?? 0" />

</div>
<div>

The **light sensor** takes the button's place: a resistor that changes with light. Like a button that's only **a bit pressed**.

**Bright:** low resistance, almost "pressed" → A0 **high**

<div v-click="1" class="mt-3">

**Dark:** high resistance, almost "released" → A0 **low**

</div>

<div v-click="2" class="mt-3">

Anything in between: an **analog** input. The sensor and the 10 kΩ **share the 5 V**.

</div>

<div v-click="3" class="note mt-4">

Without the 10 kΩ: no loop, no current. A0 reads 1023, bright or dark. The resistance only shows when current flows.

</div>

</div>
</div>

<!--
The same drawing as the slide before, with the sensor where the button was.
Bright: sensor about 1 kΩ, it takes little, the 10 kΩ takes most: A0 about 4.5 V, 930.
[click] Dark: sensor about 100 kΩ, it takes most, the 10 kΩ little: A0 about 0.5 V, 93.
[click] Half light: sensor about 10 kΩ, the same as the fixed resistor: they share the 5 V equally, A0 about 2.5 V, 512. The button only knew two states, 0 and 1023. The sensor gives anything in between: digital becomes analog.
Why 10 kΩ: it sits in the middle of the sensor's range (1 kΩ to 100 kΩ), so the share swings as far as possible. Much smaller: A0 stuck near 0 V. Much larger: stuck near 5 V.
[click] Take the 10 kΩ away: the sensor alone, from 5 V to A0. A0 only measures, nothing leads to GND: no current, no drop, 1023 always. "Voltage needs a connection, current needs a loop", from the recap. The 10 kΩ turns a change in resistance into a change in voltage.
Values are typical, not exact: every sensor is a bit different. That's why students measure their own.
-->

---

<p class="eyebrow">Light sensor</p>

# Build it

<div class="split wide-left">
<div>

<div class="placeholder h-full">Wiring: LED on pin 9 as before + light sensor from + rail to a free strip, that strip to A0, 10 kΩ from that strip to − rail (Fritzing)</div>

</div>
<div>

1. **Unplug.** Take out the knob, keep the red wire 5V → **+** rail
2. **Light sensor:** one leg → **+** rail, the other → a **free strip**
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

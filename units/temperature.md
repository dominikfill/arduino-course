---
clicks: 2
---

<p class="eyebrow">Temperature</p>

# A sensor that outputs voltage

<div class="split">
<div>

<MapScale :from="[0, 50]" :to="[0.5, 1]" :decimals="2" :value="[20, 25, 30][$clicks] ?? 30"
          top="TEMPERATURE · °C" bottom="TMP36 OUTPUT · V" />

</div>
<div>

The TMP36 has electronics inside: it **turns the temperature into a voltage**. No extra resistor needed.

**0 °C → 0.5 V.** Every degree adds **0.01 V**.

<div class="note mt-4">

Three legs. Flat side facing you, legs down: **left 5V**, **middle signal**, **right GND**.

</div>

</div>
</div>

<!--
Contrast with the light sensor: that one only changes its resistance, so it needed the 10 kΩ to turn resistance into voltage. The TMP36 delivers the voltage itself.
It doesn't create energy: it's powered by the 5 V (that's why it has three legs). And it measures its own temperature, not a difference: 0.75 V at 25 °C, whatever came before.
Clicks: 20 °C → 0.70 V, 25 °C → 0.75 V, 30 °C → 0.80 V. A straight line: like the scale bars of map().
Wired the wrong way round, the TMP36 gets hot within seconds. If it's hot to the touch: unplug the USB cable at once, then turn it around. Say this before they build.
-->

---

<p class="eyebrow">Temperature</p>

# Build it

<div class="split wide-left">
<div>

<div class="placeholder h-full">Wiring: TMP36, flat side facing you: left → 5V, middle → A1, right → − rail. Light sensor and LED stay (Fritzing)</div>

</div>
<div>

1. TMP36 into **three different strips**, flat side facing you
2. Left leg → **5V**
3. Middle leg → **A1**
4. Right leg → **−** rail

<div class="task mt-4">

**Check:** touch the sensor after 10 seconds. Hot? Unplug, turn it around.

</div>

</div>
</div>

<!--
A1, not A0: the light sensor can stay where it is. Later both can be read together.
The TMP36 looks like a transistor. If the kit has both, check the print on the flat side: TMP36.
-->

---

<p class="eyebrow">Temperature</p>

# From number to degrees

<div class="split">
<div>

<<< @/sketches/09-temperature/09-temperature.ino cpp {all|9|10|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>float</code></b><span>a number <strong>with decimals</strong>: <code>0.75</code>, <code>21.4</code></span></div>
<div v-click="1" class="spec compact"><b><code>* (5.0 / 1023.0)</code></b><span>steps × size of one step = <strong>volts</strong></span></div>
<div v-click="2" class="spec compact"><b><code>(volts - 0.5) * 100</code></b><span>volts to <strong>°C</strong>: minus the 0.5 V, then 100 °C per volt</span></div>

<div v-click="3" class="task mt-4">

**Try:** hold the sensor between your fingers. How warm does it get?

</div>

<div v-click="3" class="note mt-3">

Your board's "5 V" is about 4.7 V (measure the 5V pin). Put your value instead of `5.0`: the result gets several degrees more accurate.

</div>

</div>
</div>

<!--
Why 5.0 and not 5: with whole numbers only, the Arduino throws away the decimals in every step. 5.0 tells it to calculate with decimals.
Line 9: analogRead cuts the 5 V into 1023 steps of about 0.0049 V each. The reading is a count of steps. (5.0 / 1023.0) is the size of one step: count × step size = volts. 153 steps × 0.0049 V ≈ 0.75 V.
Line 10 reverses the TMP36: it adds 0.5 V and 0.01 V per degree. So: take away 0.5, then multiply by 100 (1 / 0.01).
Accuracy: analogRead measures against the board's own supply. Over USB that's about 4.7 V, not 5 V. With 5.0 in the formula, the temperature comes out several degrees too high. Students measured 4.7 V on pin 2 earlier: same voltage, now it matters.
The TMP36 itself is accurate to about ±2 °C. Good enough to notice a hand, a window, a sunny spot.
Values jump a little: normal. Averaging comes later.
-->

---
class: code-compact
---

<p class="eyebrow">Temperature</p>

# Warm? Light on.

<div class="split">
<div>

<<< @/sketches/10-warm-light/10-warm-light.ino cpp {all|14|15|16-17|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>if ( )</code></b><span>a condition: <code>celsius &gt; 27.0</code></span></div>
<div v-click="2" class="spec compact"><b><code>{ }</code></b><span>runs only when the condition is <strong>true</strong></span></div>
<div v-click="3" class="spec compact"><b><code>else { }</code></b><span>runs when it is <strong>false</strong></span></div>

<div v-click="3" class="note mt-3">

Compare with `>` `<` `>=` `<=` `==` `!=`

</div>

<div v-click="4" class="task mt-4">

**Try:** set the threshold 2 °C above your room temperature. Can you switch the light with your hand?

</div>

</div>
</div>

<!--
The first program that decides on its own, based on its environment. That's the responsive pavilion in miniature: too warm, open a vent; too dark, light on.
Read the if aloud: "if it's warmer than 27 degrees, light on, otherwise off".
== compares, = assigns (as with the button).
Near the threshold, the LED flickers: the reading jumps around 27.0. Real thermostats use two thresholds (on above 27, off below 26). A good question for fast students: how would you stop the flicker?
-->

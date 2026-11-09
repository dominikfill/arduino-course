---
layout: section
---

# Pulse Width Modulation

Not just on or off: faking everything in between.

---
clicks: 2
---

<p class="eyebrow">PWM</p>

# How does a pin dim?

<div class="split">
<div>

A pin can only be **on** (5 V) or **off** (0 V).

<div v-click="1" class="mt-4">

**PWM** switches it on and off, hundreds of times per second: the rhythm drawing from the first sketch, only much faster.

</div>

<div v-click="2" class="mt-4">

Too fast for the eye: it sees the **share of on-time** as brightness. A heartbeat too fast to see.

</div>

</div>
<div class="flex items-center">

<Signal type="pwm" :duty="[1, 0.5, 0.1][$clicks] ?? 0.1" />

</div>
</div>

<!--
PWM = pulse width modulation: the width of the "on" pulse changes, the rhythm stays.
Same kind of drawing as "The rhythm, drawn": HIGH and LOW over time, blue = on. Only the time scale changed: about 500 times a second instead of once.
Blue = the time the pin is on. 100 %: always on, full brightness. 50 %: half the time. 10 %: dim.
On the ~ pins the Arduino fakes in-between values this way. (The UNO R4 has one real analog output, a DAC on A0. We don't need it.)
-->

---

<p class="eyebrow">PWM</p>

# Dim the LED

<div class="split">
<div>

<<< @/sketches/05-pwm-dim/05-pwm-dim.ino cpp {all|8|10|12|all}

</div>
<div>

<Signal type="pwm" :duty="[1, 1, 60 / 255, 10 / 255, 10 / 255][$clicks] ?? 10 / 255" />

<div class="spec compact mt-4"><b><code>analogWrite</code></b><span><code>0</code> … <code>255</code>: the share of on-time</span></div>

<div class="note mt-2">

Same circuit, no rewiring. Only on **~** pins: 3, 5, 6, 9, 10, 11.

</div>

<div v-click="4" class="task mt-4">

**Try:** type it as a new sketch. Then other values between `0` and `255`: does `127` look like half brightness?

</div>

</div>
</div>

<!--
digitalWrite: only on or off. analogWrite: in-between, with PWM.
Pin 9 was a ~ pin all along: that's why we chose it.
127 doesn't look like half: physically it is half the light (on half the time), but the eye judges brightness by relative change. Half the light looks like about three quarters. To look half as bright, you need roughly a fifth to a quarter of the light: a value around 55, not 127. Small values make a big difference, large values hardly any.
Worth knowing for any lighting design: professional dimmers (DALI) dim along a curve, not a straight line; screens do the same (gamma correction).
-->

---

<p class="eyebrow">PWM</p>

# Your turn: the knob sets the brightness

<div class="split">
<div>

<div class="task">

**Try:** in your sketch, replace the blinking lines with one `analogWrite`: the **knob** sets the LED's **brightness**.

</div>

<p class="example">a dimmer on the wall: you're building one</p>

<div class="spec compact mt-4"><b><code>analogRead</code></b><span>gives <code>0</code> … <code>1023</code></span></div>
<div class="spec compact"><b><code>analogWrite</code></b><span>takes <code>0</code> … <code>255</code></span></div>

<div v-click="1" class="mt-4">

`÷ 4`: 1023 becomes 255. The ranges fit.

</div>

</div>
<div v-click="1">

<<< @/sketches/06-pot-dim/06-pot-dim.ino cpp {9-10}

</div>
</div>

<!--
The circuit is already built, and the base sketch already has LED_PIN, POT_PIN and analogRead. Only the loop changes: digitalWrite and delay out, analogWrite in.
Give them a few minutes before revealing. Many will try analogWrite(LED_PIN, analogRead(POT_PIN)) first: values above 255 don't work as expected. A good moment for the Serial Monitor.
÷ 4 works because 1023 and 255 happen to fit. With the light sensor, map() does the same for any two ranges.
Fast students: a "breathing" LED that fades in and out. That needs a for loop: for (int b = 0; b < 256; b++) { analogWrite(LED_PIN, b); delay(5); }
-->

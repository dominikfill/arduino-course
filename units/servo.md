---
layout: section
---

# Motors


---
clicks: 4
---

<p class="eyebrow">Servo</p>

# A servo that spins

<div class="split">
<div class="flex items-center">

<MapScale :from="[0, 180]" :to="[-100, 100]" :value="[90, 90, 0, 180, 135][$clicks] ?? 135"
          top="servo.write" bottom="SPEED · % (− = the other way)" />

</div>
<div>

Most servos turn to an angle. **Ours spins**: it is the 360° version.

<div v-click="1" class="spec compact mt-4"><b><code>90</code></b><span><strong>stop</strong></span></div>
<div v-click="2" class="spec compact"><b><code>0</code></b><span>full speed, one way</span></div>
<div v-click="3" class="spec compact"><b><code>180</code></b><span>full speed, the other way</span></div>

<div v-click="4" class="note mt-4">

In between: slower. It **doesn't know where it is**: it only knows how fast to turn.

</div>

</div>
</div>

<!--
Kit: SG90, 360° "continuous rotation" version. The normal 180° SG90 looks the same: with the same code, write(45) would move it to 45° and hold. Ours turns that number into speed and direction instead.
Click 4: 135 is halfway between stop and full speed: about half speed.
How far it turns is only a question of time: 2 seconds at full speed. Not precise. For exact positions: the stepper motor (later).
-->

---

<p class="eyebrow">Servo</p>

# Build it

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-servo.svg" alt="SG90 servo: brown to the − rail, red to the + rail, orange to pin 10. Knob: outer legs to the + and − rail, middle leg to A0." credit="Made with Fritzing" />

</div>
<div>

1. **Unplug.** Take out the distance sensor, the LED and its resistor. Keep the 5V and GND wires
2. **Servo:** brown → **−** rail, red → **+** rail, orange → pin **10**
3. **Knob** into **three different strips**: outer legs → **+** and **−** rail
4. Knob's middle leg → **A0**

<div class="note mt-4">

The servo's own colours: brown = GND, red = 5V, orange = signal.

</div>

</div>
</div>

<!--
Pin 10: any digital pin works for a servo. The LED comes out: none of the servo sketches use it, and the breadboard stays clear.
The knob goes in now too, so nothing has to be rebuilt later. The first sketch (Spin it) ignores it.
Power: the servo takes its current from the 5V rail, not from the pin. The pin only sends the signal, so the 8 mA limit doesn't matter here.
If the board restarts or the Serial Monitor disconnects when the motor starts: the motor draws too much from USB. Try another USB port, or a short cable.
-->

---
class: code-compact
---

<p class="eyebrow">Servo</p>

# Spin it

<div class="split">
<div>

<<< @/sketches/13-servo-spin/13-servo-spin.ino cpp {all|1|4|7|11-18|all}

</div>
<div>

<div v-click="1" class="spec"><b><code>#include &lt;Servo.h&gt;</code></b><span>brings in a <strong>library</strong>: ready-made code for servos</span></div>
<div v-click="2" class="spec"><b><code>Servo motor;</code></b><span>one servo, named <code>motor</code></span></div>
<div v-click="3" class="spec"><b><code>motor.attach(SERVO_PIN)</code></b><span>it sits on pin 10</span></div>
<div v-click="4" class="spec"><b><code>motor.write( )</code></b><span><code>0</code> … <code>90</code> … <code>180</code>: speed and direction</span></div>

<div v-click="5" class="task mt-3">

**Try:** does it really stop at `90`? Find the number where it stands still, and put it in both places.

</div>

</div>
</div>

<!--
The library comes with the Arduino IDE: nothing to install. Upload errors with "Servo.h: No such file": check the spelling, capital S.
Servo motor; is like int x;, only the type is Servo. motor is the name we chose: we could call it vent or louvre.
The dot in motor.write: "motor, write this". Read it aloud.
The stop point: cheap servos rarely stop exactly at 90. Often 88 … 94: the motor creeps. The rhythm is the same idea as the heartbeat: one way, stop, the other way.
-->

---
class: code-compact
---

<p class="eyebrow">Servo</p>

# The knob sets the speed

<div class="split">
<div>

<<< @/sketches/14-servo-knob/14-servo-knob.ino cpp {all|14|15-18|19|all}

</div>
<div>

<MapScale class="max-h-40" :from="[0, 1023]" :to="[0, 180]" :value="[200, 200, 512, 512, 900][$clicks] ?? 900"
          top="KNOB · analogRead" bottom="SPEED · servo.write" />

<div v-click="1" class="spec compact mt-2"><b><code>map</code></b><span><code>0</code> … <code>1023</code> → <code>0</code> … <code>180</code></span></div>
<div v-click="2" class="spec compact"><b><code>print</code></b><span>stays on the line, <code>println</code> ends it</span></div>
<div v-click="3" class="spec compact"><b><code>write</code></b><span>sends the speed to the servo</span></div>

<div v-click="4" class="task mt-3">

**Try:** open the Serial Monitor and turn the knob to `Speed: 90`. Does the servo stop? If not: why?

</div>

</div>
</div>

<!--
The same map() as the night light and Come closer: a new output, the same idea.
Click 2: the middle of the knob (512) lands at 90: stop.
The Try: the middle is 90, but their servo stops at the number they found on the last slide (e.g. 92). So it creeps. Fix: find the knob position where it stops, or change the range.
Serial.print pieces: "Pot: " + pot does not join text in Arduino code (it jumps through memory and prints garbage). Printing piece by piece avoids that trap.
Open the Serial Monitor: Pot: 512 - Speed: 90. Students see both numbers side by side: map(), made visible.
delay(100): 10 new values a second. Readable in the Serial Monitor, and enough for the servo.
Architecture: a turning element controlled by hand. Next step for fast students: replace the knob with the light sensor.
-->

---
clicks: 3
---

<p class="eyebrow">Distance</p>

# Measuring distance with sound

<div class="split">
<div class="flex items-center">

<Sonar :distance="30" :step="$clicks" />

</div>
<div>

The sensor sends a short **click** of ultrasound, too high to hear.

<div v-click="1" class="mt-3">

It travels to the nearest surface and **bounces back**.

</div>

<div v-click="2" class="mt-3">

The Arduino measures the **time** until the echo returns.

</div>

<div v-click="3" class="mt-3">

Sound travels **0.0343 cm per µs**. Time × speed ÷ 2 = **distance**.

</div>

</div>
</div>

<!--
µs = microsecond, a millionth of a second. 1749 µs is less than 2 thousandths of a second.
÷ 2: the click goes there and back. The time covers twice the distance.
0.0343 cm per µs = 343 metres per second, the speed of sound in air at room temperature.
Like a bat, or an echo in the mountains, only much faster.
Range: about 2 cm to 4 m. Soft or angled surfaces (a sweater, a slanted wall) can swallow or deflect the echo.
-->

---

<p class="eyebrow">Distance</p>

# Build it

<div class="split wide-left">
<div>

<div class="placeholder h-full">Wiring: HC-SR04 VCC → 5V, Trig → pin 7, Echo → pin 8, GND → − rail (Fritzing)</div>

</div>
<div>

1. **VCC** → **5V**
2. **Trig** → pin **7**
3. **Echo** → pin **8**
4. **GND** → **−** rail

<div class="note mt-4">

The two "eyes" face open space, not the breadboard or your laptop.

</div>

</div>
</div>

<!--
The pin names are printed on the sensor's front, next to the legs.
Trig = trigger: the Arduino tells the sensor to click. Echo: the sensor tells the Arduino how long the echo took.
The R4's pins handle the sensor's 5 V signals directly.
-->

---
class: code-compact
---

<p class="eyebrow">Distance</p>

# Read the distance

<div class="split">
<div>

<<< @/sketches/11-distance/11-distance.ino cpp {all|11-13|15|16|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>Trig</code></b><span><strong>10 µs</strong> HIGH: "click now"</span></div>
<div v-click="2" class="spec compact"><b><code>pulseIn</code></b><span>waits for the echo, returns the <strong>time</strong> in µs</span></div>
<div v-click="2" class="spec compact"><b><code>long</code></b><span>a whole number that can get <strong>big</strong></span></div>
<div v-click="3" class="spec compact"><b><code>* 0.0343 / 2</code></b><span>time × speed ÷ 2 = <strong>cm</strong></span></div>

<div v-click="4" class="task mt-4">

**Try:** move your hand towards the sensor. What's the shortest distance it can measure?

</div>

</div>
</div>

<!--
delayMicroseconds: like delay, but in millionths of a second.
pulseIn(ECHO_PIN, HIGH, 30000): measures how long Echo stays HIGH. 30000 µs is the timeout, about 5 m: if no echo comes back, it gives 0.
0 cm in the Serial Monitor means "no echo", not "touching": too far, too close (below about 2 cm), or a surface that swallows sound.
-->

---
class: code-compact
---

<p class="eyebrow">Distance</p>

# Come closer

<div class="split">
<div>

<<< @/sketches/12-come-closer/12-come-closer.ino cpp {all|17|18-19|all}

</div>
<div>

<MapScale :from="[5, 100]" :to="[255, 0]" :value="[80, 80, 20, 20][$clicks] ?? 20"
          top="DISTANCE · cm" bottom="BRIGHTNESS · analogWrite" />

<div v-click="1" class="spec compact mt-2"><b><code>map</code></b><span>5 cm → 255, 100 cm → 0: the closer, the brighter</span></div>
<div v-click="2" class="spec compact"><b><code>constrain</code></b><span>keeps it within <code>0</code> … <code>255</code></span></div>

<div v-click="3" class="task mt-3">

**Try:** walk towards the sensor. Change `100` to make it react from further away.

</div>

</div>
</div>

<!--
The same map() and constrain() as the night light: a new sensor, the same idea.
Architecture: a space that notices someone approaching. An entrance that lights up, a wall that responds.
"No echo" gives 0 cm, which map turns into full brightness. In a normal room, walls are within 5 m, so there's always an echo. Pointing it at the open sky would light it fully.
Fast students: the heartbeat from session start, beating faster as someone comes closer: int pause = map(cm, 5, 100, 100, 1000); then the heartbeat with delay(pause).
-->

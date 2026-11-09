---
clicks: 3
---

<p class="eyebrow">Stepper</p>

# A motor that counts

<div class="split">
<div>

<Figure class="h-full" src="/images/stepper-photo.jpg" photo alt="28BYJ-48 stepper motor with its plug in the ULN2003 driver board" credit="Photo: Kushagra Keshari · CC BY-SA 4.0 · Wikimedia Commons" />

</div>
<div>

It moves in small, exact **steps**.

<p class="chain">2048 steps = 1 turn = 360°</p>

<div v-click="1">

<p class="chain">2048 ÷ 4 = 512 steps = 90°</p>

</div>

<div v-click="2">

Unlike the servo, it **knows how far** it turned: it counts the steps.

</div>

<div v-click="3" class="note mt-4">

Slow, but strong: a gearbox inside turns many fast motor steps into one slow turn.

</div>

</div>
</div>

<!--
Servo (ours): speed and direction, no position. Stepper: exact position, slow. Pick the motor by the job: a louvre that has to stand at 45° needs the stepper.
2048 is the usual number for this motor (the gearbox is about 64 : 1). Exactly it's 2037.9, so after many turns it drifts a little. Not worth mentioning unless asked.
Click 1: follow one number, as with the temperature. 45° would be 256 steps: that's the Try two slides later.
-->

---
clicks: 3
---

<p class="eyebrow">Stepper</p>

# Why the extra board

<p class="chain">pin → board → motor</p>

<div class="split mt-4">
<div>

<div v-click="1" class="spec"><b>Pin</b><code>8 mA</code><span>only says <strong>"now"</strong></span></div>
<div v-click="2" class="spec"><b>Board</b><code>≈ 250 mA</code><span>switches the current from the <strong>5V rail</strong></span></div>
<div v-click="3" class="spec"><b>Motor</b><span>four coils, switched on <strong>one after the other</strong></span></div>

</div>
<div>

<div v-click="3" class="note">

The four small lights on the board show which coil is on. Watch them while the motor turns.

</div>

</div>
</div>

<!--
Link back: a pin gives 8 mA. An LED needs about 6, a motor much more. That's why the resistor mattered for the LED, and why the motor needs help.
The board's black chip (ULN2003) is made of transistors: switches that a small current opens for a big one. Exactly what we don't have loose in the kit.
Same for the servo: it has its own electronics inside, so the pin only sent a signal there too.
At slow speed (setSpeed(1)) students can follow the lights one by one.
-->

---

<p class="eyebrow">Stepper</p>

# Build it

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-stepper.svg" alt="Driver board: IN1 to IN4 to pins 8, 9, 10, 11; board + to 5V, − to GND on the Arduino; the motor plugged into the board." credit="Made with Fritzing · parts by mgesteiro" />

</div>
<div>

1. **Unplug.** Take out the servo and the knob
2. Motor's white plug → the board
3. **IN1, IN2, IN3, IN4** → pins **8, 9, 10, 11**
4. Board **+** → **5V**, **−** → **GND** on the Arduino

<div class="note mt-4">

The plug only fits one way round.

</div>

</div>
</div>

<!--
Most common mistake: IN wires in a different order. Then the motor buzzes or shakes instead of turning. Check: IN1 → 8, IN2 → 9, IN3 → 10, IN4 → 11.
Power: USB is enough for one stepper (about 250 mA of the roughly 500 mA a USB port gives). The breadboard power supply is for later: several motors, or the 6 V DC motor. With it, its GND must join the Arduino's GND.
The motor gets warm while it holds still: the coils stay on. Normal.
The small jumper next to + and − on the board (on/off) must be in place, or nothing happens.
-->

---
class: code-compact
---

<p class="eyebrow">Stepper</p>

# Turn it

<div class="split">
<div>

<<< @/sketches/15-stepper-turn/15-stepper-turn.ino cpp {all|4|7|11-13|all}

</div>
<div>

<div v-click="1" class="spec"><b><code>Stepper motor(…)</code></b><span>steps per turn, then the pins: <strong>8, 10, 9, 11</strong></span></div>
<div v-click="2" class="spec"><b><code>setSpeed(10)</code></b><span><strong>10 turns</strong> per minute</span></div>
<div v-click="3" class="spec"><b><code>step(512)</code></b><span>a <strong>quarter turn</strong>. <code>-512</code>: back</span></div>

<div v-click="4" class="task mt-2">

**Try:** make it turn **45°** and back.

</div>

</div>
</div>

<!--
#include <Stepper.h>: the library, like Servo.h.
8, 10, 9, 11 is not a typo: the library switches the coils in a different order than the board numbers them. With 8, 9, 10, 11 the motor only buzzes. The wires stay in order 8, 9, 10, 11: only the code is swapped.
setSpeed: about 15 is the most this motor manages on 5 V. Above that it skips steps or stands still and hums.
step() waits until it's done: while the motor turns, nothing else in loop runs. Like delay.
The Try: 45° = 512 ÷ 2 = 256.
-->

---
class: code-compact
---

<p class="eyebrow">Stepper</p>

# Turn by a number

<div class="split">
<div>

<<< @/sketches/16-stepper-turn-by/16-stepper-turn-by.ino cpp {all|12-13|14|15|all}

</div>
<div>

<div v-click="1" class="spec"><b><code>Serial.available()</code></b><span>you typed something? Then read it as a <strong>number</strong></span></div>
<div v-click="2" class="spec"><b><code>map</code></b><span><code>0</code> … <code>360</code>° → <code>0</code> … <code>2048</code> steps</span></div>
<div v-click="3" class="spec"><b><code>step(steps)</code></b><span>turns <strong>by</strong> that much, from wherever it is</span></div>

<div v-click="3">

<p class="chain">90 → step(512) · −90 → step(−512)</p>

</div>

<div v-click="4" class="task mt-2">

**Try:** in the Serial Monitor, type `90` three times, then `-270`.

</div>

</div>
</div>

<!--
Serial Monitor: type into the input line, press Enter. Line ending setting "New Line" (the default).
readStringUntil('\n'): reads up to the Enter. toInt(): turns the text "90" into the number 90.
The Try: 3 × 90 = 270, then −270: back where it started.
Every 90 turns again: the motor doesn't know where it is, it only moves. That's the difference to the next slide.
-->

---
class: code-compact
---

<p class="eyebrow">Stepper</p>

# Go to a number

<div class="split">
<div>

<<< @/sketches/17-stepper-go-to/17-stepper-go-to.ino cpp {all|5|16-17|all}

</div>
<div>

<div v-click="1" class="spec"><b><code>int position = 0;</code></b><span>outside the loop: it <strong>remembers</strong> where the motor is</span></div>
<div v-click="2" class="spec"><b><code>step(target - position)</code></b><span>only the <strong>difference</strong>, then remember the new place</span></div>

<div v-click="2">

<p class="chain">at 90°, you type 45 → step(−256)</p>

</div>

<div v-click="3" class="task mt-2">

**Try:** type `90`, then `90` again. Then `360`, then `0`.

</div>

</div>
</div>

<!--
Same as the last slide, plus memory. Now 90 means "go to 90°", not "turn 90° more".
The new idea: int position = 0; sits outside loop(), so it keeps its value from one round to the next. Inside loop(), it would start at 0 every round.
The example: 90° = 512 steps, 45° = 256 steps. 256 − 512 = −256: back.
The Try: the second 90 does nothing (already there). 360 → 0: a whole turn back, though it's the same place.
Think of a ruler that never wraps: −90 … 0 … 90 … 360. The motor travels from its place to the new one, through every step in between. It doesn't know "the short way". Typing −90 after 270 = a full turn back.
Wherever the motor stands at upload counts as 0°. Real façades use a switch at the end position to find their zero ("homing").
Turn by = movement, go to = position. Live data later is a value (wind 30 km/h), so it needs "go to".
Architecture: a louvre set by a number, e.g. 0° closed, 90° open.
-->

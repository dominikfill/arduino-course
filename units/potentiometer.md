---
clicks: 3
---

<p class="eyebrow">Potentiometer</p>

# A knob that picks a voltage

<div class="split">
<div>

<Pot :value="[0.5, 0.15, 0.9, 0.5][$clicks] ?? 0.5" />

</div>
<div>

The two **outer legs** go to **5 V** and **GND**. Between them runs a resistive track.

The **middle leg** slides along the track. Turn the knob: it picks a voltage between 0 and 5 V.

<div v-click="1" class="mt-4">

**A0** measures that voltage as a number: **0** at 0 V, **1023** at 5 V.

</div>

<div v-click="3" class="mt-4">

Not two states, but a whole **range**: that's **analog**.

</div>

</div>
</div>

<!--
The track is one resistor. The middle leg splits it into two parts that share the 5 V, like LED and resistor, or pull-up and button.
Middle leg close to GND: low voltage, small number. Close to 5 V: high voltage, large number.
Click 1: turn down. Click 2: turn up. Click 3: back to the middle. Turn a real one while you click.
A0–A5 are the analog inputs: only these pins can measure in-between voltages.
-->

---

<p class="eyebrow">Potentiometer</p>

# Build it

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-pot.svg" alt="Potentiometer: outer legs to 5V and GND, middle leg to A0; LED on pin 9" credit="Made with Fritzing" />

</div>
<div>

1. Outer leg → **5V** (red wire)
2. Other outer leg → **−** rail
3. Middle leg → **A0**

<div class="note mt-4">

The LED stays as it is.

</div>

</div>
</div>

<!--
First time students wire real 5 V: red wire for 5V, the colour convention pays off here.
Which outer leg goes to 5V doesn't matter: swapped, the knob just works the other way round.
Most common mistake: middle leg to 5V or GND instead of A0. Then turning does nothing.
-->

---
class: code-compact
---

<p class="eyebrow">Potentiometer</p>

# Turn the knob, change the heartbeat

<div class="split">
<div>

<<< @/sketches/04-pot-heartbeat/04-pot-heartbeat.ino cpp {all|2|10|19|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>A0</code></b><span>an <strong>analog</strong> input: A0–A5</span></div>
<div v-click="2" class="spec compact"><b><code>analogRead</code></b><span>measures the voltage: <code>0</code> … <code>1023</code></span></div>
<div v-click="2" class="spec compact"><b><code>int pause</code></b><span>a variable that <strong>changes</strong>: a new value every loop</span></div>
<div v-click="3" class="spec compact"><b><code>delay(pause)</code></b><span>the <code>800</code> from your first sketch, now set by hand</span></div>

<div v-click="4" class="task mt-4">

**Try:** what's the fastest heartbeat you can set? The slowest?

</div>

</div>
</div>

<!--
LED_PIN never changes: const. pause changes every time through loop(): no const. That's what makes a variable worth having.
The pause is in ms: knob at 1023 = about 1 s. Knob at 0 = no pause: the second beat runs straight into the next first beat, the double beat merges into an even blink. Let them discover it ("what's the fastest heartbeat?"), then the fix: int pause = analogRead(POT_PIN) + 300; A measured value often needs adjusting before it's useful.
Fast students: make the knob work the other way round (1023 - analogRead(POT_PIN)), or change the range.
-->

---
class: code-compact
---

<p class="eyebrow">Potentiometer</p>

# See the number

<div class="split">
<div>

<<< @/sketches/04-pot-heartbeat/04-pot-heartbeat.ino cpp {6,11}

</div>
<div>

<div class="spec compact"><b><code>Serial.begin</code></b><span>opens a line to the laptop</span></div>
<div class="spec compact"><b><code>Serial.println</code></b><span>sends a value, one per line</span></div>

<div class="task mt-4">

**Try:** open **Tools → Serial Monitor**. Turn the knob: what's the smallest and largest number?

</div>

</div>
</div>

<!--
The Serial Monitor is how we'll look at every sensor from now on: before reacting to a value, see it.
If the monitor shows garbage: the baud rate at the bottom right must match 9600.
The numbers come once per heartbeat: the delay again.
Smallest/largest: about 0 and 1023, often not quite, the knob's ends aren't perfect. Real measurements are never exact, like the 4.7 V.
-->

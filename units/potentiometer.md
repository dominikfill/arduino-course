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

The **middle leg** splits the track in two. The two parts **share the 5 V**, like LED and resistor. Turn the knob: the split moves, and so does the voltage.

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
A0–A5 are the analog inputs: only these pins can measure in-between voltages. Point at ANALOG IN on their board, it's in the next wiring image too.
-->

---

<p class="eyebrow">Potentiometer</p>

# Build it

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-pot.svg" alt="Potentiometer: outer legs to 5V and GND, middle leg to A0; LED on pin 9" credit="Made with Fritzing" />

</div>
<div>

1. **Unplug.** **5V** → **+** rail (red wire)
2. **Knob** into the breadboard: three legs in **three different strips**
3. Outer leg → **+** rail, other outer leg → **−** rail
4. Middle leg → **A0**

<div class="note mt-4">

The LED stays as it is. The button can stay too: this sketch ignores it.

</div>

</div>
</div>

<!--
First time students wire real 5 V and use the + rail: red wire for 5V, the colour convention pays off here.
Which outer leg goes to 5V doesn't matter: swapped, the knob just works the other way round.
Most common mistake: middle leg to 5V or GND instead of A0. Then turning does nothing.
-->

---

<p class="eyebrow">Potentiometer</p>

# See the number

<div class="split">
<div>

<<< @/sketches/04a-pot-serial/04a-pot-serial.ino cpp {all|1|4|8|9|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>A0</code></b><span>an <strong>analog</strong> input: A0–A5</span></div>
<div v-click="2" class="spec compact"><b><code>Serial.begin</code></b><span>opens a line to the laptop</span></div>
<div v-click="3" class="spec compact"><b><code>analogRead</code></b><span>measures the voltage: <code>0</code> … <code>1023</code></span></div>
<div v-click="4" class="spec compact"><b><code>Serial.println</code></b><span>sends a value, one per line</span></div>

<div v-click="5" class="task mt-4">

**Try:** upload, then open **Tools → Serial Monitor**. Turn the knob: what's the smallest and largest number?

</div>

</div>
</div>

<!--
Before reacting to a value, see it. The Serial Monitor is how we'll look at every sensor from now on: the light sensor and the temperature sensor start the same way.
If the monitor shows garbage: the baud rate at the bottom right must match 9600.
delay(100): ten numbers a second, enough to watch, not too many to read.
Smallest/largest: about 0 and 1023, often not quite, the knob's ends aren't perfect. Real measurements are never exact, like the 4.7 V.
-->

---
class: code-compact
---

<p class="eyebrow">Potentiometer</p>

# Turn the knob, change the heartbeat

<div class="split">
<div>

<<< @/sketches/04-pot-heartbeat/04-pot-heartbeat.ino cpp {all|10|19|all}

</div>
<div>

The knob's number, now used as a **pause**.

<div v-click="1" class="spec compact"><b><code>int pause</code></b><span>a variable that <strong>changes</strong>: a new value every loop</span></div>
<div v-click="2" class="spec compact"><b><code>delay(pause)</code></b><span>the <code>800</code> from your first sketch, now set by hand</span></div>

<div v-click="3" class="task mt-4">

**Try:** what's the fastest heartbeat you can set? The slowest?

</div>

</div>
</div>

<!--
Same reading as before, new name: pause says what the number is for now.
LED_PIN never changes: const. pause changes every time through loop(): no const. That's what makes a variable worth having.
Serial stays in: they can watch the number while they tune. It now arrives once per heartbeat: the delay again.
The pause is in ms: knob at 1023 = about 1 s. Knob at 0 = no pause: the second beat runs straight into the next first beat, the double beat merges into an even blink. Let them discover it ("what's the fastest heartbeat?"), then the fix: int pause = analogRead(POT_PIN) + 300; A measured value often needs adjusting before it's useful.
Fast students: make the knob work the other way round (1023 - analogRead(POT_PIN)), or change the range.
-->

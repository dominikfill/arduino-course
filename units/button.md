---
clicks: 1
---

<p class="eyebrow">Button</p>

# A switch in the loop

<div class="split">
<div>

<Circuit current button :pressed="$clicks >= 1" />

</div>
<div>

Put a **button** into the loop: between the resistor and the **−** rail.

<div class="task mt-4">

**Try:** keep the heartbeat sketch running. What happens when you press?

</div>

<div v-click="1" class="mt-4">

Pressing **closes the loop**. The heartbeat only shows while you press.

</div>

</div>
</div>

<!--
No code change: the sketch keeps beating, the button decides whether current can flow.
The button is the gap from the loop slide, in their hand.
-->

---

<p class="eyebrow">Button</p>

# Switch or input?

<div class="split">
<div>

### Switch

<p class="chain">button → current → LED</p>

The button is **part of the loop**. It controls the current itself.

</div>
<div v-click>

### Input

<p class="chain">button → pin 2 → program → pin 9 → LED</p>

The button only **reports**: pressed or not. The **program** decides what happens.

</div>
</div>

<div v-click class="mt-8">

Only an **input** can make a space responsive: the program can react later, differently, or to many things at once.

</div>

<!--
This is the core idea of physical computing. Take your time.
Examples: a switch turns the light on. An input could turn it on only at night, or fade it, or count visitors.
-->

---

<p class="eyebrow">Button</p>

# Build it: the button as input

<div class="split wide-left">
<div>

<Figure src="/images/wiring-button.svg" alt="Button on pin 2, LED on pin 9" credit="Made with Fritzing" />

</div>
<div>

1. Take the button **out of the LED loop**: pin 9 → LED → 470 Ω → **−** rail, as before
2. Button legs into **two different strips**
3. One leg → **pin 2**, the other leg → **−** rail

<div class="note mt-4">

Two separate loops: the button touches nothing in the LED circuit. The **program** connects them.

</div>

</div>
</div>

<!--
Most common mistake: leaving the button in the LED loop from the previous step. Then pin 2 reads the LED circuit, not the button, and the heartbeat behaves erratically.
No resistor for the button: the Arduino has one built in (INPUT_PULLUP, explained after the code).
Signal wire for pin 2 in a signal colour (not red), like pin 9.
-->

---
class: code-compact
---

<p class="eyebrow">Button</p>

# The heart stops

<div class="split">
<div>

<<< @/sketches/03-button-heartbeat/03-button-heartbeat.ino cpp {all|2|6|10|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>BUTTON_PIN</code></b><span>a name for pin 2</span></div>
<div v-click="2" class="spec compact"><b><code>INPUT_PULLUP</code></b><span>built-in resistor. Not pressed = <code>HIGH</code>, pressed = <code>LOW</code></span></div>
<div v-click="3" class="spec compact"><b><code>digitalRead</code></b><span>reads the pin: <strong>digital</strong>, only <code>HIGH</code> or <code>LOW</code></span></div>
<div v-click="3" class="spec compact"><b><code>if ( ) { }</code></b><span>runs the lines inside only when the condition is <strong>true</strong></span></div>
<div v-click="3" class="spec compact"><b><code>==</code></b><span><strong>compares</strong>. A single <code>=</code> assigns.</span></div>

<div v-click="4" class="task mt-4">

**Predict:** press during the long pause, then during a beat. When does the heart stop?

</div>

</div>
</div>

<!--
INPUT_PULLUP: just name it here (not pressed = HIGH, pressed = LOW). The next slide explains why.
Read the if aloud: "if the button is not pressed, beat".
The delay: the button is only checked once per heartbeat, about every 1.2 s. While delay() waits, the board can't look at the button. That's why it reacts late. The fix (millis) comes in a later session.
-->

---
clicks: 4
---

<p class="eyebrow">Button</p>

# What INPUT_PULLUP does

<div class="split">
<div>

<PullUp :pullup="$clicks >= 2" :pressed="$clicks === 0 || $clicks >= 3" />

</div>
<div>

Pin 2 only **measures** the voltage at its connection.

**Pressed:** connected to GND → 0 V → `LOW`

<div v-click="1" class="mt-3">

**Released:** connected to nothing. The pin **floats** and reads random values.

</div>

<div v-click="2" class="mt-3">

`INPUT_PULLUP` adds a resistor from **5 V** to pin 2. No current flows, so no voltage is lost → 5 V → `HIGH`

</div>

<div v-click="3" class="mt-3">

**Pressed:** current flows through the pull-up and the button to GND. The **pull-up** takes all 5 V → 0 V → `LOW`

</div>

<div v-click="4" class="note mt-4">

Why not a plain wire to 5 V? Pressing would connect 5 V directly to GND: a **short circuit**.

</div>

</div>
</div>

<!--
Step by step, one click each:
0: pressed, no pull-up. Clear case: pin 2 is connected to GND, 0 V, LOW.
1: released. The pin is a wire end connected to nothing: no defined voltage, it picks up disturbances and reads random values. That's "floating".
2: INPUT_PULLUP switches on a resistor from 5 V to pin 2, inside the chip. No current flows (the input only measures, the button is open). Ohm's law: no current, no voltage drop across the resistor. The pin sees the full 5 V: HIGH.
3: pressed. Now current flows: 5 V, pull-up, pin 2, button, GND. Two parts share the 5 V, like LED and resistor earlier: the pull-up has a large resistance and takes almost all of it, the pressed button has almost none and takes almost 0 V. Pin 2 sits between them, on the button's side: 0 V, LOW. (The LED's 470 Ω is a separate circuit and plays no part here.)
The resistor is large, so this current stays tiny, far below 1 mA.
How can it "pull up" without current? Voltage is a level, not a flow: a point connected to 5 V is at 5 V. A resistor only creates a difference between its ends when current flows (current × resistance). No current, no difference: pin 2 sits at 5 V.
That's why the logic is inverted: not pressed HIGH, pressed LOW.
4: why a resistor and not a wire? A wire to 5 V would hold the pin HIGH too, but pressing would connect 5 V straight to GND: almost 0 Ω, huge current, the USB port shuts down or something breaks. The resistor holds the pin at 5 V while nothing flows, and gives way (takes the 5 V) when the button connects to GND. Same idea as the LED's resistor: it's what stops a short circuit.
Demo with a multimeter, pin 2 against GND: not pressed about 4.7 V (over USB the board's own supply is a bit under 5 V, same as the 5V pin, that's normal and still clearly HIGH), pressed 0 V.
-->

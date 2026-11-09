---
layout: section
---

# Recap

<!--
Skeleton: every slide below is a placeholder until we have agreed on its content.
-->

---

<p class="eyebrow">Recap</p>

# Inputs and outputs

<p class="chain">input → pin → program → pin → output</p>

<div class="split">
<div>

### Inputs report

- a **button**: pressed or not
- a **knob**: how far it's turned
- today, **sensors**: they measure the room
  - light sensor: how bright
  - temperature sensor: how warm
  - distance sensor: how far away

<p class="example">button → pin 2 · knob → A0</p>

</div>
<div>

### Outputs act

- an **LED**: on or off
- today, **dimmed**: not just on or off, but anything in between, from a soft glow to full brightness

<p class="example">LED → pin 9</p>

</div>
</div>

<!--
The core idea of physical computing, from "Switch or input?": an input only reports, the program decides, an output acts.
Nothing on the input side switches the LED directly. Everything goes through the program.
-->

---

<p class="eyebrow">Recap</p>

# Where they connect

<div class="split wide-left">
<div>

<Board :show="['digital', 'analog', 'power']" />

</div>
<div>

<div class="spec"><b>Digital pins</b><code>0–13</code><span>input <strong>or</strong> output: <code>pinMode</code> decides. <code>OUTPUT</code> for the LED, <code>INPUT_PULLUP</code> for the button.</span></div>
<div class="spec"><b>Analog pins</b><code>A0–A5</code><span>they <strong>measure</strong>: <code>0</code> … <code>1023</code></span></div>
<div class="spec"><b>Power</b><code>5V · GND</code><span><strong>5V</strong> feeds your parts, <strong>GND</strong> is the way back</span></div>

</div>
</div>

<!--
Digital pins are both: the same pin can drive an LED or read a button. pinMode in setup() decides which.
Analog pins only matter as inputs today. (They can also work as digital pins, not needed now.)
Everything we connect today goes to one of these three places.
-->

---
class: code-large
---

<p class="eyebrow">Recap</p>

# The parts of a sketch

<div class="split wide-left">
<div>

```cpp {all|1|3-5|7-9|3,7|all}
const int LED_PIN = 9;

void setup() {
  // runs once, at the start
}

void loop() {
  // runs again and again
}
```

</div>
<div class="mid-terms">

<div v-click="1" class="spec compact"><b><code>const</code></b><span>a <strong>name</strong> for a pin, set once at the top</span></div>
<div v-click="2" class="spec compact"><b><code>setup</code></b><span>runs <strong>once</strong>, when the board starts</span></div>
<div v-click="3" class="spec compact"><b><code>loop</code></b><span>runs <strong>again and again</strong>, top to bottom</span></div>
<div v-click="4" class="spec compact"><b><code>void</code></b><span>function has <strong>no</strong> return value</span></div>

<div v-click="5" class="note mt-6">

`;` ends an instruction · `{ }` groups lines · `( )` holds values · `//` a comment · capitals matter

</div>

</div>
</div>

<!--
The skeleton every sketch shares. The next two slides fill it: first with output code, then with input code.
[click] const int: change the pin in one place, not five.
[click] setup: settings such as pinMode. Unplug and replug: setup runs again.
[click] loop: after the last line, it starts again at the top. That's why the heartbeat keeps beating.
[click] void: as explained last week.
[click] The grammar behind most errors. And: after every change, upload again.
-->

---

<p class="eyebrow">Recap</p>

# Outputs in code

<div class="split">
<div>

```cpp {all|4|8,10|9,11|all}
const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
```

</div>
<div>

The skeleton, filled: the LED on pin 9 blinks.

<div v-click="1" class="spec compact"><b><code>pinMode</code></b><span>in <code>setup</code>: this pin is an <strong>OUTPUT</strong></span></div>
<div v-click="2" class="spec compact"><b><code>digitalWrite</code></b><span>switches the pin: <code>HIGH</code> = 5 V, <code>LOW</code> = 0 V</span></div>
<div v-click="3" class="spec compact"><b><code>delay</code></b><span>waits, in <strong>ms</strong> (1000 ms = 1 s)</span></div>

<div v-click="4" class="note mt-6">

</div>

</div>
</div>

<!--
Same skeleton as the slide before: setup and loop, now with lines inside.
[click] pinMode belongs in setup: the pin's role is decided once.
[click] digitalWrite: HIGH gives the loop its 5 V push, LOW takes it away.
[click] delay: without it, the LED would switch faster than the eye can see.
[click] The heartbeat: HIGH 100, LOW 120, HIGH 150, LOW 800.
-->

---

<p class="eyebrow">Recap</p>

# Inputs in code

<div class="split">
<div>

```cpp {all|5|10-12|13|6,14|all}
const int BUTTON_PIN = 2;
const int KNOB_PIN = A0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("pressed");
  }
  int knob = analogRead(KNOB_PIN);
  Serial.println(knob);
  delay(100);
}
```

</div>
<div>

The skeleton again, now with two inputs.

<div v-click="1" class="spec compact"><b><code>INPUT_PULLUP</code></b><span>pin 2 is an input, with the built-in resistor</span></div>
<div v-click="2" class="spec compact"><b><code>digitalRead</code></b><span><strong>digital</strong>: <code>HIGH</code> or <code>LOW</code>. Pressed = <code>LOW</code></span></div>
<div v-click="2" class="spec compact"><b><code>if ( ) { }</code></b><span>runs the inside only when the condition is <strong>true</strong></span></div>
<div v-click="3" class="spec compact"><b><code>analogRead</code></b><span><strong>analog</strong>: <code>0</code> … <code>1023</code></span></div>
<div v-click="4" class="spec compact"><b><code>Serial</code></b><span>sends values to the laptop: the Serial Monitor</span></div>

</div>
</div>

<!--
Same skeleton: names at the top, settings in setup, the work in loop.
[click] INPUT_PULLUP: pressed = LOW, not pressed = HIGH. Why: the pull-up slide later in this recap.
[click] digitalRead asks the pin. if decides. == compares (a single = assigns).
[click] analogRead: the knob's middle leg, measured. int knob: a variable, a new value every loop.
[click] Serial.begin once in setup, println every loop. Before reacting to a value, see it.
-->

---

<p class="eyebrow">Recap</p>

# Push, flow, narrowing

<div class="split">
<div>

<Circuit :voltage="$clicks >= 1" :current="$clicks >= 2" :resistance="$clicks >= 3" :share="$clicks >= 4 ? 2 : 0" />

</div>
<div>

<div v-click="1" class="spec compact"><b>Voltage</b><span><code>V</code> · the <strong>push</strong>, like water pressure</span></div>
<div v-click="2" class="spec compact"><b>Current</b><span><code>A</code> · the <strong>flow</strong>: how much passes</span></div>
<div v-click="3" class="spec compact"><b>Resistance</b><span><code>Ω</code> · the <strong>narrowing</strong></span></div>

<div v-click="4" class="mt-6">

**Ohm's law:** current = voltage ÷ resistance

<p class="chain">I = V ÷ R</p>

A resistor only **takes voltage** when **current flows** through it.

</div>

</div>
</div>

<!--
Voltage pushes, resistance limits, current is the result.
[click] Voltage: always between two points, here the pin (5 V) and GND (0 V).
[click] Current: the same everywhere in the loop. This is the chain from the next slides.
[click] Resistance: the narrow pipe that sets how much flows.
[click] The split shows in the drawing: ≈ 2 V for the LED, ≈ 3 V for the resistor. Two parts share the 5 V: that idea comes back with the pull-up. The next slide does the numbers.
-->

---
clicks: 7
---

<p class="eyebrow">Recap</p>

# Calculating the resistor

<div class="split">
<div>

<Circuit current voltage resistance :share="$clicks >= 2 ? 2 : $clicks >= 1 ? 1 : 0" />

</div>
<div>

<v-clicks>

1. The pin pushes **5 V**
2. The LED takes about **2 V**
3. The resistor gets the rest: 5 − 2 = **3 V**
4. The pin allows at most **8 mA** = 0.008 A
5. Ohm's law, asked the other way: R = V ÷ I = 3 V ÷ 0.008 A = **375 Ω**
6. That's the **smallest** resistor allowed. Take the next one up you have: **470 Ω**

</v-clicks>

<div v-click="7" class="note mt-4">

Check: 3 V ÷ 470 Ω ≈ **6.4 mA** · With 220 Ω: 3 V ÷ 220 Ω ≈ 13.6 mA

1 kΩ = 1000 Ω · 1 mA = 0.001 A

</div>

</div>
</div>

<!--
Last week we calculated the current for a given resistor. Now the other way round: which resistor do we need?
[click] The push: 5 V between pin and GND.
[click] The LED always takes about the same, about 2 V, as long as it's lit. Shown under the LED.
[click] The resistor gets what's left, shown under the resistor. Only this 3 V goes into the calculation, not 5 V: the classic mistake.
[click] The target: the pin's limit. The LED could take 20 mA, but the weakest part sets the limit.
[click] Same law as I = V ÷ R, rearranged: which resistance lets exactly 8 mA through at 3 V?
[click] Round up, never down: more resistance means less current, so safer. The kit has 470 Ω and 10 kΩ; 470 is the next one up. 10 kΩ would work too, but the LED would be very dim (0.3 mA).
[click] The check with I = V ÷ R. 220 Ω is common in tutorials for older boards like the UNO R3: too much for the R4. Over USB the pin gives about 4.7 V: 2.7 V ÷ 470 Ω ≈ 5.7 mA, even safer.
-->

---

<p class="eyebrow">Recap</p>

# A gap anywhere

<div class="split">
<div>

<Circuit current :gap="$clicks >= 1" />

</div>
<div>

A loop: from the pin, through the LED and the resistor, back to GND.

<div v-click="1" class="mt-4">

A **gap anywhere**, and the LED goes dark. Nothing flows, **anywhere** in the loop, not just after the gap.

</div>

<div v-click="2" class="mt-4">

**Why?** The wires are already **full**, like a **bicycle chain** that runs all the way round. The source pushes the whole chain at once: it moves **everywhere**, or **nowhere**.

</div>

</div>
</div>

<!--
From last week's "A circuit is a loop".
[click] The gap: a loose wire, a leg in the wrong strip. Current stops everywhere at once.
[click] The chain is the picture for the next slides. Electricity doesn't travel from + to the LED like water from a tap: the chain is already there, and every link moves at the same moment, at the same speed.
-->

---
clicks: 2
---

<p class="eyebrow">Recap</p>

# Before or after?

<div class="task">

**Predict:** one loop with the resistor **before** the LED, one with it **after**. Which LED is brighter?

</div>

<div v-click="1" class="mt-4">

**Both are the same.** The resistor is a **brake** on the chain. Wherever it sits, it slows the **whole** chain, so the same current flows everywhere, through the LED too.

</div>

<div v-click="2" class="note mt-6">

<a href="https://www.falstad.com/s.php?s=dgF3FZ" target="_blank">Falstad circuit simulator</a>

</div>

<!--
Collect guesses first. Most expect the LED after the resistor to be "protected" and the other to get "the full 5 V".
[click] The chain: nothing arrives at the LED first. The brake slows every link at once.
[click] Switch to Falstad. Show the dots: same speed in both loops. Hover over each LED: both 1.749 V, both about 6.9 mA. Voltmeter across each LED for the "difference between its legs".
If someone asks "but the LED's lower leg is at 5 V": a part only feels the difference between its two legs. Like a bird on a power line.
-->

---
clicks: 4
---

<p class="eyebrow">Recap</p>

# Two LEDs side by side

<div class="task">

**Predict:** two LEDs side by side. **A:** each has its own 470 Ω. **B:** both share one 470 Ω. Which shine brighter?

</div>

<div class="split mt-4">
<div v-click="1">

### A · a resistor each

Each branch works like the single loop: 3 V ÷ 470 Ω ≈ **6.4 mA** per LED.

The shared wire carries both: 6.4 + 6.4 = **12.8 mA**.

</div>
<div v-click="2">

### B · one shared resistor

One brake for both chains: about **6.4 mA in total**, shared: about **3.2 mA** each. Both dimmer.

</div>
</div>

<div v-click="3" class="mt-4">

**Every LED gets its own resistor.** And one pin delivers the **sum**: two LEDs on one pin = 12.8 mA, over the **8 mA**. Two LEDs, two pins.

</div>

<div v-click="4" class="note mt-3">

<a href="https://www.falstad.com/s.php?s=dgF3FZ" target="_blank">Falstad circuit simulator</a>

</div>

<!--
Side by side, the current splits: the chain divides into two branches and joins again.
[click] A: each branch has the full 5 V across it, so each calculates like the single loop. Where the branches run together, the currents add up.
[click] B: the shared resistor lets through as much as one loop would, and the two LEDs share it. Real LEDs are never identical: one usually takes most, one glows weakly.
[click] The rule, and the pin limit: the pin is the shared part. Or larger resistors: 1 kΩ each gives 2 × 3 mA = 6 mA.
[click] Switch to Falstad. Hover over the LEDs and over a shared wire. Falstad's LED takes 1.75 V instead of 2 V, so it shows about 6.9 mA and 3.5 mA: same pattern.
Change one resistor to 235 Ω: only that branch speeds up, the other stays the same, the shared wire carries the new sum.
-->

---
clicks: 2
class: code-compact
---

<p class="eyebrow">Recap</p>

# Just a button

<div class="split">
<div>

Pin 2 only **measures** the voltage at its connection. A button from pin 2 to GND:

```cpp
void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(2));
  delay(50);
}
```

**Pressed:** pin 2 is on GND → 0 V → `0`

<div v-click="1" class="mt-2">

**Released:** pin 2 is connected to **nothing**. It **floats**: it keeps the last value for a while, drifts, or jumps when you come close

</div>

</div>
<div>

<PullUp :pullup="false" outside :pressed="$clicks === 0" />

<div v-click="2" class="note mt-2">

Try it: touch the loose wire and watch the Serial Plotter.

</div>

</div>
</div>

<!--
The problem the next four slides solve, step by step. pinMode INPUT: no resistor switched on, the pin only listens.
digitalRead gives 1 for HIGH and 0 for LOW: that's what the Serial Monitor shows.
[click] Floating: a wire end connected to nothing has no defined voltage. The pin and its wire hold a tiny charge, like a very small bucket: after release it keeps its last level (0) for a while, because nothing fills or empties it. Then leaks and disturbances (your hand, the laptop, the room) push it around. You can't predict what it reads: that's the problem.
[click] Demo on the board (Falstad can't show floating): button from pin 2 to GND, nothing else, this sketch. Tools → Serial Plotter: after release it may stay at 0 for a few seconds, then drifts or jumps between 0 and 1. Move your hand towards the wire or touch it to speed it up. Press the button: a steady 0.
-->

---
clicks: 1
---

<p class="eyebrow">Recap</p>

# A wire to 5 V?

<div class="split">
<div>

<PullUp :pullup="false" wire outside :pressed="$clicks >= 1" />

</div>
<div>

The fix for floating? Connect pin 2 to **5 V** with a plain wire.

**Released:** pin 2 is on 5 V → `1`

<div v-click="1" class="mt-3">

**Pressed:** 5 V is connected **straight to GND**, nothing in between: a **short circuit**

</div>

<div v-click="1" class="note mt-4">

Don't build this. Nothing brakes the chain: the USB port shuts down, or the board gets damaged.

</div>

</div>
</div>

<!--
The obvious idea, and why it fails.
Released: the wire holds pin 2 at 5 V, no floating.
[click] Pressed: the button connects the 5 V wire to GND. Like the LED without a resistor, only worse: there's no part at all in between. Falstad shows gigaamps, the real board protects itself or breaks.
We need something that holds the pin at 5 V, but gives way when the button pulls it to GND: a brake.
-->

---
clicks: 2
---

<p class="eyebrow">Recap</p>

# A resistor to 5 V: the pull-up

<div class="split">
<div>

<PullUp outside :pressed="$clicks >= 1" />

</div>
<div>

A **10 kΩ** resistor from 5 V to pin 2, instead of the wire.

**Released:** no current flows, so the resistor takes nothing: 0 mA × 10 kΩ = **0 V**. Pin 2 is on 5 V → `1`

<div v-click="1" class="mt-3">

**Pressed:** pin 2 is on GND → `0`. Current: 5 V ÷ 10 kΩ = **0.5 mA**. The resistor is the brake.

</div>

<div v-click="2" class="mt-3">

The resistor **pulls** the pin **up** to 5 V, unless the button pulls it down. **Voltage needs a connection. Current needs a loop.**

<p class="example">a door closer: holds the door shut, but lets you push it open</p>

</div>

<div v-click="2" class="note mt-3">

Live in Falstad: 5 V, 10 kΩ, a switch, a test point as pin 2.

</div>

</div>
</div>

<!--
The same rules as with the LED.
Released: the button is a gap, the chain stands still. A resistor without current takes 0 V, so pin 2 sits at the full 5 V. (The pin itself takes no current: it only measures.)
[click] Pressed: the button is a wire to GND, so pin 2 is at 0 V. Now current flows, and the resistor takes all 5 V. 0.5 mA: tiny, harmless.
[click] Two parts share the 5 V: open button takes all of it (pin at 5 V), closed button takes none (pin at 0 V). The pin sits between them.
"Voltage needs a connection": released, pin 2 is connected to 5 V through the resistor, like a pressure gauge on a pipe with a closed tap: full pressure, no flow. "Current needs a loop": only when the button closes the loop does anything flow.
The name: "pull" = a gentle pull that can be overruled, "up" = towards 5 V. The door closer: the default state, overruled when pushed, back by itself when released.
On the real board, with the floating sketch: the 1 comes back immediately after release, no waiting. The resistor fills the "bucket" at once.
In Falstad: switch, 10 kΩ to 5 V, test point between them. Click the switch: 5 V / 0 V. Hover the resistor: 0 mA / 0.5 mA.
-->

---
clicks: 2
---

<p class="eyebrow">Recap</p>

# INPUT_PULLUP: the resistor is inside

<div class="split">
<div>

<PullUp :pressed="$clicks >= 1" />

</div>
<div>

The same circuit, built into the chip. One word in the code switches it on:

```cpp
pinMode(2, INPUT_PULLUP);
```

On the breadboard: **only the button**, from pin 2 to GND. The resistor from 5 V to pin 2 sits **inside** the Arduino.

<div v-click="1" class="mt-3">

**Released** → `HIGH` · **pressed** → `LOW`

</div>

<div v-click="2" class="mt-3">

That's why last week's button needed no resistor, and why **pressed = `LOW`**: the inverted logic comes from the pull-up.

</div>

</div>
</div>

<!--
The pull-up from the slide before, moved inside the chip. Every digital pin has one; INPUT_PULLUP switches it on, INPUT leaves it off.
[click] The same two states as with the 10 kΩ on the breadboard.
[click] if (digitalRead(2) == LOW) means "if pressed". Read it aloud that way.
Demo on the board: the floating sketch from "Just a button", change INPUT to INPUT_PULLUP and upload. Released: a steady 1, immediately. Pressed: 0. One word fixes it.
-->

---

<p class="eyebrow">Recap</p>

# Digital and analog

<div class="split">
<div>

### Digital

<Signal type="digital" compact />

Two states: `HIGH` = 5 V, `LOW` = 0 V

`digitalWrite` · `digitalRead`

<p class="example">LED on / off, button</p>

</div>
<div>

### Analog

<Signal type="analog" compact />

Any value from 0 to 5 V, measured as `0` … `1023`

`analogRead(A0)`

<p class="example">knob · today: light, temperature</p>

</div>
</div>

<!--
The two kinds of signal so far. Digital: on or off, nothing in between. Analog: any value in between, but only as an input: analogRead measures.
Our outputs so far are only digital: the LED is on or off. How a pin can dim comes next, right after building.
-->

---

<p class="eyebrow">Recap</p>

# Build it again

<div class="split wide-left">
<div>

<Figure class="h-full" src="/images/wiring-pot.svg" alt="LED on pin 9 with 470 Ω, knob between the rails, middle leg to A0" credit="Made with Fritzing" />

</div>
<div>

1. **Unplug.** **5V** → **+** rail (red), **GND** → **−** rail (blue)
2. **LED:** pin 9 → the strip of the long leg, short leg → **470 Ω** → **−** rail
3. **Knob:** three legs in three strips, outer legs → **+** and **−** rail
4. Middle leg → **A0**, then plug in

<div class="note mt-4">

Strips of 5 are one wire · the gap separates the halves · the rails run along the side

</div>

<div class="task mt-4">

**Try:** upload `04b-check-circuit`. Does the LED blink, and do the numbers go from 0 to 1023 when you turn the knob?

</div>

</div>
</div>

<!--
From an empty breadboard: everything PWM needs in the next slides. LED on pin 9 (a ~ pin), knob on A0.
Walk round and check: LED the right way round, the resistor between LED and − rail, the knob's middle leg on A0.
The test: 04b-check-circuit, LED and knob in one sketch. If the numbers don't move, the middle leg is in the wrong strip. If they stay at 0 (or at 1023) whatever you turn, one outer leg is not on its rail.
-->

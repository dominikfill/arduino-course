---
clicks: 1
---

<p class="eyebrow">Electricity</p>

# A circuit is a loop

<div class="split">
<div>

<Circuit current :gap="$clicks >= 1" />

</div>
<div>

From the pin, through the parts, **back to GND**.

<div v-click="1">

A gap anywhere, and **nothing flows**. A loose wire is the most common reason a circuit doesn't work.

</div>

</div>
</div>

<!--
Trace the loop with your finger: pin, LED, resistor, GND.
Click: the gap. The LED goes dark, current stops everywhere, not just after the gap.
-->

---
clicks: 4
---

<p class="eyebrow">Electricity</p>

# Voltage, current, resistance

<div class="split">
<div>

<Circuit :voltage="$clicks >= 1" :current="$clicks >= 2" :resistance="$clicks >= 3" />

</div>
<div>

<div v-click="1" class="spec"><b>Voltage</b><code>V · volt</code><span>the <strong>push</strong>, like water pressure</span></div>
<div v-click="2" class="spec"><b>Current</b><code>I · ampere</code><span>the <strong>flow</strong>: how much passes per second</span></div>
<div v-click="3" class="spec"><b>Resistance</b><code>R · ohm</code><span>the <strong>narrowing</strong>: a thin pipe lets less through</span></div>

<div v-click="4" class="mt-6">

Voltage **pushes**, resistance **limits**, current is the **result**.

</div>

</div>
</div>

<!--
Water analogy: voltage = water pressure, current = how much water flows, resistance = a narrow pipe.
Voltage always needs two points: here the pin (5 V) and GND (0 V). A battery in a drawer still has 1.5 V: push without flow, like a closed tap.
Current isn't used up: the same current flows through the LED and the resistor. What they share is the push: LED about 2 V, resistor about 3 V.
Stress the order: voltage pushes, resistance limits, current is the result.
-->

---

<p class="eyebrow">Electricity</p>

# Ohm's law

<div class="split">
<div class="flex flex-col justify-center items-center">

<div class="text-4xl">

$$
I = \frac{V}{R}
$$

</div>

current = push ÷ narrowing

</div>
<div>

- more voltage → **more** current
- more resistance → **less** current

<div class="task mt-6">

**Predict:** 5 V across **2 kΩ** instead of 1 kΩ. More or less current?

</div>

<div v-click class="mt-4">

**Less**, half as much:<br>
5 V ÷ 1000 Ω = 5 mA → 5 V ÷ 2000 Ω = **2.5 mA**

</div>

<div v-click class="note mt-4">

1 kΩ = 1000 Ω · 1 mA = 0.001 A

</div>

</div>
</div>

<!--
This is the tool for choosing a resistor. We apply it right after building the external LED.
Only this form today: we calculate current. V = I × R and R = V / I are the same law, rearranged; show them only if someone asks.
Watch out later: with an LED in the circuit, the resistor doesn't get the full 5 V. The LED takes about 2 V, so the resistor sees about 3 V.
-->

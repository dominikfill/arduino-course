<p class="eyebrow">External LED</p>

# Build it

<div class="split wide-left">
<div>

<Figure src="/images/wiring-external-led.svg" alt="External LED wiring: pin 9, LED, 470 Ω resistor, GND" credit="Made with Fritzing" />

</div>
<div>

1. Wire from **pin 9** to the LED's **long leg**
2. **Short leg** → **470 Ω** resistor → **−** rail
3. Wire from **GND** to the **−** rail

<div class="note mt-4">

**470 Ω** colour bands<br>
4 bands: yellow · violet · brown<br>
5 bands: yellow · violet · black · black

</div>

<div class="task mt-4">

**Predict:** what's in the circuit besides the LED, and why might it be needed?

</div>

</div>
</div>

<!--
Let them find the resistor themselves and collect guesses. The next slides answer the question.
Long leg = + side (anode). Most "it doesn't light" problems: LED backwards, or both legs in one strip.
-->

---
class: code-compact
---

<p class="eyebrow">External LED</p>

# Change the code

<div class="split">
<div>

<<< @/sketches/02-heartbeat-external/02-heartbeat-external.ino cpp {all|1|4,8,10,13,15|all}

</div>
<div>

<div v-click="1" class="spec"><b>Variable</b><code>const int LED_PIN = 9;</code><span>a <strong>name</strong> for a <strong>value</strong>: wherever the code says <code>LED_PIN</code>, it means 9</span></div>

<div v-click="2">

Change the pin in **one place**, not five.

</div>

<div v-click="3" class="task mt-4">

**Try:** change your heartbeat sketch like this and upload. Which LED beats now?

</div>

<div v-click="3" class="note mt-4">

Nothing lights up? Turn the LED around. Still nothing: are its legs in different strips?

</div>

</div>
</div>

<!--
const: the value can't change while the program runs. Good for pin numbers.
int: a whole number. More types later, when we need them.
Only the external LED beats now: the L LED is pin 13, and nothing controls it any more.
-->

---
clicks: 1
---

<p class="eyebrow">External LED</p>

# Why the resistor?

<div class="split">
<div>

<Circuit current high :resistor="false" />

<p class="text-center">No resistor: <strong>too much current</strong></p>

</div>
<div v-click="1">

<Circuit current />

<p class="text-center">470 Ω: about <strong>6 mA</strong></p>

</div>
</div>

<!--
Left: an LED barely resists on its own, so nothing limits the flow: too much for the LED and for the pin.
Click: the resistor is the narrow pipe. The blue stream gets thin.
-->

---
clicks: 4
---

<p class="eyebrow">External LED</p>

# How much current flows?

<div class="split">
<div>

<Circuit current voltage resistance />

</div>
<div>

<v-clicks>

1. The pin pushes **5 V**
2. The LED uses about **2 V**
3. The resistor gets the rest: **5 − 2 = 3 V**
4. **Ohm's law:** 3 V ÷ 470 Ω ≈ **6.4 mA**

</v-clicks>

<div v-click="4" class="note mt-4">

The LED could take 20 mA, but the **pin** allows only **8 mA**. The weakest part sets the limit.

</div>

</div>
</div>

<!--
Many online tutorials use 220 Ω: 3 V ÷ 220 Ω ≈ 14 mA. Fine on the older UNO R3, over the limit on the R4.
1 kΩ ≈ 3 mA: safe, just dimmer.
Your LED is rated 2.0–2.2 V: at 2.2 V the current is 2.8 V ÷ 470 Ω ≈ 6.0 mA. Still fine.
Blue and white LEDs drop about 3 V, so they get less current through the same resistor. 470 Ω is safe for every LED colour in the kit.
-->

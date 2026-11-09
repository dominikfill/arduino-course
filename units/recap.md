---
layout: section
---

# Recap

Three ways a pin can talk.

---

<p class="eyebrow">Recap</p>

# Digital, analog, PWM

<div class="split thirds">
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

<p class="example">knob · next: light, temperature</p>

</div>
<div>

### PWM ~

<Signal type="pwm" compact :steps="[0.25, 0.75]" />

Very fast on and off: the longer on, the brighter.

`analogWrite(9, 127)` · only **~** pins

<p class="example">dimming the LED with the knob</p>

</div>
</div>

<div class="note mt-2">

**Digital** = on / off · **Analog** = measuring in-between values · **PWM** = faking in-between values by switching fast

</div>

<!--
The three ways a pin can talk, now complete. LED on/off and button: digital. Knob: analog. Dimming: PWM.
Only analog IN is truly in-between here. On the ~ pins, the Arduino fakes in-between values with PWM. (The R4 has one real analog output, a DAC on A0; we don't need it.)
-->

<p class="eyebrow">Recap</p>

# Digital, analog, PWM

<div class="split thirds">
<div>

### Digital

<Signal type="digital" compact />

Two states:<br>
`HIGH` = 5 V<br>
`LOW` = 0 V
 
`digitalWrite` · `digitalRead`

<p class="example">LED on / off, button</p>

</div>
<div>

### Analog

<Signal type="analog" compact />

Any value from 0 to 5 V, measured as `0` … `1023`

`analogRead(A0)`

<p class="example">potentiometer, light sensor</p>

</div>
<div>

### PWM ~

<Signal type="pwm" compact :steps="[0.25, 0.5, 0.75]" />

Switches on and off very fast.<br>
The longer it's on, the brighter it looks.

`analogWrite(9, 127)` · only **~** pins

<p class="example">dimming, motor speed</p>

</div>
</div>

<div class="note mt-4">

**Digital** = on / off · **Analog** = measuring in-between values · **PWM** = faking in-between values by switching fast

</div>

<!--
Ask before revealing anything: which of today's parts was which? LED on/off, button, knob, dimming.
Only analog IN is truly in-between here. On the ~ pins, the Arduino fakes in-between values with PWM. (The R4 has one real analog output, a DAC on A0; we don't need it.)
-->

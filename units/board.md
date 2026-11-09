---
layout: section
---

# Building a circuit

From the board's own LED to one you wire yourself.

---

<p class="eyebrow">Board</p>

# The Arduino UNO R4

<div class="split wide-left">
<div>

<Board full :show="[[], ['usb'], ['usb', 'led', 'digital'], ['usb', 'led', 'digital', 'power']][$clicks]" />

</div>
<div>

<div v-click="1" class="spec"><b>USB-C</b><span>power, and the way new code gets onto the board</span></div>
<div v-click="2" class="spec"><b>Digital pins</b><code>0–13</code><span>switch <strong>on</strong> or <strong>off</strong>: 5 V or 0 V. The <strong>L</strong> LED is pin 13.</span></div>
<div v-click="3" class="spec"><b>Power</b><code>5V · GND</code><span><strong>5V</strong> feeds your parts, <strong>GND</strong> is the way back. 3.3V: not today.</span></div>

<div class="note mt-6">

Never set the board down on metal: keys, a laptop case, foil. The pins underneath short out.

</div>

</div>
</div>

<!--
Start with the bare photo: let them find the L LED on their own board first.
[click] USB-C: the cable they already used.
[click] Digital pins and the L LED: pin 13, the LED they just programmed.
[click] Power: out at 5V, back at GND. "The way back" leads straight into the next slide: a circuit is a loop.
PWM, analog in and the barrel jack: not now. The board comes back with those labels when we use them.
-->

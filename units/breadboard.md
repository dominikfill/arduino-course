---
clicks: 3
---

<p class="eyebrow">Breadboard</p>

# The breadboard

<div class="split wide-left">
<div>

<Breadboard rail :top="10" :bottom="10" labels :step="$clicks" />

</div>
<div>

Connects parts **without soldering**.

<div v-click="1">

Holes that are connected work like **one wire**.

</div>

<div v-click="2">

The **gap** in the middle separates the two halves.

</div>

<div v-click="3">

The **rails**: wire **5V** to **+** and **GND** to **−**, and every hole along them becomes 5V or GND.

<div class="note mt-4">

Real boards mark the rails red (+) and blue (−), like 5V and GND in our wiring drawings. Some split the rails in the middle: check first.

</div>

</div>

</div>
</div>

<!--
Hold up a real breadboard. Show the metal strips on the back with a photo, or with one board kept for showing: peeling the backing ruins the adhesive.
[click] One strip of 5: a part's leg in any of these holes is connected to the others.
[click] The gap: the two halves are separate. A part whose legs straddle it connects one half to the other.
[click] The rails, fed from the board: 5V on +, GND on −. That's where every circuit today finds its way back.
-->

---
clicks: 1
---

<p class="eyebrow">Breadboard</p>

# Where do the legs go?

<div class="split wide-left">
<div>

<Breadboard led :bottom="$clicks >= 1 ? 5 : undefined" />

</div>
<div>

<div class="task">

**Predict:** legs in **A5** and **B5**. However you wire it, this LED will never light. Why?

</div>

<div v-click="1" class="mt-4">

Both legs are in the same strip, so they're connected to each other. The loop never passes **through** the LED.

The legs must go into **different strips**.

</div>

</div>
</div>

<!--
Link back to the loop slide: current takes the connected path and skips the LED.
-->

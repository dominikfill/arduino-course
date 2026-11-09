<p class="eyebrow">Hardware</p>

# The breadboard

<div class="split wide-left">
<div>

<Breadboard rail :top="10" :bottom="10" labels />

</div>
<div>

Connects parts **without soldering**.

Holes that are connected work like **one wire**.

<div class="note mt-6">

On the real board, the rails are marked red (+) and blue (−). Some breadboards split the rails in the middle: check before relying on them.

</div>

</div>
</div>

<!--
Hold up a real breadboard. Show the metal strips on the back (peel off a corner of the backing, or show a photo).
Point at one strip of 5, the gap, and the rails while explaining.
-->

---
clicks: 1
---

<p class="eyebrow">Hardware</p>

# Where do the legs go?

<div class="split wide-left">
<div>

<Breadboard led :bottom="$clicks >= 1 ? 5 : undefined" />

</div>
<div>

<div class="task">

**Predict:** an LED with its legs in **A5** and **B5**. Will it light up?

</div>

<div v-click="1" class="mt-4">

**No.** Both legs are in the same strip, so they're connected to each other. The loop never passes **through** the LED.

The legs must go into **different strips**.

</div>

</div>
</div>

<!--
Link back to the loop slide: current takes the connected path and skips the LED.
-->

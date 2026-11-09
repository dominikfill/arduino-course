<p class="eyebrow">01 · First sketch</p>

# What will it do?

<div class="split wide-left">
<div>

<<< @/sketches/01-heartbeat/01-heartbeat.ino cpp

</div>
<div>

<div class="task">

**Predict:** read the code. What will the board do?

</div>

<div v-click class="task mt-6">

**Type it:** File → New Sketch, delete what's there, and type the code exactly as shown.

</div>

</div>
</div>

<!--
Let the room guess for a minute before revealing anything. No wrong answers yet.
Stay on this slide while they type (3–5 min): they need the code visible.
Keep heartbeat.ino ready for anyone stuck after ~5 min; have them compare it with their own version.
-->

---

<p class="eyebrow">01 · First sketch</p>

# Upload it

<div class="split">
<div>

1. **Plug in** the Arduino with the USB cable
2. **Board:** Tools → Board → Arduino UNO R4 Boards → **UNO R4 WiFi**
3. **Port:** Tools → Port → the one showing **UNO R4**
4. **Upload:** click the **→** arrow (top left)

<div class="note mt-6">

**Doesn't work?** No port listed: try another cable, some only charge. Error message: check every character against the code, more on that in a minute.

</div>

</div>
<div>

<div v-click>

The tiny LED marked **L** blinks like a heartbeat: two short flashes, then a pause.

</div>

<div v-click class="task mt-6">

**Predict:** what changes if `800` becomes `300`? Then test it.

</div>

</div>
</div>

<!--
Before the first click: ask who sees it blinking. Look for the L LED, not the LED matrix.
Common problems:
- No port: charge-only USB cable, or a loose plug. Swap cables.
- "Board not selected" / wrong board: re-check step 2.
- Compile error: typo. Don't fix it for them yet, the grammar slide is coming.
800 → 300: the heartbeat gets faster, more "excited". First hint of a responsive behaviour.
-->

---

<p class="eyebrow">01 · First sketch</p>

# Anatomy of a sketch

<div class="split">
<div>

<<< @/sketches/01-heartbeat/01-heartbeat.ino cpp {all|1-3|2|5-16|6-9|11-13|15|all}

</div>
<div>

<div v-click="1" class="spec compact"><b><code>setup()</code></b><span>runs <strong>once</strong> at the start</span></div>
<div v-click="2" class="spec compact"><b><code>pinMode</code></b><span>sets a pin as <strong>input</strong> or <strong>output</strong></span></div>
<div v-click="2" class="spec compact"><b><code>LED_BUILTIN</code></b><span>the onboard <strong>L</strong> LED (a name for pin 13)</span></div>
<div v-click="3" class="spec compact"><b><code>loop()</code></b><span>runs <strong>again and again</strong>, forever</span></div>
<div v-click="4" class="spec compact"><b><code>digitalWrite</code></b><span>switches a pin <strong>on</strong> or <strong>off</strong></span></div>
<div v-click="4" class="spec compact"><b><code>HIGH</code> / <code>LOW</code></b><span>on (5 V) / off (0 V)</span></div>
<div v-click="4" class="spec compact"><b><code>delay(100)</code></b><span>wait, in <strong>ms</strong> (1000 ms = 1 s)</span></div>

</div>
</div>

<!--
Clicks 5 and 6 highlight the second beat and the long pause: ask them to explain those lines themselves.
The program stays on the board: unplug it and power it from a power bank, and it keeps beating.
-->

---

<p class="eyebrow">01 · First sketch</p>

# Code grammar

<div class="split">
<div>

```cpp {all|3|2,4|2-3|1|3}
// the LED pin is an output
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
```

Code has a strict grammar. Small slips cause most beginner errors.

</div>
<div>

<div v-click="1" class="spec compact"><b><code>;</code></b><span>ends every instruction</span></div>
<div v-click="2" class="spec compact"><b><code>{ }</code></b><span>groups lines that belong together</span></div>
<div v-click="3" class="spec compact"><b><code>( )</code></b><span>follow every instruction name, and hold its values</span></div>
<div v-click="4" class="spec compact"><b><code>//</code></b><span>comment: for humans, ignored by the board</span></div>
<div v-click="5" class="spec compact"><b>Aa</b><span>capitals matter: <code>pinmode</code> ≠ <code>pinMode</code></span></div>

<div v-click="5" class="note mt-6">

`void` in front of `setup` and `loop`: ignore it for now.

</div>

</div>
</div>

---

<p class="eyebrow">01 · First sketch</p>

# Break it, then explain it

<div class="split">
<div>

<div class="task">

**Try:** delete one `;` in your heartbeat sketch and click **✓ Verify**. Which line does the error point to?

</div>

<div v-click class="mt-4">

The error often points to the line **after** the missing `;`, so look one line up. Put the `;` back.

</div>

</div>
<div>

<div v-click>

<div class="task">

**Try:** add a comment to every line, in your own words.

</div>

```cpp
delay(800);  // pause before the next heartbeat
```

</div>

</div>
</div>

<!--
Breaking code on purpose: students learn to read error messages without the stress of a real failure.
Comments: walk around and read a few aloud. Good comments say what it's for, not just what it says.
-->
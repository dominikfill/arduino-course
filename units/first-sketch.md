---
layout: section
---

# First sketch

Type a program, run it on the board, break it on purpose.

<!--
About 25–30 min: typing, uploading, reading the code, drawing the rhythm, two errors, comments.
-->

---

<p class="eyebrow">First sketch</p>

# What will it do?

<div class="split wide-left">
<div>

<<< @/sketches/01-heartbeat/01-heartbeat.ino cpp

</div>
<div>

<div class="task">

**Type it:** File → New Sketch, delete what's there, and type the code exactly as shown.

</div>

<div v-click class="task mt-6">

**Predict:** something switches on and off. In what rhythm? Tap it on the table.

</div>

</div>
</div>

<!--
Stay on this slide while they type (3–5 min): they need the code visible.
Keep 01-heartbeat.ino ready for anyone stuck after ~5 min; have them compare it with their own version.
[click] Once most have typed it: everyone taps the rhythm at once. No wrong answers yet.
Hint if stuck: the numbers are durations; 100 is short, 800 is long.
Don't confirm or correct: go straight to "Upload it", the board gives the answer.
-->

---

<p class="eyebrow">First sketch</p>

# Upload it

<Annotated src="/images/ide-toolbar.png" alt="Arduino IDE toolbar"
              :marks="[{ n: 2, x: 33.5, y: 70 }, { n: 3, x: 13, y: 70 }]" />
   <div class="mb-6"></div>

<div class="split">
<div>

1. **Plug in** the Arduino with the USB cable
2. **Select** **Arduino UNO R4 WiFi** in the board dropdown
3. **Upload:** click the **→** arrow

<div class="note mt-6">

**Doesn't work?** No port listed: try another cable, some only charge. Error message: check every character against the code, more on that in a minute.

</div>

</div>
<div>

<div v-click>

The tiny LED marked **L** blinks like a heartbeat: two short flashes (`100`, `150`), then a long pause (`800`).

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
- Dropdown shows no R4, or "Select Board": Tools → Board → Arduino UNO R4 Boards → UNO R4 WiFi, then Tools → Port → the one showing UNO R4.
- No "Arduino UNO R4 Boards" in that menu: the board package is missing. Accept the IDE's install offer (slow on shared wifi), or pair them with a neighbour meanwhile.
- Compile error: typo. Don't fix it for them yet, the grammar slide is coming.
800 → 300: the heartbeat gets faster, more "excited". First hint of a responsive behaviour.
Say it once: after every change, upload again. The board only knows the last upload.
-->

---

<p class="eyebrow">First sketch</p>

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

<div v-click="7" class="note mt-6">

Top to bottom, then `loop()` starts again.

</div>

</div>
</div>

<!--
Clicks 5 and 6 highlight the second beat and the long pause: ask them to explain those lines themselves.
[click:7] Show it: swap the laptop for a power bank. The board needs no computer to run, so it can sit inside a model or an installation.
-->

---

<p class="eyebrow">First sketch</p>

# The rhythm, drawn

<div class="split">
<div>

<<< @/sketches/01-heartbeat/01-heartbeat.ino cpp {all|6-7|8-9|11-12|13-15|all}

</div>
<div>

<Rhythm :step="$clicks" />

<div v-click="6" class="task mt-6">

**Try:** draw a rhythm of your own on paper: on, off, on… Then change the code so the LED plays it.

</div>

</div>
</div>

<!--
Each click draws one segment next to its lines: on 100, off 120, on 150, off 800. Click 5: one loop, and it starts again.
The drawing is to scale: the long pause really is most of the loop. Same kind of drawing returns for PWM later.
[click:6] 5 min. They may add lines or change numbers. Ask two or three to tap their rhythm before uploading.
-->

---
class: code-large
---

<p class="eyebrow">First sketch</p>

# Code grammar

<div class="split wide-left">
<div>

```cpp {all|3|2,4|2-3|1|3}
// the LED pin is an output
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
```

Code has a strict grammar. Small slips cause most beginner errors.

<div v-click="5" class="note mt-6">

Known words change colour in the IDE. If one stays black, check its spelling.

`void` in front of `setup` and `loop`: ignore it for now.

</div>

</div>
<div class="short-terms">

<div v-click="1" class="spec compact"><b><code>;</code></b><span>ends every instruction</span></div>
<div v-click="2" class="spec compact"><b><code>{ }</code></b><span>groups lines that belong together</span></div>
<div v-click="3" class="spec compact"><b><code>( )</code></b><span>follow every instruction name, and hold its values</span></div>
<div v-click="4" class="spec compact"><b><code>//</code></b><span>comment: for humans, ignored by the board</span></div>
<div v-click="5" class="spec compact"><b>Aa</b><span>capitals matter: <code>pinmode</code> ≠ <code>pinMode</code></span></div>

</div>
</div>

---

<p class="eyebrow">First sketch</p>

# Break it, explain it

<div class="split wide-left">
<div>

<div class="task">

**Try:** delete one `;`, then click **✓ Verify**. Which line does the error point to?

</div>

<div v-click="1">

```text
error: expected ';' before 'digitalWrite'
```

**expected**: something is missing, often on the line above.

</div>

<div v-click="2" class="task mt-4">

**Try:** put the `;` back. Now change `pinMode` to `pinmode`. Watch its colour, then Verify.

</div>

<div v-click="3">

```text
error: 'pinmode' was not declared in this scope
```

**not declared**: a name it doesn't know. Check the spelling, capitals too.

</div>

</div>
<div>

<div v-click="4">

<div class="task">

**Try:** fix it, then add a comment to every line, in your own words.

</div>

```cpp
// pause before the next heartbeat
delay(800);  
```

</div>

</div>
</div>

<!--
Breaking code on purpose: students learn to read error messages without the stress of a real failure.
[click] The exact word after "before" depends on which ; they deleted ('delay', '}' …). The line number is in the message too, and the IDE marks the line red.
[click] pinmode turns black before anything else happens: the colour tip from the last slide.
[click] The message may end with "did you mean 'pinMode'?". Both messages come back all session: a typo in any name (LED_PIN, pause …) gives "not declared".
[click] Comments: walk around and read a few aloud. Good comments say what it's for, not just what it says.
-->

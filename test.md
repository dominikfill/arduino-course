---
# Projector test deck: checks the visual system, not course content.
# Run with: npm run dev:test
theme: default
title: Projector test · Arduino course
colorSchema: light
fonts:
  sans: IBM Plex Sans
  mono: IBM Plex Mono
  weights: '400,500,600'
lineNumbers: false
transition: none
layout: cover
---

# Reading light

Physical Computing · projector test

---

<p class="eyebrow">01 · Type</p>

# Hierarchy at the back of the room

Subtitle line in the muted colour. Check that it is still clearly readable.

Body text at 1.15rem. **Bold for key terms.** Inline `analogRead()` code.

- First point of a list
- Second point, a little longer, to check the line height on wrap across two lines
- Third point

<div class="note">
Note: a smaller side remark in the muted colour. Readable from the last row?
</div>

---

<p class="eyebrow">02 · Inputs</p>

# Reading light: analog input

<div class="split">
  <Figure src="/circuits/ldr-divider.svg" alt="LDR voltage divider on A0" credit="Drawing: test schematic" />
  <div>

```cpp
int light = analogRead(A0);
Serial.println(light);
```

<div class="task">

**Predict:** you cover the sensor with your hand. Does the number go up or down?

</div>
  </div>
</div>

---

<p class="eyebrow">03 · Code</p>

# A whole sketch, stepped through

<<< @/sketches/03-light-sensor/03-light-sensor.ino cpp {all|4|6-8|10-14}

---

<p class="eyebrow">04 · Images</p>

# White backgrounds blend into the paper

<div class="split">
  <Figure src="/circuits/white-bg-test.svg" alt="Test: white-background export" credit="Should show no white rectangle" />
  <div class="placeholder">Placeholder: photo of the light-sensor model</div>
</div>

---

<p class="eyebrow">05 · Reference</p>

# Specs and tables

<div class="split">
  <div>
    <div class="spec"><b>Analog input</b><code>A0–A5</code><span>Reads a voltage between 0 and 5 V as a number from 0 to 1023.</span></div>
    <div class="spec compact"><b><code>setup()</code></b><span>runs once at start</span></div>
    <div class="spec compact"><b><code>loop()</code></b><span>repeats forever</span></div>
  </div>
  <div>

| Sensor | Measures | Signal |
|---|---|---|
| LDR | Light | Analog |
| PIR | Movement | Digital |
| DHT22 | Temp, humidity | Data |

  </div>
</div>

---
layout: section
---

# 02 · Outputs

---
footer: false
---

# No footer on this slide

Set with `footer: false` in the slide's frontmatter.

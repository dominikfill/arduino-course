<script setup lang="ts">
// A light sensor (LDR) from 5 V to A0, and a fixed 10 kΩ pull-down from A0 to GND.
// Together they share the 5 V; A0 measures the voltage between them.
//
//   <Ldr :light="1" />                               bright, with 10 kΩ
//   <Ldr :light="0" :fixed="false" />                dark, without 10 kΩ: A0 stays at 5 V
//   <Ldr :fixed="$clicks >= 2" :light="[1, 0, 1, 0][$clicks] ?? 0" />
//   <Ldr button :pressed="$clicks >= 1" />           a button instead of the sensor: the plain pull-down
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  light?: number    // 0 = dark, 1 = bright
  fixed?: boolean   // the 10 kΩ from A0 to GND is in place
  button?: boolean  // draw a push button where the sensor sits (pull-down with a button)
  pressed?: boolean // ...and whether it is pressed
}>(), {
  light: 1,
  fixed: true,
})

const l = computed(() => Math.min(1, Math.max(0, props.light)))
// LDR resistance: about 100 kΩ in the dark, about 1 kΩ in bright light
const rLdr = computed(() => 10 ** (5 - 2 * l.value))
// without the 10 kΩ no current flows: no drop, A0 sees the full 5 V
const volts = computed(() => {
  if (props.button) return props.pressed ? 5 : (props.fixed ? 0 : NaN)
  return props.fixed ? (5 * 10000) / (rLdr.value + 10000) : 5
})
const reading = computed(() =>
  Number.isNaN(volts.value) ? '?' : Math.round((volts.value / 5) * 1023))
// current flows only through a closed path: 5 V → sensor (or pressed button) → 10 kΩ → GND
const flowing = computed(() => props.fixed && (!props.button || props.pressed))
const kOhm = computed(() => {
  const k = rLdr.value / 1000
  return k >= 10 ? `${Math.round(k)} kΩ` : `${k.toFixed(1)} kΩ`
})
const gloss = computed(() => {
  if (props.button) {
    if (props.pressed) return '5 V · connected to 5 V'
    return props.fixed ? '0 V · no current, no drop' : 'floating · not connected'
  }
  return props.fixed ? `≈ ${volts.value.toFixed(1)} V` : '5 V · no current, no drop'
})
</script>

<template>
  <svg class="ldr" viewBox="0 0 480 400" role="img"
       aria-label="Light sensor from 5 V to A0, 10 kΩ pull-down from A0 to GND">
    <!-- always there: 5 V → sensor → A0 -->
    <path class="wire" d="M90 84V100M90 180V210M90 210H230" />

    <!-- the 10 kΩ path to GND -->
    <g class="layer" :class="{ on: fixed }">
      <path class="wire" d="M90 210V240M90 320V346" />
    </g>

    <!-- current: only through a closed path -->
    <g class="layer" :class="{ on: flowing }">
      <path class="flow" d="M90 84V346" />
      <path class="signal-fill" d="M83 192L90 206L97 192ZM83 326L90 340L97 326Z" />
    </g>

    <!-- 5 V -->
    <rect class="part" x="40" y="44" width="100" height="40" />
    <text class="label" x="90" y="69" text-anchor="middle">5 V</text>

    <!-- light falling on the sensor -->
    <g v-if="!button" class="light" :style="{ opacity: 0.15 + 0.85 * l }">
      <path class="ray" d="M24 104L66 128M24 140L66 158" />
      <path class="ink-fill" d="M70 130L58 129L63 120ZM70 160L58 160L62 151Z" />
    </g>

    <!-- LDR -->
    <g v-if="!button">
      <rect class="part" x="76" y="100" width="28" height="80" />
      <path class="zigzag" d="M90 108l-7 8l14 8l-14 8l14 8l-14 8l14 8l-7 8" />
      <text class="label" x="120" y="132">LIGHT SENSOR</text>
      <text class="gloss" x="120" y="152">≈ {{ kOhm }}</text>
    </g>

    <!-- or a push button in the same place -->
    <g v-else>
      <rect class="knockout" x="70" y="100" width="44" height="80" />
      <path class="wire" d="M90 100V118M90 162V180" />
      <path v-if="pressed" class="wire" d="M90 118V162" />
      <path v-else class="wire" d="M90 118L112 152" />
      <circle class="terminal" cx="90" cy="118" r="3.5" />
      <circle class="terminal" cx="90" cy="162" r="3.5" />
      <text class="label" x="124" y="146">BUTTON</text>
    </g>

    <!-- A0 -->
    <circle class="dot" cx="90" cy="210" r="4" />
    <rect class="pin" x="230" y="200" width="20" height="20" />
    <text class="label" x="258" y="216">A0</text>
    <text class="gloss" x="230" y="240">only looks, no current in</text>

    <!-- reading -->
    <text class="caption" x="290" y="104">A0 READS</text>
    <text class="reading" x="290" y="150">{{ reading }}</text>
    <text class="gloss" x="290" y="176">{{ gloss }}</text>

    <!-- 10 kΩ pull-down and GND -->
    <g class="layer" :class="{ on: fixed }">
      <rect class="part" x="76" y="240" width="28" height="80" />
      <text class="label" x="120" y="276">10 kΩ</text>
      <text class="gloss" x="120" y="296">pull-down</text>
      <rect class="part" x="40" y="346" width="100" height="40" />
      <text class="label" x="90" y="371" text-anchor="middle">GND</text>
    </g>
  </svg>
</template>

<style scoped>
.ldr { width: 100%; max-height: 21rem; display: block; }

.wire  { fill: none; stroke: var(--ink); stroke-width: 2.5; }
.knockout { fill: var(--paper); }
.terminal { fill: var(--paper); stroke: var(--ink); stroke-width: 2; }
.part  { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.pin   { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.zigzag { fill: none; stroke: var(--ink); stroke-width: 1.5; }
.ray   { fill: none; stroke: var(--ink); stroke-width: 1.8; }
.dot, .ink-fill { fill: var(--ink); }
.light { transition: opacity 0.4s ease; }

.flow { fill: none; stroke: var(--signal); stroke-width: 2.5; }
.signal-fill { fill: var(--signal); }

.label {
  font-family: var(--font-mono);
  font-size: 15px;
  letter-spacing: 0.06em;
  fill: var(--ink);
}
.caption {
  font-family: var(--font-mono);
  font-size: 12px;
  letter-spacing: 0.08em;
  fill: var(--ink-muted);
}
.reading {
  font-family: var(--font-mono);
  font-size: 40px;
  font-weight: 500;
  fill: var(--ink);
}
.gloss {
  font-family: var(--font-sans);
  font-size: 14px;
  fill: var(--ink-muted);
}

.layer { opacity: 0; transition: opacity 0.3s ease; }
.layer.on { opacity: 1; }
</style>

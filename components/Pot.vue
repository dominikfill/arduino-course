<script setup lang="ts">
// A potentiometer as a voltage divider: the middle leg (wiper) slides
// along the resistive track between 5 V and GND and picks a voltage.
//
//   <Pot :value="0.5" />                                  knob in the middle
//   <Pot :value="[0.15, 0.5, 0.9][$clicks] ?? 0.9" />     turn it with clicks
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  value?: number   // knob position: 0 = GND end, 1 = 5 V end
}>(), {
  value: 0.5,
})

const v = computed(() => Math.min(1, Math.max(0, props.value)))
// track runs from y=300 (GND end) to y=100 (5 V end)
const y = computed(() => 300 - v.value * 200)
const reading = computed(() => Math.round(v.value * 1023))
const volts = computed(() => (v.value * 5).toFixed(1))
// from the wiper down to A0
const toA0 = computed(() => `M250 ${y.value}V300`)
</script>

<template>
  <svg class="pot" viewBox="0 0 440 400" role="img"
       aria-label="Potentiometer between 5 V and GND, middle leg to A0">
    <!-- 5 V → track → GND -->
    <path class="wire" d="M90 84V100M90 300V336" />

    <!-- 5 V -->
    <rect class="part" x="40" y="44" width="100" height="40" />
    <text class="label" x="90" y="69" text-anchor="middle">5 V</text>

    <!-- resistive track -->
    <rect class="part" x="76" y="100" width="28" height="200" />
    <text class="caption" x="22" y="205" transform="rotate(-90 22 205)" text-anchor="middle">TRACK</text>

    <!-- wiper: middle leg, slides along the track -->
    <g class="wiper" :style="{ transform: `translateY(${y - 200}px)` }">
      <path class="wire" d="M112 200H250" />
      <path class="ink-fill" d="M106 200L120 192V208Z" />
      <circle class="dot" cx="250" cy="200" r="4" />
      <text class="caption" x="130" y="190">MIDDLE LEG</text>
    </g>

    <!-- A0 -->
    <path class="wire to-a0" :d="toA0" />
    <rect class="pin" x="240" y="300" width="20" height="20" />
    <text class="label" x="272" y="316">A0</text>

    <!-- reading -->
    <text class="caption" x="290" y="150">A0 READS</text>
    <text class="reading" x="290" y="196">{{ reading }}</text>
    <text class="gloss" x="290" y="222">≈ {{ volts }} V</text>

    <!-- GND -->
    <rect class="part" x="40" y="336" width="100" height="40" />
    <text class="label" x="90" y="361" text-anchor="middle">GND</text>
  </svg>
</template>

<style scoped>
.pot { width: 100%; max-height: 21rem; display: block; }

.wire  { fill: none; stroke: var(--ink); stroke-width: 2.5; }
.part  { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.pin   { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.dot, .ink-fill { fill: var(--ink); }

.wiper { transition: transform 0.4s ease; }
.to-a0 { transition: d 0.4s ease; }

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
</style>

<script setup lang="ts">
// The HC-SR04, drawn: a click of ultrasound goes out, bounces off a surface,
// comes back. The time tells the distance.
//
//   <Sonar :distance="30" :step="$clicks" />
//   step 0: sensor and surface · 1: click goes out · 2: echo comes back · 3: the numbers
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  distance?: number   // cm, 5 … 100
  step?: number
}>(), {
  distance: 30,
  step: 3,
})

const d = computed(() => Math.min(100, Math.max(5, props.distance)))
const wallX = computed(() => 120 + d.value * 3)
// there and back at 0.0343 cm per microsecond
const micros = computed(() => Math.round((2 * d.value) / 0.0343))
</script>

<template>
  <svg class="sonar" viewBox="0 0 460 230" role="img" aria-label="Ultrasound goes out, bounces back; the time gives the distance">
    <!-- sensor -->
    <rect class="part" x="20" y="60" width="80" height="80" />
    <circle class="eye" cx="60" cy="82" r="14" />
    <circle class="eye" cx="60" cy="118" r="14" />
    <text class="caption" x="60" y="160" text-anchor="middle">HC-SR04</text>

    <!-- surface -->
    <g class="wall" :style="{ transform: `translateX(${wallX - 420}px)` }">
      <path class="surface" d="M420 62V160" />
      <path class="hatch" d="M420 78l12 -8M420 98l12 -8M420 118l12 -8M420 138l12 -8M420 158l12 -8" />
    </g>

    <!-- click out -->
    <g class="layer" :class="{ on: step >= 1 }">
      <path class="sound" :d="`M78 82H${wallX - 8}`" />
      <path class="ink-fill" :d="`M${wallX - 4} 82l-12 -6v12Z`" />
      <text class="gloss" x="110" y="72">click</text>
    </g>

    <!-- echo back -->
    <g class="layer" :class="{ on: step >= 2 }">
      <path class="sound" :d="`M${wallX - 4} 118H86`" />
      <path class="ink-fill" d="M80 118l12 -6v12Z" />
      <text class="gloss" x="110" y="138">echo</text>
    </g>

    <!-- distance dimension, like on a drawing -->
    <g class="layer" :class="{ on: step >= 3 }">
      <path class="dim" :d="`M100 196H${wallX}M100 189V203M${wallX} 189V203`" />
      <text class="label" :x="(100 + wallX) / 2" y="190" text-anchor="middle">{{ d }} cm</text>
    </g>

    <!-- time -->
    <g class="layer" :class="{ on: step >= 2 }">
      <text class="caption" x="250" y="24">ECHO AFTER</text>
      <text class="reading" x="250" y="50">{{ micros }} µs</text>
    </g>
  </svg>
</template>

<style scoped>
.sonar { width: 100%; display: block; }

.part  { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.eye   { fill: var(--paper-deep); stroke: var(--ink); stroke-width: 2; }
.surface { fill: none; stroke: var(--ink); stroke-width: 3; }
.hatch { fill: none; stroke: var(--ink); stroke-width: 1.2; }
.wall  { transition: transform 0.4s ease; }

.sound { fill: none; stroke: var(--ink); stroke-width: 2; stroke-dasharray: 2 6; stroke-linecap: round; }
.ink-fill { fill: var(--ink); }
.dim   { fill: none; stroke: var(--ink-muted); stroke-width: 1.2; }

.label {
  font-family: var(--font-mono);
  font-size: 15px;
  letter-spacing: 0.04em;
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
  font-size: 24px;
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

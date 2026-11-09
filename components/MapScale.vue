<script setup lang="ts">
// map(), drawn as two scale bars: one range laid onto another.
//
//   <MapScale :from="[100, 900]" :to="[255, 0]" :value="700"
//             top="LIGHT · analogRead" bottom="BRIGHTNESS · analogWrite" />
//   <MapScale :from="[0, 50]" :to="[0.5, 1]" :decimals="2" :value="25" />
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  from?: [number, number]
  to?: [number, number]
  value?: number
  top?: string
  bottom?: string
  decimals?: number   // decimals for the mapped value
}>(), {
  from: () => [0, 1023],
  to: () => [0, 255],
  value: 512,
  top: 'FROM',
  bottom: 'TO',
  decimals: 0,
})

const X0 = 40
const X1 = 400
const YT = 50     // top bar
const YB = 150    // bottom bar

const t = computed(() => {
  const [a, b] = props.from
  return Math.min(1, Math.max(0, (props.value - a) / (b - a)))
})
const x = computed(() => X0 + t.value * (X1 - X0))
const mapped = computed(() => {
  const [c, d] = props.to
  return (c + t.value * (d - c)).toFixed(props.decimals)
})
const ticks = [0, 0.25, 0.5, 0.75, 1].map(f => X0 + f * (X1 - X0))
</script>

<template>
  <svg class="map" viewBox="0 -6 440 206" role="img" aria-label="map(): one range laid onto another">
    <!-- captions -->
    <text class="caption" :x="X0" :y="YT - 36">{{ top }}</text>
    <text class="caption" :x="X0" :y="YB + 42">{{ bottom }}</text>

    <!-- corresponding ticks -->
    <path v-for="tx in ticks" :key="tx" class="tie" :d="`M${tx} ${YT}V${YB}`" />

    <!-- scale bars -->
    <path class="bar" :d="`M${X0} ${YT}H${X1}M${X0} ${YB}H${X1}`" />
    <path class="tick" :d="ticks.map(tx => `M${tx} ${YT - 6}V${YT + 6}M${tx} ${YB - 6}V${YB + 6}`).join('')" />

    <!-- range ends -->
    <text class="end" :x="X0" :y="YT - 12" text-anchor="middle">{{ from[0] }}</text>
    <text class="end" :x="X1" :y="YT - 12" text-anchor="middle">{{ from[1] }}</text>
    <text class="end" :x="X0" :y="YB + 24" text-anchor="middle">{{ to[0] }}</text>
    <text class="end" :x="X1" :y="YB + 24" text-anchor="middle">{{ to[1] }}</text>

    <!-- the value, carried across -->
    <g class="value" :style="{ transform: `translateX(${x - X0}px)` }">
      <path class="flow" :d="`M${X0} ${YT}V${YB}`" />
      <circle class="mark" :cx="X0" :cy="YT" r="6" />
      <circle class="mark" :cx="X0" :cy="YB" r="6" />
      <text class="val" :x="X0 + 10" :y="YT + 30">{{ value }}</text>
      <text class="val" :x="X0 + 10" :y="YB - 14">{{ mapped }}</text>
    </g>
  </svg>
</template>

<style scoped>
.map { width: 100%; display: block; }

.bar  { fill: none; stroke: var(--ink); stroke-width: 2.5; }
.tick { fill: none; stroke: var(--ink); stroke-width: 2; }
.tie  { fill: none; stroke: var(--rule-faint); stroke-width: 1; stroke-dasharray: 4 4; }

.flow { fill: none; stroke: var(--signal); stroke-width: 3; }
.mark { fill: var(--signal); }
.value { transition: transform 0.4s ease; }

.caption {
  font-family: var(--font-mono);
  font-size: 12px;
  letter-spacing: 0.08em;
  fill: var(--ink-muted);
}
.end {
  font-family: var(--font-mono);
  font-size: 15px;
  fill: var(--ink);
}
.val {
  font-family: var(--font-mono);
  font-size: 20px;
  font-weight: 500;
  fill: var(--signal);
}
</style>

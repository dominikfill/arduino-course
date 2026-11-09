<script setup lang="ts">
// An on/off rhythm over time, drawn to scale like a timing diagram.
// Same conventions as Signal: ink waveform, blue = on-time.
//
//   <Rhythm />                                   the heartbeat, all shown
//   <Rhythm :step="$clicks" />                   segment by segment (1 … n),
//                                                then n + 1: one loop, and again
//   <Rhythm :pattern="[[1, 500], [0, 500]]" />   any rhythm: [on 1 / off 0, ms]
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  pattern?: [number, number][]
  step?: number
}>(), {
  pattern: () => [[1, 100], [0, 120], [1, 150], [0, 800]],
  step: 99,
})

const X0 = 60          // time axis starts
const X1 = 440         // time axis ends
const HI = 56          // y of HIGH
const LO = 116         // y of LOW

const n = computed(() => props.pattern.length)
const cycle = computed(() => props.pattern.reduce((s, [, ms]) => s + ms, 0))
// one full loop plus the start of the next one
const scale = computed(() => (X1 - X0) / (cycle.value * 1.3))
const loopEnd = computed(() => X0 + cycle.value * scale.value)

// segments of two loops, cut off at the end of the axis
const segs = computed(() => {
  const out: { on: boolean, ms: number, a: number, b: number, again: boolean, i: number }[] = []
  let t = 0
  for (let c = 0; c < 2; c++) {
    props.pattern.forEach(([on, ms], i) => {
      const a = X0 + t * scale.value
      t += ms
      if (a >= X1) return
      out.push({ on: !!on, ms, a, b: Math.min(X1, X0 + t * scale.value), again: c === 1, i })
    })
  }
  return out
})

const shown = (s: { again: boolean, i: number }) =>
  s.again ? props.step > n.value : props.step > s.i

const y = (on: boolean) => (on ? HI : LO)

// waveform of the first loop, and of the next one
function line(again: boolean) {
  const list = segs.value.filter(s => s.again === again && shown(s))
  if (!list.length) return ''
  let d = `M${list[0].a} ${again ? y(segs.value[n.value - 1].on) : y(list[0].on)}`
  for (const s of list) d += `V${y(s.on)}H${s.b}`
  return d
}

const fills = computed(() => segs.value
  .filter(s => s.on && shown(s))
  .map(s => `M${s.a} ${HI}H${s.b}V${LO}H${s.a}Z`)
  .join(''))
</script>

<template>
  <svg class="rhythm" viewBox="0 0 460 180" role="img"
       aria-label="The rhythm as a timing diagram: on and off over time, drawn to scale">
    <!-- HIGH and LOW levels -->
    <path class="level" :d="`M${X0} ${HI}H${X1}M${X0} ${LO}H${X1}`" />
    <text class="caption" :x="X0 - 8" :y="HI + 4" text-anchor="end">HIGH</text>
    <text class="caption" :x="X0 - 8" :y="LO + 4" text-anchor="end">LOW</text>

    <!-- time axis -->
    <path class="axis" :d="`M${X0} ${LO + 36}H${X1}`" />
    <path class="axis-head" :d="`M${X1} ${LO + 36}l-7 -4v8Z`" />
    <text class="caption" :x="X1" :y="LO + 54" text-anchor="end">time</text>

    <!-- on-time and waveform -->
    <path class="on" :d="fills" />
    <path class="wave" :d="line(false)" />
    <path class="wave again" :d="line(true)" />

    <!-- the delay of each segment: on-times above, off-times below -->
    <template v-for="s in segs" :key="`${s.again}-${s.i}`">
      <text v-if="!s.again && shown(s)" class="ms" :x="(s.a + s.b) / 2"
            :y="s.on ? HI - 8 : LO + 20" text-anchor="middle">{{ s.ms }}</text>
    </template>

    <!-- one loop, dimensioned like on a drawing -->
    <g v-if="step > n">
      <path class="dim" :d="`M${X0} 18H${loopEnd}M${X0} 12V24M${loopEnd} 12V24`" />
      <text class="caption" :x="(X0 + loopEnd) / 2" y="12" text-anchor="middle">ONE LOOP · {{ cycle }} MS</text>
      <text class="gloss" :x="loopEnd + 6" :y="HI - 8">again …</text>
    </g>
  </svg>
</template>

<style scoped>
.rhythm { width: 100%; display: block; }

.level { fill: none; stroke: var(--rule-faint); stroke-width: 1; stroke-dasharray: 4 4; }
.axis  { fill: none; stroke: var(--ink-muted); stroke-width: 1.2; }
.axis-head { fill: var(--ink-muted); }
.dim   { fill: none; stroke: var(--ink-muted); stroke-width: 1.2; }

.wave  { fill: none; stroke: var(--ink); stroke-width: 2.5; stroke-linejoin: round; }
.wave.again { stroke: var(--ink-muted); }
.on    { fill: var(--signal); opacity: 0.2; }

.ms {
  font-family: var(--font-mono);
  font-size: 16px;
  font-weight: 500;
  fill: var(--ink);
}
.caption {
  font-family: var(--font-mono);
  font-size: 12px;
  letter-spacing: 0.08em;
  fill: var(--ink-muted);
}
.gloss {
  font-family: var(--font-sans);
  font-size: 14px;
  fill: var(--ink-muted);
}
</style>

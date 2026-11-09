<script setup lang="ts">
// A signal over time, between 0 V and 5 V.
//
//   <Signal type="digital" />                         on / off, slow
//   <Signal type="analog" />                          any value in between
//   <Signal type="pwm" :duty="60 / 255" />            fast on / off, share of on-time
//   <Signal type="pwm" :duty="[1, 0.5, 0.1][$clicks]" />
//
// Blue fill = the time the pin is on (current can flow).
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  type?: 'digital' | 'analog' | 'pwm'
  duty?: number        // pwm only: 0 … 1, share of on-time
  label?: boolean      // show the % readout (pwm)
}>(), {
  type: 'pwm',
  duty: 0.5,
  label: true,
})

const X0 = 40          // time axis starts
const X1 = 340         // time axis ends
const HI = 30          // y of 5 V
const LO = 110         // y of 0 V

const d = computed(() => Math.min(1, Math.max(0, props.duty)))

// the waveform as a path, and the "on" areas to fill
const shape = computed(() => {
  const W = X1 - X0
  if (props.type === 'analog') {
    const pts: string[] = []
    for (let i = 0; i <= 60; i++) {
      const x = X0 + (W * i) / 60
      const y = (HI + LO) / 2 - 32 * Math.sin((i / 60) * Math.PI * 2 * 1.25) - 8 * Math.sin((i / 60) * Math.PI * 6)
      pts.push(`${i ? 'L' : 'M'}${x.toFixed(1)} ${y.toFixed(1)}`)
    }
    return { line: pts.join(''), fill: '' }
  }
  // digital: 2 slow periods, 50 %; pwm: 6 fast periods at the given duty
  const periods = props.type === 'digital' ? 2 : 6
  const duty = props.type === 'digital' ? 0.5 : d.value
  const P = W / periods
  let line = `M${X0} ${duty > 0 ? HI : LO}`
  let fill = ''
  for (let k = 0; k < periods; k++) {
    const a = X0 + k * P
    const b = a + P * duty
    const c = a + P
    if (duty >= 1) {
      line += `H${c}`
      fill += `M${a} ${HI}H${c}V${LO}H${a}Z`
    }
    else if (duty <= 0) {
      line += `H${c}`
    }
    else {
      line += `V${HI}H${b}V${LO}H${c}`
      fill += `M${a} ${HI}H${b}V${LO}H${a}Z`
    }
  }
  return { line, fill }
})

const percent = computed(() => `${Math.round(d.value * 100)} %`)
</script>

<template>
  <svg class="signal" viewBox="0 0 460 150" role="img" :aria-label="`${type} signal`">
    <!-- 5 V and 0 V levels -->
    <path class="level" :d="`M${X0} ${HI}H${X1}M${X0} ${LO}H${X1}`" />
    <text class="caption" :x="X0 - 8" :y="HI + 4" text-anchor="end">5 V</text>
    <text class="caption" :x="X0 - 8" :y="LO + 4" text-anchor="end">0 V</text>

    <!-- time axis -->
    <path class="axis" :d="`M${X0} ${LO + 14}H${X1}`" />
    <path class="axis-head" :d="`M${X1} ${LO + 14}l-7 -4v8Z`" />
    <text class="caption" :x="X1" :y="LO + 32" text-anchor="end">time</text>

    <!-- on-time and waveform -->
    <path v-if="shape.fill" class="on" :d="shape.fill" />
    <path class="wave" :d="shape.line" />

    <!-- readout -->
    <g v-if="type === 'pwm' && label">
      <text class="caption" x="356" y="56">ON</text>
      <text class="reading" x="356" y="86">{{ percent }}</text>
    </g>
  </svg>
</template>

<style scoped>
.signal { width: 100%; display: block; }

.level { fill: none; stroke: var(--rule-faint); stroke-width: 1; stroke-dasharray: 4 4; }
.axis  { fill: none; stroke: var(--ink-muted); stroke-width: 1.2; }
.axis-head { fill: var(--ink-muted); }

.wave { fill: none; stroke: var(--ink); stroke-width: 2.5; stroke-linejoin: round; transition: d 0.4s ease; }
.on   { fill: var(--signal); opacity: 0.2; transition: d 0.4s ease; }

.caption {
  font-family: var(--font-mono);
  font-size: 12px;
  letter-spacing: 0.08em;
  fill: var(--ink-muted);
}
.reading {
  font-family: var(--font-mono);
  font-size: 28px;
  font-weight: 500;
  fill: var(--ink);
}
</style>

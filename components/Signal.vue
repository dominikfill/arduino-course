<script setup lang="ts">
// A signal over time, between 0 V and 5 V.
//
//   <Signal type="digital" />                         on / off, slow
//   <Signal type="analog" />                          any value in between
//   <Signal type="pwm" :duty="60 / 255" />            fast on / off, share of on-time
//   <Signal type="pwm" :duty="[1, 0.5, 0.1][$clicks]" />
//   <Signal type="digital" compact />                 narrow columns: no readout, cropped
//   <Signal type="pwm" compact :steps="[0.25, 0.5, 0.75]" />   several duties stacked
//
// Blue fill = the time the pin is on (current can flow).
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  type?: 'digital' | 'analog' | 'pwm'
  duty?: number        // pwm only: 0 … 1, share of on-time
  label?: boolean      // show the % readout (pwm)
  compact?: boolean    // for narrow columns (recap): no readout, cropped width
  steps?: number[]     // pwm only: draw one row per duty, stacked, each with its %
}>(), {
  type: 'pwm',
  duty: 0.5,
  label: true,
  compact: false,
})

const X0 = 40          // time axis starts
const X1 = 340         // time axis ends
const HI = 30          // y of 5 V
const LO = 110         // y of 0 V

const clamp = (n: number) => Math.min(1, Math.max(0, n))
const d = computed(() => clamp(props.duty))

// one waveform as a path, plus the "on" areas to fill
function wave(type: string, duty: number, x0: number, x1: number, hi: number, lo: number) {
  const W = x1 - x0
  if (type === 'analog') {
    const pts: string[] = []
    const mid = (hi + lo) / 2
    const amp = (lo - hi) / 80
    for (let i = 0; i <= 60; i++) {
      const x = x0 + (W * i) / 60
      const y = mid - amp * (32 * Math.sin((i / 60) * Math.PI * 2 * 1.25) + 8 * Math.sin((i / 60) * Math.PI * 6))
      pts.push(`${i ? 'L' : 'M'}${x.toFixed(1)} ${y.toFixed(1)}`)
    }
    return { line: pts.join(''), fill: '' }
  }
  // digital: 2 slow periods, 50 %; pwm: 6 fast periods at the given duty
  const periods = type === 'digital' ? 2 : 6
  const dt = type === 'digital' ? 0.5 : duty
  const P = W / periods
  let line = `M${x0} ${dt > 0 ? hi : lo}`
  let fill = ''
  for (let k = 0; k < periods; k++) {
    const a = x0 + k * P
    const b = a + P * dt
    const c = a + P
    if (dt >= 1) {
      line += `H${c}`
      fill += `M${a} ${hi}H${c}V${lo}H${a}Z`
    }
    else if (dt <= 0) {
      line += `H${c}`
    }
    else {
      line += `V${hi}H${b}V${lo}H${c}`
      fill += `M${a} ${hi}H${b}V${lo}H${a}Z`
    }
  }
  return { line, fill }
}

const shape = computed(() => wave(props.type, d.value, X0, X1, HI, LO))
const percent = computed(() => `${Math.round(d.value * 100)} %`)

// stacked rows (steps): each row 56 high, wave 36 high, time axis below the last row
const ROW = 56
const rows = computed(() => (props.steps ?? []).map((s, i) => {
  const hi = 14 + i * ROW
  const lo = hi + 36
  return { ...wave('pwm', clamp(s), X0, 290, hi, lo), hi, lo, pct: `${Math.round(clamp(s) * 100)} %` }
}))
const stackedHeight = computed(() => 14 + rows.value.length * ROW + 30)
const stackedAxis = computed(() => 14 + rows.value.length * ROW)

const viewBox = computed(() => {
  if (rows.value.length) return `0 0 360 ${stackedHeight.value}`
  return props.compact ? '0 0 360 150' : '0 0 460 150'
})
</script>

<template>
  <!-- stacked: several PWM duties, one row each -->
  <svg v-if="rows.length" class="signal" :viewBox="viewBox" role="img" aria-label="pwm signals at several duties">
    <g v-for="(r, i) in rows" :key="i">
      <path class="level" :d="`M${X0} ${r.hi}H290M${X0} ${r.lo}H290`" />
      <template v-if="i === 0">
        <text class="caption" :x="X0 - 8" :y="r.hi + 4" text-anchor="end">5 V</text>
        <text class="caption" :x="X0 - 8" :y="r.lo + 4" text-anchor="end">0 V</text>
      </template>
      <path v-if="r.fill" class="on" :d="r.fill" />
      <path class="wave" :d="r.line" />
      <text class="pct" x="302" :y="(r.hi + r.lo) / 2 + 6">{{ r.pct }}</text>
    </g>
    <path class="axis" :d="`M${X0} ${stackedAxis}H290`" />
    <path class="axis-head" :d="`M290 ${stackedAxis}l-7 -4v8Z`" />
    <text class="caption" x="290" :y="stackedAxis + 18" text-anchor="end">time</text>
  </svg>

  <!-- single signal -->
  <svg v-else class="signal" :viewBox="viewBox" role="img" :aria-label="`${type} signal`">
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
    <g v-if="type === 'pwm' && label && !compact">
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
.pct {
  font-family: var(--font-mono);
  font-size: 16px;
  font-weight: 500;
  fill: var(--ink);
}
</style>

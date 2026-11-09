<script setup lang="ts">
// A breadboard close-up, drawn in the course style.
// Blue (--signal) marks holes that are connected.
//
//   <Breadboard rail :top="10" :bottom="10" labels />    how it's connected
//   <Breadboard led />                                    LED legs in A5 and B5
//   <Breadboard led :bottom="5" />                        ...and why it won't light
//   <Breadboard rail :top="10" :bottom="10" labels :step="$clicks" />
//        build-up: 0 bare · 1 bottom strip · 2 gap + top strip · 3 rail
import { computed } from 'vue'

const props = defineProps<{
  rail?: boolean     // highlight the + rail
  top?: number       // highlight the F–J strip in this column
  bottom?: number    // highlight the A–E strip in this column
  labels?: boolean   // annotations on the right
  led?: boolean      // an LED with both legs in A5 and B5
  step?: number      // optional build-up (see above); without it, everything shows
}>()

// what is shown at the current step (no step: everything that was asked for)
const at = (n: number) => props.step === undefined || props.step >= n
const railOn = computed(() => props.rail && at(3))
const topCol = computed(() => (at(2) ? props.top : undefined))
const bottomCol = computed(() => (at(1) ? props.bottom : undefined))

const cols = Array.from({ length: 12 }, (_, i) => i + 1)
const x = (c: number) => 40 + (c - 1) * 28
const railCols = cols.filter(c => c % 6 !== 0)   // rails come in groups of 5

const topRows = [['J', 104], ['I', 126], ['H', 148], ['G', 170], ['F', 192]] as const
const bottomRows = [['E', 232], ['D', 254], ['C', 276], ['B', 298], ['A', 320]] as const

const isOn = (c: number, half: 'top' | 'bottom') =>
  (half === 'top' && topCol.value === c) || (half === 'bottom' && bottomCol.value === c)

const labelCol = computed(() => props.top ?? props.bottom ?? 10)
</script>

<template>
  <svg class="bb" viewBox="0 0 650 360" role="img" aria-label="Breadboard close-up">
    <!-- board -->
    <rect class="board" x="10" y="10" width="380" height="340" />
    <rect class="channel" x="10" y="205" width="380" height="14" />

    <!-- power rails -->
    <text class="sign" x="22" y="39" text-anchor="middle">−</text>
    <text class="sign" x="22" y="61" text-anchor="middle">+</text>
    <rect v-for="c in railCols" :key="'m' + c" class="hole" :x="x(c) - 3.5" y="30.5" width="7" height="7" />
    <rect v-for="c in railCols" :key="'p' + c" class="hole" :class="{ on: railOn }" :x="x(c) - 3.5" y="52.5" width="7" height="7" />
    <rect v-if="railOn" class="outline" x="28" y="44" width="304" height="24" rx="12" />

    <!-- column numbers -->
    <text v-for="c in [1, 5, 10]" :key="'n' + c" class="num" :x="x(c)" y="88" text-anchor="middle">{{ c }}</text>

    <!-- terminal strips -->
    <template v-for="[r, y] in topRows" :key="r">
      <text class="row" x="22" :y="y + 4" text-anchor="middle">{{ r }}</text>
      <rect v-for="c in cols" :key="r + c" class="hole" :class="{ on: isOn(c, 'top') }"
            :x="x(c) - 3.5" :y="y - 3.5" width="7" height="7" />
    </template>
    <template v-for="[r, y] in bottomRows" :key="r">
      <text class="row" x="22" :y="y + 4" text-anchor="middle">{{ r }}</text>
      <rect v-for="c in cols" :key="r + c" class="hole" :class="{ on: isOn(c, 'bottom') }"
            :x="x(c) - 3.5" :y="y - 3.5" width="7" height="7" />
    </template>
    <rect v-if="topCol" class="outline" :x="x(topCol) - 12" y="92" width="24" height="112" rx="12" />
    <rect v-if="bottomCol" class="outline" :x="x(bottomCol) - 12" y="220" width="24" height="112" rx="12" />

    <!-- LED: legs in A5 and B5 -->
    <g v-if="led">
      <path class="leg" d="M152 320L190 314M152 298L190 304" />
      <circle class="dot" cx="152" cy="320" r="3" />
      <circle class="dot" cx="152" cy="298" r="3" />
      <circle class="led" cx="202" cy="309" r="13" />
      <text class="row" x="202" y="343" text-anchor="middle">LED</text>
    </g>

    <!-- annotations -->
    <g v-if="labels">
      <g v-if="at(3)">
        <path class="lead" d="M332 56H410" />
        <text class="label" x="420" y="52">POWER RAIL</text>
        <text class="gloss" x="420" y="72">connected along its length</text>
      </g>

      <g v-if="at(2)">
        <path class="lead" :d="`M${x(labelCol) + 12} 148H410`" />
        <text class="label" x="420" y="144">5 HOLES</text>
        <text class="gloss" x="420" y="164">connected (F–J)</text>

        <path class="lead" :d="`M${x(labelCol)} 212H410`" />
        <circle class="end" :cx="x(labelCol)" cy="212" r="4" />
        <text class="label" x="420" y="208">GAP</text>
        <text class="gloss" x="420" y="228">not connected</text>
      </g>

      <g v-if="at(1)">
        <path class="lead" :d="`M${x(labelCol) + 12} 276H410`" />
        <text class="label" x="420" y="272">5 HOLES</text>
        <text class="gloss" x="420" y="292">connected (A–E)</text>
      </g>
    </g>
  </svg>
</template>

<style scoped>
.bb { width: 100%; height: 100%; display: block; }

.board   { fill: var(--paper-deep); stroke: var(--ink); stroke-width: 2; }
.channel { fill: var(--paper); }
.hole    { fill: var(--ink-muted); }
.hole.on { fill: var(--signal); }
.outline { fill: none; stroke: var(--signal); stroke-width: 3; }

.leg  { fill: none; stroke: var(--ink); stroke-width: 2.5; stroke-linecap: round; }
.dot  { fill: var(--ink); }
.led  { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }

.lead { fill: none; stroke: var(--ink); stroke-width: 1.5; }
.end  { fill: var(--ink); }

.sign, .row, .num {
  font-family: var(--font-mono);
  font-size: 13px;
  fill: var(--ink-muted);
}
.sign { font-size: 18px; fill: var(--ink); }

.label {
  font-family: var(--font-mono);
  font-size: 17px;
  letter-spacing: 0.06em;
  fill: var(--ink);
}
.gloss {
  font-family: var(--font-sans);
  font-size: 16px;
  fill: var(--ink-muted);
}
</style>

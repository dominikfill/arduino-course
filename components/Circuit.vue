<script setup lang="ts">
import { computed } from 'vue'
// One LED circuit, drawn in the course style. Layers switch on via props,
// so one drawing serves every electricity slide.
//
//   <Circuit current />                              loop with current flowing
//   <Circuit current gap />                          broken loop (current off)
//   <Circuit :voltage="$clicks >= 1" :current="$clicks >= 2" :resistance="$clicks >= 3" />
//   <Circuit current high :resistor="false" />       no resistor: too much current
//   <Circuit current button :pressed="$clicks >= 1" /> a push button in the loop
//
// Ink = parts and wires · blue (--signal) = current, the only colour in diagrams.
const props = withDefaults(defineProps<{
  voltage?: boolean      // show the voltage arrow between PIN and GND
  current?: boolean      // show current flowing around the loop
  resistance?: boolean   // label the resistor
  resistor?: boolean     // draw the resistor at all
  gap?: boolean          // break the loop (a loose wire)
  high?: boolean         // thick current line: too much current
  button?: boolean       // a push button in the bottom wire
  pressed?: boolean      // ...and whether it is pressed (closes the loop)
  ohms?: string          // resistor value label
}>(), {
  resistor: true,
  ohms: '470 Ω',
})

// current flows only through a closed loop
const flowing = computed(() =>
  props.current && !props.gap && (!props.button || props.pressed),
)
</script>

<template>
  <svg class="circuit" viewBox="0 0 520 320" role="img"
       aria-label="LED circuit: pin, LED, resistor, back to GND">
    <!-- wire -->
    <path class="wire" d="M140 70H360V250H140" />

    <!-- current: blue line along the wire, under the parts -->
    <g class="layer" :class="{ on: flowing }">
      <path class="flow" :class="{ high }" d="M140 70H360V250H140" />
    </g>

    <!-- gap: a break in the bottom wire -->
    <g v-if="gap">
      <rect class="knockout" x="282" y="236" width="36" height="28" />
      <path class="wire" d="M282 242V258M318 242V258" />
    </g>

    <!-- push button: open lifts the contact, pressed closes the loop -->
    <g v-if="button">
      <rect class="knockout" x="276" y="226" width="48" height="34" />
      <path v-if="pressed" class="wire" d="M282 250H318" />
      <path v-else class="wire" d="M282 250L314 232" />
      <circle class="terminal" cx="282" cy="250" r="3.5" />
      <circle class="terminal" cx="318" cy="250" r="3.5" />
      <text class="label small" x="300" y="274" text-anchor="middle">BUTTON</text>
    </g>

    <!-- PIN and GND -->
    <rect class="part" x="30" y="44" width="110" height="52" />
    <rect class="part" x="30" y="224" width="110" height="52" />
    <text class="label" x="85" y="68" text-anchor="middle">PIN</text>
    <text class="gloss" x="85" y="87" text-anchor="middle">5 V</text>
    <text class="label" x="85" y="248" text-anchor="middle">GND</text>
    <text class="gloss" x="85" y="267" text-anchor="middle">0 V</text>

    <!-- LED -->
    <rect class="knockout" x="228" y="48" width="46" height="44" />
    <path class="part" d="M236 50V90L266 70Z" stroke-linejoin="round" />
    <path class="wire" d="M268 50V90" />
    <g class="layer" :class="{ on: flowing }">
      <path class="ray" d="M250 42l10-14M264 42l10-14" />
      <path class="ink-fill" d="M256 28l7-4-1 8ZM270 28l7-4-1 8Z" />
    </g>
    <text class="label small" x="251" y="116" text-anchor="middle">LED</text>

    <!-- resistor -->
    <rect v-if="resistor" class="part" x="346" y="120" width="28" height="70" />

    <!-- voltage -->
    <g class="layer" :class="{ on: voltage }">
      <path class="arrow-line" d="M85 106V214" />
      <path class="ink-fill" d="M78 114L85 100L92 114ZM78 206L85 220L92 206Z" />
      <text class="label" x="100" y="152">VOLTAGE</text>
      <text class="gloss" x="100" y="172">the push</text>
    </g>

    <!-- current arrows and label -->
    <g class="layer" :class="{ on: flowing }">
      <path v-if="!high" class="signal-fill"
            d="M182 62L198 70L182 78ZM352 214L360 230L368 214ZM256 242L240 250L256 258Z" />
      <text class="label signal" x="250" y="292" text-anchor="middle">CURRENT</text>
      <text class="gloss signal" x="250" y="312" text-anchor="middle">the flow</text>
    </g>

    <!-- resistance label -->
    <g v-if="resistor" class="layer" :class="{ on: resistance }">
      <text class="label" x="390" y="140">RESISTANCE</text>
      <text class="gloss strong" x="390" y="160">{{ ohms }}</text>
      <text class="gloss" x="390" y="180">the narrowing</text>
    </g>
  </svg>
</template>

<style scoped>
.circuit { width: 100%; height: auto; display: block; overflow: visible; }

.wire, .part, .arrow-line, .ray {
  fill: none;
  stroke: var(--ink);
  stroke-width: 2.5;
}
.part { fill: var(--paper); }
.arrow-line, .ray { stroke-width: 1.8; }
.knockout { fill: var(--paper); }
.ink-fill { fill: var(--ink); }
.terminal { fill: var(--paper); stroke: var(--ink); stroke-width: 2; }

.flow {
  fill: none;
  stroke: var(--signal);
  stroke-width: 4;
  stroke-linejoin: round;
}
.flow.high { stroke-width: 14; }
.signal-fill { fill: var(--signal); }

.label {
  font-family: var(--font-mono);
  font-size: 15px;
  letter-spacing: 0.06em;
  fill: var(--ink);
}
.label.small { font-size: 13px; }
.gloss {
  font-family: var(--font-sans);
  font-size: 14px;
  fill: var(--ink-muted);
}
.gloss.strong { fill: var(--ink); }
.signal { fill: var(--signal); }

/* layers fade in and out with clicks */
.layer { opacity: 0; transition: opacity 0.3s ease; }
.layer.on { opacity: 1; }
</style>

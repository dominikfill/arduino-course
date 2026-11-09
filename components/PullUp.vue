<script setup lang="ts">
// The button circuit on pin 2, with and without the built-in pull-up.
//
//   <PullUp :pullup="false" />                 not pressed, no pull-up: floating
//   <PullUp :pullup="false" pressed />         pressed: pin 2 connected to GND
//   <PullUp />                                 pull-up on, not pressed: HIGH
//   <PullUp pressed />                         pull-up on, pressed: LOW
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  pullup?: boolean     // INPUT_PULLUP: the resistor from 5 V to pin 2 is switched on
  pressed?: boolean    // the button connects pin 2 to GND
}>(), {
  pullup: true,
})

// what pin 2 measures
const reading = computed(() =>
  props.pressed ? 'LOW' : props.pullup ? 'HIGH' : '?',
)
const volts = computed(() =>
  props.pressed ? '0 V · connected to GND'
    : props.pullup ? '5 V · no current, no drop'
      : 'floating · not connected',
)
// current flows only from 5 V through the resistor and the button to GND
const flowing = computed(() => props.pullup && props.pressed)
</script>

<template>
  <svg class="pullup" viewBox="0 0 440 390" role="img"
       aria-label="Button between pin 2 and GND, with the built-in pull-up resistor to 5 V">
    <!-- the Arduino's inside -->
    <rect class="boundary" x="20" y="10" width="400" height="230" />
    <text class="caption" x="34" y="32">INSIDE THE ARDUINO</text>

    <!-- pin 2 → button → GND (always there) -->
    <path class="wire" d="M90 210V346" />

    <!-- pull-up: 5 V → resistor → pin 2, switched on by INPUT_PULLUP -->
    <g class="layer" :class="{ on: pullup }">
      <path class="wire" d="M90 84V210" />
    </g>

    <!-- current: only with pull-up and pressed -->
    <g class="layer" :class="{ on: flowing }">
      <path class="flow" d="M90 84V346" />
      <path class="signal-fill" d="M83 180L90 194L97 180ZM83 318L90 332L97 318Z" />
      <text class="gloss signal" x="150" y="372">a tiny current</text>
    </g>

    <!-- 5 V -->
    <rect class="part" x="40" y="44" width="100" height="40" />
    <text class="label" x="90" y="69" text-anchor="middle">5 V</text>

    <!-- pull-up resistor -->
    <g class="layer" :class="{ on: pullup }">
      <rect class="part" x="76" y="104" width="28" height="64" />
      <text class="label" x="120" y="130">PULL-UP</text>
      <text class="gloss" x="120" y="150">INPUT_PULLUP</text>
    </g>

    <!-- pin 2 -->
    <circle class="dot" cx="90" cy="210" r="4" />
    <rect class="pin" x="80" y="230" width="20" height="20" />
    <text class="label" x="120" y="258">PIN 2</text>

    <!-- what the pin reads -->
    <text class="caption" x="250" y="140">PIN 2 READS</text>
    <text class="reading" x="250" y="186">{{ reading }}</text>
    <text class="gloss" x="250" y="212">{{ volts }}</text>

    <!-- button -->
    <rect class="knockout" x="70" y="268" width="44" height="44" />
    <path v-if="pressed" class="wire" d="M90 276V308" />
    <path v-else class="wire" d="M90 276L110 304" />
    <circle class="terminal" cx="90" cy="276" r="3.5" />
    <circle class="terminal" cx="90" cy="308" r="3.5" />
    <text class="label" x="124" y="300">BUTTON</text>

    <!-- GND -->
    <rect class="part" x="40" y="346" width="100" height="40" />
    <text class="label" x="90" y="371" text-anchor="middle">GND</text>
  </svg>
</template>

<style scoped>
.pullup { width: 100%; max-height: 21rem; display: block; }

.boundary { fill: none; stroke: var(--ink-muted); stroke-width: 1.5; stroke-dasharray: 6 5; }
.wire  { fill: none; stroke: var(--ink); stroke-width: 2.5; }
.part  { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.pin   { fill: var(--paper); stroke: var(--ink); stroke-width: 2.5; }
.dot   { fill: var(--ink); }
.knockout { fill: var(--paper); }
.terminal { fill: var(--paper); stroke: var(--ink); stroke-width: 2; }

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
.signal { fill: var(--signal); }

.layer { opacity: 0; transition: opacity 0.3s ease; }
.layer.on { opacity: 1; }
</style>
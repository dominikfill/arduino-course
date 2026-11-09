<script setup lang="ts">
// The Arduino UNO R4 WiFi photo with ink annotations.
// Show only the labels a slide needs:
//
//   <Board />                                         usb, led, digital, power
//   <Board :show="['digital', 'pwm']" />              later: PWM pins
//   <Board :show="['analog', 'power']" />             later: sensors
//
// Labels: usb · led · digital · pwm · power · analog · barrel
import { computed } from 'vue'

const props = withDefaults(defineProps<{
  show?: string[]
}>(), {
  show: () => ['usb', 'led', 'digital', 'power'],
})

const has = (k: string) => props.show.includes(k)

// Crop the empty bottom margin when no bottom label is shown
const viewBox = computed(() =>
  ['barrel', 'power', 'analog'].some(has) ? '0 0 1050 1000' : '0 0 1050 915',
)

const pwmPins = [535, 567, 598, 712, 743, 807]
</script>

<template>
  <figure class="board">
    <svg :viewBox="viewBox" role="img" aria-label="Arduino UNO R4 WiFi, background removed, labels added">
      <image class="photo" x="20" y="150" width="1000" height="750"
             href="/images/arduino-uno-r4-wifi.webp" />

      <!-- top -->
      <g v-if="has('usb')">
        <path class="halo" d="M102 92V387H117" /><path class="lead" d="M102 92V387H117" />
        <circle class="dot" cx="117" cy="387" r="9" />
        <text class="label" x="102" y="74" text-anchor="middle">USB-C</text>
      </g>

      <g v-if="has('led')">
        <path class="halo" d="M442 92V335" /><path class="lead" d="M442 92V335" />
        <circle class="dot" cx="442" cy="335" r="9" />
        <text class="label" x="442" y="74" text-anchor="middle">L LED</text>
      </g>

      <g v-if="has('digital')">
        <path class="halo" d="M655 92V212" /><path class="lead" d="M655 92V212" />
        <circle class="dot" cx="655" cy="212" r="9" />
        <text class="label" x="800" y="74" text-anchor="middle">DIGITAL 0–13</text>
      </g>

      <g v-if="has('pwm')">
        <g v-for="x in pwmPins" :key="x">
          <circle class="tilde" :cx="x" cy="178" r="14" />
          <text class="tilde-text" :x="x" y="187" text-anchor="middle">~</text>
        </g>
        <text class="label" x="800" y="122" text-anchor="middle">~ = PWM</text>
      </g>

      <!-- bottom -->
      <g v-if="has('barrel')">
        <path class="halo" d="M170 790V912" /><path class="lead" d="M170 790V912" />
        <circle class="dot" cx="170" cy="790" r="9" />
        <text class="label" x="150" y="962" text-anchor="middle">BARREL JACK</text>
      </g>

      <g v-if="has('power')">
        <path class="halo" d="M555 846V868H648V846M602 868V912" />
        <path class="lead" d="M555 846V868H648V846M602 868V912" />
        <text class="label" x="500" y="962" text-anchor="middle">3.3V · 5V · GND</text>
      </g>

      <g v-if="has('analog')">
        <path class="halo" d="M743 846V868H902V846M822 868V912" />
        <path class="lead" d="M743 846V868H902V846M822 868V912" />
        <text class="label" x="885" y="962" text-anchor="middle">ANALOG A0–A5</text>
      </g>
    </svg>
    <figcaption>
      Photo: <a href="https://commons.wikimedia.org/wiki/File:Arduino_Uno_R4_WiFi.webp">Wikimedia Commons</a>,
      <a href="https://creativecommons.org/licenses/by-sa/3.0/">CC BY-SA 3.0</a> · background removed, labels added
    </figcaption>
  </figure>
</template>

<style scoped>
.board {
  margin: 0;
  display: flex;
  flex-direction: column;
  gap: 0.35rem;
}
/* the photo is nearly square: cap its height so title + photo + caption
   fit the slide (canvas is ~550px tall) */
svg { width: 100%; max-height: 21rem; }

/* the photo's light backdrop blends into the paper */
.photo { mix-blend-mode: multiply; }

/* leader lines: ink with a paper halo, so they read on the dark board */
.halo { fill: none; stroke: var(--paper); stroke-width: 10; stroke-linecap: round; stroke-linejoin: round; }
.lead { fill: none; stroke: var(--ink); stroke-width: 3.5; stroke-linecap: round; stroke-linejoin: round; }
.dot  { fill: var(--paper); stroke: var(--ink); stroke-width: 4; }

.label {
  font-family: var(--font-mono);
  font-size: 38px;
  letter-spacing: 0.06em;
  fill: var(--ink);
}

.tilde { fill: var(--paper); stroke: var(--ink); stroke-width: 3; }
.tilde-text { font-family: var(--font-mono); font-size: 26px; fill: var(--ink); }

figcaption {
  flex-shrink: 0;
  font-family: var(--font-mono);
  font-size: 0.7rem;
  color: var(--ink-muted);
}
figcaption a { color: inherit; }
</style>

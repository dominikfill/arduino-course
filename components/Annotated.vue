<script setup lang="ts">
// A screenshot with numbered ink markers, like callouts on a drawing.
// x and y are percentages of the image, so markers stay put when it scales.
// Place a marker beside the element it points to, not on top of it.
//
//   <Annotated src="/images/ide-toolbar.png" alt="Arduino IDE toolbar"
//              :marks="[{ n: 2, x: 40, y: 50 }, { n: 3, x: 12, y: 50 }]" />
//
// src must be an absolute path into public/ (see Figure.vue).
defineProps<{
  src: string
  alt?: string
  marks?: { n: number | string, x: number, y: number }[]
  credit?: string
}>()
</script>

<template>
  <figure class="annotated">
    <div class="frame">
      <img :src="src" :alt="alt ?? ''">
      <span v-for="m in marks" :key="m.n" class="mark"
            :style="{ left: `${m.x}%`, top: `${m.y}%` }">{{ m.n }}</span>
    </div>
    <figcaption v-if="credit">{{ credit }}</figcaption>
  </figure>
</template>

<style scoped>
.annotated {
  margin: 0;
  display: flex;
  flex-direction: column;
  gap: 0.35rem;
}

/* the frame shrinks to the image, so % positions refer to the image */
.frame {
  position: relative;
  align-self: flex-start;
  max-width: 100%;
}

/* screenshots stay as they are (no multiply): a screen is a screen.
   A faint rule separates the white UI from the paper. */
img {
  display: block;
  max-width: 100%;
  border: 1px solid var(--rule-faint);
}

/* ink callout: paper fill, ink ring, mono numeral. Never red: red means tasks. */
.mark {
  position: absolute;
  transform: translate(-50%, -50%);
  width: 1.7rem;
  height: 1.7rem;
  display: grid;
  place-items: center;
  border-radius: 50%;
  background: var(--paper);
  border: 2px solid var(--ink);
  font-family: var(--font-mono);
  font-size: 0.9rem;
  font-weight: 600;
  color: var(--ink);
}

figcaption {
  font-family: var(--font-mono);
  font-size: 0.7rem;
  color: var(--ink-muted);
}
</style>

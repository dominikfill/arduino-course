<script setup lang="ts">
// <Figure src="/circuits/ldr-divider.svg" alt="…" credit="Drawing: D. Fill" />
// <Figure src="/images/pavilion.jpg" photo credit="Photo: …" />
//
// src must be an absolute path into public/ (e.g. /circuits/x.svg):
// relative paths in component props break after build.
defineProps<{
  src: string
  alt?: string
  credit?: string
  photo?: boolean   // photos keep full colour (no multiply blending)
}>()
</script>

<template>
  <figure class="figure" :class="{ photo }">
    <img :src="src" :alt="alt ?? ''">
    <figcaption v-if="credit">{{ credit }}</figcaption>
  </figure>
</template>

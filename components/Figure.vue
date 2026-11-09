<script setup lang="ts">
// <Figure src="/circuits/ldr-divider.svg" alt="…" credit="Drawing: D. Fill" />
// <Figure src="/images/pavilion.jpg" photo credit="Photo: …" />
//
// src must be an absolute path into public/ (e.g. /circuits/x.svg):
// relative paths in component props break after build.
import { computed } from 'vue'

const props = defineProps<{
  src: string
  alt?: string
  credit?: string
  photo?: boolean   // photos keep full colour (no multiply blending)
}>()

// prefix the site's base path, so images also load when hosted in a subfolder (GitHub Pages)
const url = computed(() => import.meta.env.BASE_URL + props.src.replace(/^\//, ''))
</script>

<template>
  <figure class="figure" :class="{ photo }">
    <img :src="url" :alt="alt ?? ''">
    <figcaption v-if="credit">{{ credit }}</figcaption>
  </figure>
</template>

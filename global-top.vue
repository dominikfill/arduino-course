<script setup lang="ts">
import { computed } from 'vue'
import { useNav, useSlideContext } from '@slidev/client'


const { currentLayout, currentFrontmatter } = useNav()

// Deck title from the entry's headmatter (`title:`), via the typed composable
const { $slidev } = useSlideContext()
const deckTitle = computed(() => $slidev.configs.title)

// Layouts that carry their own composition and don't get a footer
const hiddenOn = ['cover', 'section', 'image', 'full', 'end']

// Also hide on any slide with `footer: false` in its frontmatter
const visible = computed(() =>
  !hiddenOn.includes(currentLayout.value)
  && currentFrontmatter.value?.footer !== false,
)
</script>

<template>
  <!-- Title block: reads the `title` from each entry's headmatter,
       so every session labels itself. -->
  <footer v-if="visible" class="title-block">
    <span class="title">{{ deckTitle }}</span>
    <span class="count"><SlideCurrentNo /> / <SlidesTotal /></span>
  </footer>
</template>

<style scoped>
.title-block {
  position: absolute;
  left: 3.5rem;
  right: 3.5rem;
  bottom: 1rem;
  z-index: 50;
  display: flex;
  justify-content: space-between;
  align-items: baseline;
  gap: 2rem;
  padding-top: 0.35rem;
  border-top: 1px solid var(--rule);
  font-family: var(--font-mono);
  font-size: 0.75rem;
  letter-spacing: 0.04em;
  text-transform: uppercase;
  color: var(--ink);
  pointer-events: none;
  user-select: none;
}

.title {
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
}

.count { flex-shrink: 0; }
</style>
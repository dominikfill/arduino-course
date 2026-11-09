import { defineShikiSetup } from '@slidev/types'

export default defineShikiSetup(() => {
  return {
    themes: {
      // The deck is light only (colorSchema: light), so only `light` is used.
      // High-contrast variant: holds up on a washed-out projector.
      light: 'github-light-high-contrast',
      dark: 'github-dark-high-contrast',
    },
  }
})

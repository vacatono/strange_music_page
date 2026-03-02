// @ts-check
import { defineConfig } from 'astro/config';

import react from '@astrojs/react';

// https://astro.build/config
export default defineConfig({
  site: 'https://vacatono.github.io',
  base: '/strange_music_page',
  integrations: [react()],
});

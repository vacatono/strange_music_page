import { defineCollection, z } from 'astro:content';
import { glob } from 'astro/loaders';

const livereports = defineCollection({
  loader: glob({ pattern: '**/[^_]*.{md,mdx}', base: "./src/content/livereports" }),
  schema: z.object({
    title: z.string(),
    date: z.coerce.date(),
    source: z.string().optional(),
    venue: z.string().optional(),
    artists: z.array(z.string()).optional(),
    setlist: z.array(z.string()).optional(),
  }),
});

export const collections = { livereports };

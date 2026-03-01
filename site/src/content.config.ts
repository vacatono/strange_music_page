import { defineCollection, z } from 'astro:content';

const livereports = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string(),
    date: z.coerce.date(),
    venue: z.string().optional().default(''),
    source: z.enum(['html', 'wordpress']),
    artists: z.array(z.string()).optional().default([]),
    setlist: z.array(z.string()).optional().default([]),
  }),
});

export const collections = { livereports };

import { defineCollection, z } from 'astro:content';

const livereports = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string().optional(),
    date: z.coerce.date().optional(),
    venue: z.string().optional().default(''),
    source: z.enum(['html', 'wordpress', 'fb', 'facebook', 'manual', 'twitter', 'keep', '']).optional(),
    artists: z.array(z.string()).optional().default([]),
    setlist: z.array(z.string()).optional().default([]),
  }),
});

export const collections = { livereports };

import { getCollection } from 'astro:content';

export async function GET() {
  const reports = await getCollection('livereports');

  const index = reports.map((report) => ({
    id: report.id,
    slug: report.id,
    title: report.data.title || '',
    date: report.data.date ? new Date(report.data.date).toISOString().split('T')[0] : '',
    venue: report.data.venue || '',
    artists: report.data.artists || [],
    body: report.body ? report.body.substring(0, 500) : '', // 検索用に冒頭500文字を保持
  }));

  return new Response(JSON.stringify(index), {
    headers: {
      'Content-Type': 'application/json',
    },
  });
}

/**
 * WordPress XML → Markdown変換スクリプト
 * WXR XMLエクスポートから'live'カテゴリの記事を抽出し、
 * Front Matter付きMarkdownファイルとして出力する
 */
import fs from 'fs';
import path from 'path';
import xml2js from 'xml2js';
import TurndownService from 'turndown';

const SOURCE_FILE = path.resolve('../wordpress_export/strangemusicpagewp.wordpress.2026-03-01.xml');
const OUTPUT_DIR = path.resolve('./src/content/livereports');

const turndown = new TurndownService({
  headingStyle: 'atx',
  codeBlockStyle: 'fenced',
  bulletListMarker: '-',
});

// WordPress特有のHTMLフィルタリング
turndown.addRule('removeWordPressShortcodes', {
  filter: (node) => {
    return node.textContent && node.textContent.match(/\[\/?\w+[^\]]*\]/);
  },
  replacement: (content) => {
    return content.replace(/\[\/?\w+[^\]]*\]/g, '');
  },
});

function slugify(text) {
  return text
    .toLowerCase()
    .replace(/[^\w\u3000-\u9fff\uff00-\uffef\s-]/g, '')
    .replace(/[\s]+/g, '-')
    .replace(/-+/g, '-')
    .replace(/^-|-$/g, '')
    .substring(0, 80);
}

function extractDateFromTitle(title) {
  // "2007/07/06 アーティスト名 @会場" のようなパターン
  const match = title.match(/^(\d{4})[\/\.](\d{1,2})[\/\.](\d{1,2})\s+(.+)/);
  if (match) {
    return {
      year: match[1],
      month: match[2].padStart(2, '0'),
      day: match[3].padStart(2, '0'),
      rest: match[4].trim(),
    };
  }
  return null;
}

function parseTitleParts(rest) {
  let artist = rest;
  let venue = '';

  // "@会場" or "@ 会場" or "＠ 会場" or "at 会場"
  const atMatch = rest.match(/^(.+?)\s*(?:@|＠|at)\s*(.+)$/i);
  if (atMatch) {
    artist = atMatch[1].trim();
    venue = atMatch[2].trim();
  }

  return { artist, venue };
}

function wpContentToMarkdown(content) {
  if (!content) return '';

  // WordPress の改行処理
  let html = content
    .replace(/\r\n/g, '\n')
    .replace(/\n\n/g, '</p><p>')
    .replace(/\n/g, '<br>')
    .replace(/^/, '<p>')
    .replace(/$/, '</p>');

  // WordPress shortcodes除去
  html = html.replace(/\[caption[^\]]*\]([\s\S]*?)\[\/caption\]/g, '$1');
  html = html.replace(/\[\/?\w+[^\]]*\]/g, '');

  const md = turndown.turndown(html);
  return md.replace(/\n{3,}/g, '\n\n').trim();
}

function extractTagsAsArtists(categories) {
  if (!categories) return [];
  const cats = Array.isArray(categories) ? categories : [categories];
  return cats
    .filter((cat) => {
      const domain = cat?.$ ? cat.$.domain : '';
      return domain === 'post_tag';
    })
    .map((cat) => {
      return cat._ || cat;
    })
    .filter((name) => typeof name === 'string' && name.length > 0);
}

async function main() {
  // 出力ディレクトリ作成
  if (!fs.existsSync(OUTPUT_DIR)) {
    fs.mkdirSync(OUTPUT_DIR, { recursive: true });
  }

  // XMLを読み込み
  console.log(`Reading: ${SOURCE_FILE}`);
  const xmlContent = fs.readFileSync(SOURCE_FILE, 'utf-8');

  const parser = new xml2js.Parser({
    explicitArray: false,
    preserveChildrenOrder: true,
  });

  const result = await parser.parseStringPromise(xmlContent);
  const items = result.rss.channel.item;
  const allItems = Array.isArray(items) ? items : [items];

  console.log(`Total items: ${allItems.length}`);

  // liveカテゴリの記事のみフィルタ
  const liveItems = allItems.filter((item) => {
    const postType = item['wp:post_type'];
    const typeValue = typeof postType === 'object' ? postType._ : postType;
    if (typeValue !== 'post') return false;

    const categories = item.category;
    if (!categories) return false;
    const cats = Array.isArray(categories) ? categories : [categories];
    return cats.some((cat) => {
      const catName = cat._ || cat;
      const domain = cat?.$ ? cat.$.domain : '';
      return domain === 'category' && catName === 'live';
    });
  });

  console.log(`Live posts: ${liveItems.length}`);

  // 既存のHTML変換済みファイルをチェック（重複排除用）
  const existingDates = new Set();
  if (fs.existsSync(OUTPUT_DIR)) {
    const walkDir = (dir) => {
      const entries = fs.readdirSync(dir, { withFileTypes: true });
      for (const entry of entries) {
        if (entry.isDirectory()) {
          walkDir(path.join(dir, entry.name));
        } else if (entry.name.endsWith('.md')) {
          // ファイルのfront matterからsourceを確認
          const content = fs.readFileSync(path.join(dir, entry.name), 'utf-8');
          const sourceMatch = content.match(/^source:\s*"?html"?\s*$/m);
          if (sourceMatch) {
            // 日付をファイル名から取得
            const dateMatch = entry.name.match(/^(\d{4}-\d{2}-\d{2})/);
            if (dateMatch) {
              existingDates.add(dateMatch[1]);
            }
          }
        }
      }
    };
    walkDir(OUTPUT_DIR);
  }

  console.log(`Existing HTML dates to check for duplicates: ${existingDates.size}`);

  let convertedCount = 0;
  let skippedDuplicates = 0;

  for (const item of liveItems) {
    const title = item.title || 'Untitled';
    const postDate = item['wp:post_date'];
    const dateValue = typeof postDate === 'object' ? postDate._ : postDate;
    const content = item['content:encoded'];
    const contentValue = typeof content === 'object' ? content._ : content;
    const categories = item.category;

    // 日付パース
    let date, year, displayTitle, venue;
    const titleParsed = extractDateFromTitle(title);

    if (titleParsed) {
      date = `${titleParsed.year}-${titleParsed.month}-${titleParsed.day}`;
      year = titleParsed.year;
      const parts = parseTitleParts(titleParsed.rest);
      displayTitle = titleParsed.rest;
      venue = parts.venue;
    } else if (dateValue) {
      // タイトルに日付がない場合、post_dateを使う
      const dateMatch = dateValue.match(/^(\d{4})-(\d{2})-(\d{2})/);
      if (dateMatch) {
        date = `${dateMatch[1]}-${dateMatch[2]}-${dateMatch[3]}`;
        year = dateMatch[1];
        const parts = parseTitleParts(title);
        displayTitle = title;
        venue = parts.venue;
      } else {
        console.warn(`  Skipping (no date): ${title}`);
        continue;
      }
    } else {
      console.warn(`  Skipping (no date): ${title}`);
      continue;
    }

    // 重複チェック: HTML版が存在する場合はスキップ（WP優先なので「WP版で上書き」する）
    // ← 実際にはWP優先なので、HTML版を削除してWP版を書く
    // ここでは逆に、既存HTML版がある日付ではHTML版を削除する
    if (existingDates.has(date)) {
      // HTML版のファイルを削除
      const yearDir = path.join(OUTPUT_DIR, year);
      if (fs.existsSync(yearDir)) {
        const files = fs.readdirSync(yearDir);
        for (const f of files) {
          if (f.startsWith(date)) {
            const fPath = path.join(yearDir, f);
            const fContent = fs.readFileSync(fPath, 'utf-8');
            if (fContent.includes('source: "html"')) {
              fs.unlinkSync(fPath);
              console.log(`  Replaced HTML version: ${f}`);
              skippedDuplicates++;
            }
          }
        }
      }
    }

    // タグからアーティストを抽出
    const artists = extractTagsAsArtists(categories);

    // 本文変換
    const body = wpContentToMarkdown(contentValue || '');

    // 年別ディレクトリ
    const yearDir = path.join(OUTPUT_DIR, year);
    if (!fs.existsSync(yearDir)) {
      fs.mkdirSync(yearDir, { recursive: true });
    }

    // Markdownファイル生成
    let md = '---\n';
    md += `title: "${displayTitle.replace(/"/g, '\\"')}"\n`;
    md += `date: ${date}\n`;
    md += `venue: "${(venue || '').replace(/"/g, '\\"')}"\n`;
    md += `source: "wordpress"\n`;

    if (artists.length > 0) {
      md += 'artists:\n';
      artists.forEach((a) => {
        md += `  - "${a.replace(/"/g, '\\"')}"\n`;
      });
    }

    md += '---\n\n';
    md += body + '\n';

    // ファイル名生成
    const slug = slugify(displayTitle);
    const filename = `${date}-${slug || 'report'}.md`;
    let outputPath = path.join(yearDir, filename);

    // 重複回避
    let counter = 2;
    while (fs.existsSync(outputPath)) {
      const base = filename.replace('.md', `-${counter}.md`);
      outputPath = path.join(yearDir, base);
      counter++;
    }

    fs.writeFileSync(outputPath, md, 'utf-8');
    convertedCount++;
  }

  console.log(`\nDone! Converted ${convertedCount} WordPress posts.`);
  console.log(`Replaced ${skippedDuplicates} HTML duplicates.`);
}

main().catch(console.error);

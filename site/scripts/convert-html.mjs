/**
 * HTML版ライブレポート → Markdown変換スクリプト
 * Shift_JIS HTMLファイルから<div class="box1">ブロックを抽出し、
 * Front Matter付きMarkdownファイルとして出力する
 */
import fs from 'fs';
import path from 'path';
import { load } from 'cheerio';
import iconv from 'iconv-lite';

const SOURCE_DIR = path.resolve('../z');
const OUTPUT_DIR = path.resolve('./src/content/livereports');

// 年別ライブレポートファイル一覧
const HTML_FILES = [
  'liverepo.html', // -1998
  '99liverepo.html', // 1999
  '00liverepo.html', // 2000
  '01liverepo.html', // 2001
  '02liverepo.html', // 2002
  '03liverepo.html', // 2003
  '04liverepo.html', // 2004
  '05liverepo.html', // 2005
];

function readShiftJIS(filePath) {
  const buffer = fs.readFileSync(filePath);
  return iconv.decode(buffer, 'Shift_JIS');
}

function slugify(text) {
  return text
    .toLowerCase()
    .replace(/[^\w\u3000-\u9fff\uff00-\uffef\s-]/g, '')
    .replace(/[\s]+/g, '-')
    .replace(/-+/g, '-')
    .replace(/^-|-$/g, '')
    .substring(0, 80);
}

function htmlToText(html) {
  if (!html) return '';
  return html
    .replace(/<br\s*\/?>/gi, '\n')
    .replace(/<\/p>/gi, '\n\n')
    .replace(/<p[^>]*>/gi, '')
    .replace(/<\/?(font|b|i|em|strong|a|img|div|span)[^>]*>/gi, '')
    .replace(/<[^>]+>/g, '')
    .replace(/&lt;/g, '<')
    .replace(/&gt;/g, '>')
    .replace(/&amp;/g, '&')
    .replace(/&quot;/g, '"')
    .replace(/&#39;/g, "'")
    .replace(/&nbsp;/g, ' ')
    .replace(/\n{3,}/g, '\n\n')
    .trim();
}

function extractSetlistFromOl($, olElement) {
  const items = [];
  $(olElement)
    .find('li')
    .each((_, li) => {
      const text = $(li).text().trim();
      if (text) items.push(text);
    });
  return items;
}

function extractMembersFromUl($, ulElement) {
  const members = [];
  $(ulElement)
    .find('li')
    .each((_, li) => {
      const text = $(li).text().trim();
      if (text) {
        // "名前 (楽器)" のパターンからアーティスト名を抽出
        const match = text.match(/^(.+?)\s*\(/);
        members.push({
          name: match ? match[1].trim() : text,
          instruments: text,
        });
      }
    });
  return members;
}

function parseTitle(titleText) {
  // "1998.12.24 KILLING TIME at 高円寺JIROKICHI" のようなパターン
  // or "1998.12.24 アーティスト @ 会場"
  let dateMatch = titleText.match(/^(\d{4})\.(\d{1,2})\.(\d{1,2})\s+(.+)/);
  if (!dateMatch) {
    // YYYYMMDD形式にも対応 (04liverepo.html以降)
    dateMatch = titleText.match(/^(\d{4})(\d{2})(\d{2})\s+(.+)/);
  }
  if (!dateMatch) return null;

  const year = dateMatch[1];
  const month = dateMatch[2].padStart(2, '0');
  const day = dateMatch[3].padStart(2, '0');
  const rest = dateMatch[4].trim();

  // "アーティスト @ 会場" or "アーティスト at 会場"
  let artist = rest;
  let venue = '';

  const atMatch = rest.match(/^(.+?)\s+(?:@|at|＠)\s+(.+)$/i);
  if (atMatch) {
    artist = atMatch[1].trim();
    venue = atMatch[2].trim();
  }

  return {
    date: `${year}-${month}-${day}`,
    year,
    artist,
    venue,
    title: rest,
  };
}

function processBlock($, block) {
  const $block = $(block);

  // h4からタイトル取得
  const h4 = $block.find('h4').first();
  if (!h4.length) return null;

  const titleText = h4.text().trim();
  const parsed = parseTitle(titleText);
  if (!parsed) {
    console.warn(`  Could not parse title: "${titleText}"`);
    return null;
  }

  // アンカー名取得
  const anchor = h4.find('a[name]').attr('name') || '';

  // セットリスト抽出
  const setlists = [];
  $block.find('ol').each((_, ol) => {
    const items = extractSetlistFromOl($, ol);
    if (items.length > 0) setlists.push(...items);
  });

  // メンバー抽出
  const allMembers = [];
  $block.find('ul').each((_, ul) => {
    const members = extractMembersFromUl($, ul);
    allMembers.push(...members);
  });

  // 本文テキスト抽出（h4, ol, ul を除いた部分）
  // "#"で始まる行がレポート本文
  const blockHtml = $block.html() || '';
  // h4タグを除去
  let bodyHtml = blockHtml.replace(/<h4[^>]*>[\s\S]*?<\/h4>/gi, '');
  // h5タグをMarkdownのh3に変換（サブアクト名など）
  bodyHtml = bodyHtml.replace(/<h5[^>]*>([\s\S]*?)<\/h5>/gi, (_, content) => {
    return `\n### ${content.replace(/<[^>]+>/g, '').trim()}\n`;
  });
  // ol/ul を除去（セットリストとメンバーは別途Front Matterに）
  bodyHtml = bodyHtml.replace(/<ol[^>]*>[\s\S]*?<\/ol>/gi, '');
  bodyHtml = bodyHtml.replace(/<ul[^>]*>[\s\S]*?<\/ul>/gi, '');
  // imgタグを除去
  bodyHtml = bodyHtml.replace(/<img[^>]*>/gi, '');

  const bodyText = htmlToText(bodyHtml)
    .replace(/^#/gm, '') // レポート本文の#プレフィックスを除去
    .replace(/^\s*\n/gm, '\n')
    .trim();

  // アーティスト名リスト（メンバーの名前から）
  const artistNames = allMembers.map((m) => m.name).filter((n) => n);

  return {
    ...parsed,
    anchor,
    setlist: setlists,
    members: allMembers,
    artistNames,
    body: bodyText,
    source: 'html',
  };
}

function generateMarkdown(report) {
  // Front Matter
  const frontMatter = {
    title: report.title,
    date: report.date,
    venue: report.venue,
    source: report.source,
  };

  if (report.artistNames.length > 0) {
    frontMatter.artists = report.artistNames;
  }
  if (report.setlist.length > 0) {
    frontMatter.setlist = report.setlist;
  }

  let md = '---\n';
  md += `title: "${report.title.replace(/"/g, '\\"')}"\n`;
  md += `date: ${report.date}\n`;
  md += `venue: "${report.venue.replace(/"/g, '\\"')}"\n`;
  md += `source: "${report.source}"\n`;

  if (frontMatter.artists && frontMatter.artists.length > 0) {
    md += 'artists:\n';
    frontMatter.artists.forEach((a) => {
      md += `  - "${a.replace(/"/g, '\\"')}"\n`;
    });
  }

  if (frontMatter.setlist && frontMatter.setlist.length > 0) {
    md += 'setlist:\n';
    frontMatter.setlist.forEach((s) => {
      md += `  - "${s.replace(/"/g, '\\"')}"\n`;
    });
  }

  md += '---\n\n';

  // 本文
  if (report.body) {
    md += report.body + '\n\n';
  }

  // メンバーリスト（本文内に表示）
  if (report.members.length > 0) {
    md += '## メンバー\n\n';
    report.members.forEach((m) => {
      md += `- ${m.instruments}\n`;
    });
    md += '\n';
  }

  // セットリスト（本文内にも表示）
  if (report.setlist.length > 0) {
    md += '## セットリスト\n\n';
    report.setlist.forEach((s, i) => {
      md += `${i + 1}. ${s}\n`;
    });
    md += '\n';
  }

  return md;
}

function main() {
  // 出力ディレクトリ作成
  if (!fs.existsSync(OUTPUT_DIR)) {
    fs.mkdirSync(OUTPUT_DIR, { recursive: true });
  }

  let totalReports = 0;

  for (const file of HTML_FILES) {
    const filePath = path.join(SOURCE_DIR, file);
    if (!fs.existsSync(filePath)) {
      console.warn(`File not found: ${filePath}`);
      continue;
    }

    console.log(`Processing: ${file}`);
    const html = readShiftJIS(filePath);
    const $ = load(html);

    const blocks = $('div.box1').toArray();
    console.log(`  Found ${blocks.length} report blocks`);

    for (const block of blocks) {
      const report = processBlock($, block);
      if (!report) continue;

      // 年別ディレクトリ作成
      const yearDir = path.join(OUTPUT_DIR, report.year);
      if (!fs.existsSync(yearDir)) {
        fs.mkdirSync(yearDir, { recursive: true });
      }

      // ファイル名生成
      const slug = slugify(report.artist || report.title);
      const filename = `${report.date}-${slug || 'report'}.md`;
      const outputPath = path.join(yearDir, filename);

      // 重複チェック（同じ日付のファイルが既にある場合はサフィックス追加）
      let finalPath = outputPath;
      let counter = 2;
      while (fs.existsSync(finalPath)) {
        const base = filename.replace('.md', `-${counter}.md`);
        finalPath = path.join(yearDir, base);
        counter++;
      }

      const markdown = generateMarkdown(report);
      fs.writeFileSync(finalPath, markdown, 'utf-8');
      totalReports++;
    }
  }

  console.log(`\nDone! Converted ${totalReports} reports.`);
}

main();

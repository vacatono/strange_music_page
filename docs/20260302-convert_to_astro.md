# Strange Music Page - Astro静的サイト化作業記録

作業日: 2026-03-02

## 概要

旧HTMLサイト（1993-2005年）とWordPressブログ（2003-2014年）のライブレポートを統合し、Astro製の検索可能な静的サイトを構築した。

---

## 1. データソース分析

### 旧HTMLサイト（`z/` ディレクトリ）

| ファイル          | 対象期間  | 備考               |
| ----------------- | --------- | ------------------ |
| `liverepo.html`   | 1993-1998 | 28レポートブロック |
| `99liverepo.html` | 1999      | 6レポートブロック  |
| `00liverepo.html` | 2000      | 36レポートブロック |
| `01liverepo.html` | 2001      | -                  |
| `02liverepo.html` | 2002      | -                  |
| `03liverepo.html` | 2003      | 最大（1845行）     |
| `04liverepo.html` | 2004      | -                  |
| `05liverepo.html` | 2005      | 3レポートブロック  |

- エンコーディング: **Shift_JIS**
- 構造: `<div class="box1">` ブロックごとに1レポート
- 見出し: `<h4><a name="YYYYMMDD">日付 タイトル @ 会場</a></h4>`
- セットリスト: `<ol>` 要素
- メンバー: `<ul>` 要素（`名前 (楽器)` 形式）
- 月別HTMLファイル（`200301.html` 等、約80ファイル）は日記形式で混在。ライブレポートは年別ファイルに集約済みのため、変換対象外とした。

### WordPressエクスポート（`wordpress_export/`）

- ファイル: `strangemusicpagewp.wordpress.2026-03-01.xml`（3.5MB）
- 全785アイテム中、`post` 651件・`page` 17件・`attachment` 113件

| カテゴリ | 件数 |
| -------- | ---- |
| live     | 414  |
| disc     | -    |
| book     | -    |
| etc      | -    |
| news     | -    |
| web      | -    |

- タグ: 117種（アーティスト名含む）
- 年別分布: 2003〜2014年（一部1970年=下書き20件）

### 重複期間

2003〜2005年にHTML版とWordPress版が重複。**WordPress版を優先**し、HTML版の該当レポート（68件）は上書き削除した。

---

## 2. 技術選定

| 要素         | 選択                                  | 理由                                      |
| ------------ | ------------------------------------- | ----------------------------------------- |
| SSG          | Astro 5.x                             | React経験活用、コンテンツコレクション機能 |
| UI           | React                                 | 検索コンポーネント等で利用予定            |
| スタイリング | Vanilla CSS                           | ダークテーマ、シンプル                    |
| 検索         | Pagefind（未実装）                    | ビルド時インデックス、サーバーレス        |
| デプロイ先   | GitHub Pages（未実装）                | 無料、GitHub Actions連携                  |
| 変換ツール   | cheerio, turndown, xml2js, iconv-lite | Node.js製パーサー群                       |

---

## 3. 変換スクリプト

### `site/scripts/convert-html.mjs`

HTML版ライブレポートをMarkdownに変換するスクリプト。

処理フロー:

1. `iconv-lite` でShift_JISからUTF-8に変換
2. `cheerio` で `<div class="box1">` ブロックを抽出
3. `<h4>` タグから日付・タイトル・会場を正規表現でパース
4. `<ol>` からセットリスト、`<ul>` からメンバーを抽出
5. 本文テキストをHTML→プレーンテキスト変換
6. Front Matter付き `.md` ファイルとして `src/content/livereports/YYYY/` に出力

対応した日付フォーマット:

- `1998.12.24 タイトル`（ドット区切り）
- `20050411 タイトル`（ドットなし、04/05liverepo.html用）

### `site/scripts/convert-wordpress.mjs`

WordPress WXR XMLからliveカテゴリの記事をMarkdownに変換するスクリプト。

処理フロー:

1. `xml2js` でXMLをパース
2. `post_type=post` かつ `category=live` の記事のみ抽出
3. タイトルから日付・アーティスト・会場をパース
4. `content:encoded` を `turndown` でMarkdown変換
5. タグ情報からアーティスト名を抽出
6. 重複チェック: 既存のHTML版（`source: "html"`）があれば削除してWP版で置換
7. Front Matter付き `.md` ファイルとして出力

### 変換結果

```
HTML版:       244件 変換
WordPress版:  414件 変換
重複排除:      68件 (WP優先で上書き)
───────────────────
最終合計:     590件
```

---

## 4. Astroサイト構成

### ディレクトリ構成

```
site/
├── astro.config.mjs
├── package.json
├── scripts/
│   ├── convert-html.mjs
│   └── convert-wordpress.mjs
├── src/
│   ├── content.config.ts          # コンテンツコレクション定義
│   ├── content/livereports/       # 変換済み590件（年別フォルダ）
│   │   ├── 1970/ (20件)
│   │   ├── 1994/ (3件)
│   │   ├── ...
│   │   └── 2014/ (7件)
│   ├── layouts/
│   │   └── BaseLayout.astro       # 共通レイアウト（ヘッダー・ナビ・フッター）
│   ├── utils/
│   │   └── slug.ts                # URLスラッグ化（*:等の禁止文字除去）
│   └── pages/
│       ├── index.astro            # トップページ
│       ├── years/
│       │   ├── index.astro        # 年別一覧
│       │   └── [year].astro       # 年別個別ページ
│       ├── artists/
│       │   ├── index.astro        # アーティスト一覧（出現回数順）
│       │   └── [artist].astro     # アーティスト別ページ
│       ├── venues/
│       │   ├── index.astro        # 会場一覧
│       │   └── [venue].astro      # 会場別ページ
│       └── livereports/
│           └── [...slug].astro    # 個別レポートページ
└── public/
    └── styles/
        └── global.css             # ダークテーマCSS
```

### Front Matterスキーマ（`content.config.ts`）

```typescript
{
  title: string,       // "KILLING TIME at 高円寺JIROKICHI"
  date: Date,          // 2003-10-19
  venue: string,       // "高円寺JIROKICHI"
  source: "html" | "wordpress",
  artists: string[],   // ["板倉文", "清水一登", ...]
  setlist: string[],   // ["Peru", "Upon Hearing", ...]
}
```

### ビルド結果

- 生成ページ数: **1282ページ**
- ビルド時間: 約3秒
- 内訳: 590レポート + 年別22ページ + アーティスト445ページ + 会場229ページ 等

### 解決した問題

- **Shift_JISエンコーディング**: `iconv-lite` で変換
- **日付フォーマットの差異**: `1998.12.24` と `20050411` の両方に対応
- **Windowsパス禁止文字**: `Ma*To` 等の `*` を含むアーティスト名でビルドエラー → `toSlug()` で除去
- **重複スラッグ**: 同じスラッグになるアーティスト名の統合処理

---

## 5. 起動方法

```bash
cd site
npm install       # 初回のみ
npm run dev       # 開発サーバー → http://localhost:4321/
npx astro build   # 本番ビルド → dist/ に出力
```

### 変換スクリプトの再実行（データ修正時）

```bash
cd site
node scripts/convert-html.mjs       # HTML版を変換
node scripts/convert-wordpress.mjs   # WordPress版を変換（HTML版を先に実行すること）
```

---

## 6. 残タスク

- [ ] **Pagefind検索の追加**: ビルド時にインデックス生成、トップページに検索UI配置
- [ ] **GitHub Pagesデプロイ**: `astro.config.mjs` に `site`/`base` 設定、GitHub Actionsワークフロー作成
- [ ] **月別HTMLの統合検討**: `z/200301.html` 等の日記コンテンツにもライブレポ関連の記述があるが、現状は対象外
- [ ] **画像の移行**: 旧サイトの `z/img/` 内の画像を必要に応じて移行
- [ ] **デザイン調整**: フォント、配色、レスポンシブ等の改善

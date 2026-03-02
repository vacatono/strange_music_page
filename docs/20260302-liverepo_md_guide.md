# ライブレポート Markdown 書き方ガイド

このガイドでは、`site/src/content/livereports/` 配下に配置するライブレポートの Markdown ファイルの書き方を説明します。

---

## ファイル名の規則

```
YYYY-MM-DD-アーティスト名-会場名.md
```

- **日付**: `YYYY-MM-DD` 形式（例: `2013-05-08`）
- **アーティスト名**: 複数の場合はハイフン `-` 区切り
- **会場名**: スペースはハイフンに置き換える
- すべて小文字の英数字 + 日本語。特殊文字（`*:<>?"|\/`）は使わない

### ファイル名の例

| 内容               | ファイル名                                                 |
| ------------------ | ---------------------------------------------------------- |
| 単独公演           | `2013-05-08-kraftwerk-赤坂blitz.md`                        |
| 複数アーティスト   | `2013-03-17-anglagard-crimson-projekcts-川崎club-citta.md` |
| 日本語アーティスト | `2013-05-31-福原まり-西麻布新世界.md`                      |

### ディレクトリ構成

年ごとのサブディレクトリに配置してください。

```
site/src/content/livereports/
├── 2003/
│   ├── 2003-03-22-lars-hollmers-sola.md
│   └── ...
├── 2013/
│   ├── 2013-05-08-kraftwerk-赤坂blitz.md
│   └── ...
├── 2014/
│   └── ...
└── 2026-02-21-mitarafina-那由他計画-吉祥寺silver-elephant.md
```

> [!NOTE]
> ルート直下に置いても動作しますが、整理のため年ディレクトリの使用を推奨します。

---

## Frontmatter（メタデータ）

ファイル先頭の `---` で囲まれた YAML ブロックです。

```yaml
---
title: "Anglagard, Crimson ProjeKcts @川崎CLUB CITTA'"
date: 2013-03-17
venue: "川崎CLUB CITTA'"
source: 'wordpress'
artists:
  - 'Anglagard'
  - 'Crimson ProjeKct'
setlist:
  - "B'BOOM"
  - 'Thrak'
  - 'Dinosaur'
---
```

### フィールド一覧

| フィールド | 必須 | 型                        | 説明                                                   |
| ---------- | ---- | ------------------------- | ------------------------------------------------------ |
| `title`    | ✅   | 文字列                    | レポートのタイトル。`"アーティスト @会場"` 形式を推奨  |
| `date`     | ✅   | 日付                      | ライブの日付（`YYYY-MM-DD` 形式）                      |
| `venue`    |      | 文字列                    | 会場名（省略可、会場ページへのリンクに使用）           |
| `source`   | ✅   | `"html"` or `"wordpress"` | データの出典元                                         |
| `artists`  |      | 文字列配列                | 出演アーティスト名のリスト（アーティストページに使用） |
| `setlist`  |      | 文字列配列                | セットリストの曲名リスト（構造化データとして表示）     |

> [!IMPORTANT]
>
> - `title` と `venue` に `'`（シングルクォート）を含む場合は、値全体を `"` で囲んでください
> - 新規作成時の `source` は `"wordpress"` を使用してください

### source フィールドについて

| 値            | 用途                                               |
| ------------- | -------------------------------------------------- |
| `"html"`      | 旧 HTML サイトから移行したレポート                 |
| `"wordpress"` | WordPress ブログから移行した or 新規作成のレポート |

---

## 本文の書き方

Frontmatter の `---` 以降が本文です。通常の Markdown 記法が使えます。

### 基本構成

```markdown
---
(frontmatter)
---

ライブの感想やレポート本文をここに書きます。
段落はそのまま改行を挟んで書けます。

改行を維持したい場合は行末にスペース2つを入れます。  
こうすると同じ段落内で改行されます。
```

### 複数バンドが出演する場合

各バンドのセクションを太字見出し（`**`）または見出し（`####`）で区切ります。

```markdown
**Mauro Pagani**

Mauro Paganiについてのレポート...

Mauro Pagani (violin, guitars, bouzouki, flute, vocals)  
Eros Cristiani (keyboards)  
Joe Damiani (drums)

**Area**

Areaについてのレポート...

Patrizio Fariselli (piano, keyboards)  
Paolo Tofani (guitars, vocals)  
Ares Tavolazzi (bass)  
Walter Paoli (drums)
```

> [!TIP]
> `####`（h4見出し）を使うパターンもあります。`#### Anglagard` のように書くとやや大きめの見出しになります。

---

## セットリストの書き方

セットリストは **Frontmatter の `setlist` フィールド** と **本文** の 2 箇所に書けます。

### 方法① Frontmatter に記述（推奨）

構造化データとして扱われ、ページ下部に自動的にリスト表示されます。

```yaml
setlist:
  - 'Parallel Railways'
  - 'Winter Song'
  - 'かげろう'
```

### 方法② 本文に記述

自由なフォーマットで書けます。番号付きリストとして記述します。

```markdown
1\. B'BOOM (Reuter+Mastelotto+Ralph)  
2\. Thrak  
3\. Dinosaur  
4\. Elephant Talk
```

> [!NOTE]
> `\. ` と書く（バックスラッシュでエスケープ）のは、Markdown の自動番号振りを防ぐためです。  
> 必須ではありませんが、番号を手動で管理したい場合に使います。

### アンコールの区切り

本文でセットリストを書く場合、アンコール部分は空行で区切ります。

```markdown
1\. Red  
2\. Indiscipline

3\. Thela Hun Ginjeet（アンコール）
```

---

## メンバー / 出演者の書き方

各行に `名前 (楽器)` 形式で、行末にスペース2つを入れて改行します。

```markdown
平田聡 (guitars)  
佐藤真也 (keyboards)  
佐々木絵実 (accordion)  
入山ひとみ (violin)  
谷本朋翼 (drums)  
佐野俊介 (bass)
```

> [!TIP]
> 行末の **スペース2つ** (`  `) が重要です。これがないと改行されず、名前が1行に連結されてしまいます。

---

## 完全なサンプル

### パターン A: シンプルなワンマン公演

```markdown
---
title: 'Stella Lee Jones @吉祥寺Silver Elephant'
date: 2014-05-10
venue: '吉祥寺Silver Elephant'
source: 'wordpress'
---

前回のチッタでは若干音響関係で聴きづらかったのですが、
今回はバッチリ過ぎる程バッチリです。

ベースが代わったせいかドラムが色んな事やってるのが
今回は良く聴こえました。

1\. Parallel Railways  
2\. Winter Song  
3\. かげろう  
4\. Salar de Uyuni

5\. Jean Pierre（アンコール）

平田聡 (guitars)  
佐藤真也 (keyboards)  
佐々木絵実 (accordion)  
入山ひとみ (violin)  
谷本朋翼 (drums)  
佐野俊介 (bass)
```

### パターン B: 複数バンド + Frontmatter セットリスト

```markdown
---
title: 'NATSUMEN @ NHK-FM ライブビート公開収録'
date: 2005-04-21
venue: 'NHK-FM ライブビート公開収録'
source: 'wordpress'
artists:
  - 'A.S.E'
  - 'アイン'
  - 'マシタ'
  - '蔦谷好位置'
setlist:
  - 'Whole Lotta Summer'
  - 'Sonata of The Summer'
  - 'Pills To Kill Ma August'
---

NATSUMENのライブレポート本文...

## メンバー

- A.S.E (guitars)
- アイン (guitars)
- マシタ (drums)
- 蔦谷好位置 (piano)
```

### パターン C: フェス / 来日公演

```markdown
---
title: "Mauro Pagani, Area @川崎CLUB CITTA'"
date: 2013-04-28
venue: "川崎CLUB CITTA'"
source: 'wordpress'
artists:
  - '来日公演'
---

**Mauro Pagani**

Paganiのレポート...

Mauro Pagani (violin, guitars)  
Eros Cristiani (keyboards)  
Joe Damiani (drums)

**Area**

Areaのレポート...

Patrizio Fariselli (piano, keyboards)  
Paolo Tofani (guitars, vocals)
```

---

## よくあるミス

| ミス                                    | 正しい書き方                                    |
| --------------------------------------- | ----------------------------------------------- | -------------- |
| 行末スペースなしで改行                  | 行末にスペース2つ `  ` を付ける                 |
| `title` にシングルクォートを含む        | 値全体をダブルクォートで囲む: `title: "Citta'"` |
| `date` の形式が不正                     | `YYYY-MM-DD` 形式を使う（例: `2013-04-28`）     |
| `source` の値が不正                     | `"html"` または `"wordpress"` のいずれかを指定  |
| Frontmatter の `---` が閉じられていない | 開始と終了の両方に `---` を書く                 |
| ファイル名に特殊文字                    | `\*:<>?"                                        | \/` は使わない |

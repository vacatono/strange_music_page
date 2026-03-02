# GitHub Pages へのデプロイ手順

このプロジェクト（strange_music_page）を GitHub Pages で公開するための手順をまとめます。
このプロジェクトは Astro を使用しており、ルート直下の `site/` ディレクトリにソースコードが含まれています。

## 構成の概要

- **GitHub リポジトリ**: `vacatono/strange_music_page`
- **公開用URL**: `https://vacatono.github.io/strange_music_page/`
- **デプロイ方法**: GitHub Actions による自動デプロイ

## 事前準備（完了済み）

以下のファイルが設定済みです。

1.  **Astro 設定 (`site/astro.config.mjs`)**:
    GitHub Pages のサブパス `/strange_music_page` で正しくアセットが読み込まれるように `site` と `base` を設定済みです。
2.  **GitHub Actions ワークフロー (`.github/workflows/deploy.yml`)**:
    GitHub への push 時に自動的にビルドし、`site/dist` の内容をデプロイする設定済みです。

## 手順 1: GitHub リポジトリの設定

GitHub Actions を使用してデプロイするために、GitHub のリポジトリ設定を変更する必要があります。

1.  GitHub のリポジトリページ（`vacatono/strange_music_page`）を開きます。
2.  **Settings** タブをクリックします。
3.  左側メニューの **Pages** を選択します。
4.  **Build and deployment** セクションの **Source** ドロップダウンを **GitHub Actions** に変更します。

## 手順 2: コードのプッシュ

設定したファイルを `main` ブランチに push します。

```bash
git add .
git commit -m "Add GitHub Pages deployment settings"
git push origin main
```

## 手順 3: デプロイ状況の確認

1.  GitHub リポジトリの **Actions** タブをクリックします。
2.  `Deploy to GitHub Pages` というワークフローが実行されていることを確認します。
3.  実行が完了（緑色のチェックマーク）すると、デプロイが完了します。
4.  デプロイ完了後、`https://vacatono.github.io/strange_music_page/` にアクセスして動作を確認してください。

## トラブルシューティング

- **画像が表示されない**: `base` 設定が正しく反映されているか確認してください。Astro コンポーネント内では `<img src="/strange_music_page/images/foo.jpg" />` のようにパスを指定するか、`import` 構文を利用してください。
- **デプロイに失敗する**: Actions のログを確認し、`npm install` や `npm run build` でエラーが出ていないか確認してください。

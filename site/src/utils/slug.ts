/**
 * URLセーフなスラッグを生成する
 * Windows/OSのパス禁止文字(*:<>?"|\/等)を除去しつつ、
 * 日本語文字はそのまま保持する
 */
export function toSlug(text: string): string {
  return text
    .replace(/[*:<>?"|\\/]/g, '') // ファイルシステム禁止文字除去
    .replace(/\s+/g, '-')
    .replace(/-+/g, '-')
    .replace(/^-|-$/g, '')
    .trim();
}

/**
 * スラッグからオリジナル名を逆引きするためのMap構築ヘルパー
 */
export function buildSlugMap(names: string[]): Map<string, string> {
  const map = new Map<string, string>();
  for (const name of names) {
    map.set(toSlug(name), name);
  }
  return map;
}

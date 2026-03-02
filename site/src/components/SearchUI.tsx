import React, { useState, useEffect, useRef } from 'react';
import Fuse from 'fuse.js';

interface SearchResult {
  id: string;
  slug: string;
  title: string;
  date: string;
  venue: string;
  artists: string[];
  body: string;
}

const SearchUI: React.FC = () => {
  const [query, setQuery] = useState('');
  const [results, setResults] = useState<any[]>([]);
  const [fuse, setFuse] = useState<Fuse<SearchResult> | null>(null);
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    fetch('/search-index.json')
      .then(res => res.json())
      .then(data => {
        const fuseInstance = new Fuse<SearchResult>(data, {
          keys: [
            { name: 'title', weight: 1.0 },
            { name: 'artists', weight: 0.8 },
            { name: 'venue', weight: 0.7 },
            { name: 'body', weight: 0.4 }
          ],
          threshold: 0.3, // 0.0は完全一致、1.0はすべてに一致。日本語の部分一致のために調整
          ignoreLocation: true, // 全文から検索
          minMatchCharLength: 1,
          useExtendedSearch: true, // 引用符やAND検索を使えるようにする
        });
        setFuse(fuseInstance);
        setIsLoading(false);
      })
      .catch(err => {
        console.error('Failed to load search index:', err);
        setIsLoading(false);
      });
  }, []);

  const handleSearch = (e: React.ChangeEvent<HTMLInputElement>) => {
    const val = e.target.value;
    setQuery(val);

    if (!fuse) return;
    if (val.trim() === '') {
      setResults([]);
      return;
    }

    // 日本語の部分一致を強化するため、クエリがスペースなしの場合は完全一致含め柔軟に検索
    const searchResults = fuse.search(val);
    setResults(searchResults.slice(0, 50)); // 上位50件を表示
  };

  return (
    <div className="search-ui-container">
      <div className="search-input-wrapper">
        <input
          type="text"
          value={query}
          onChange={handleSearch}
          placeholder={isLoading ? "インデックス読み込み中..." : "アーティスト、会場、曲名で検索..."}
          className="search-input"
          disabled={isLoading}
        />
        {isLoading && <div className="spinner"></div>}
      </div>

      {query && !isLoading && (
        <div className="search-results-summary">
          {results.length > 0
            ? `「${query}」で ${results.length} 件の結果が見つかりました`
            : `「${query}」に一致する結果は見つかりませんでした`}
        </div>
      )}

      <div className="search-results-list">
        {results.map(({ item }) => (
          <a key={item.id} href={`/livereports/${item.slug}/`} className="search-result-item">
            <div className="result-header">
              <span className="result-date">{item.date}</span>
              <h3 className="result-title">{item.title}</h3>
            </div>
            <div className="result-meta">
              <span className="result-venue">{item.venue}</span>
              {item.artists.length > 0 && (
                <span className="result-artists"> / {item.artists.join(', ')}</span>
              )}
            </div>
            <p className="result-excerpt">
              {item.body.substring(0, 150)}...
            </p>
          </a>
        ))}
      </div>

      <style>{`
        .search-ui-container {
          margin: 2rem 0;
          font-family: inherit;
        }
        .search-input-wrapper {
          position: relative;
          margin-bottom: 1rem;
        }
        .search-input {
          width: 100%;
          padding: 1rem 1.25rem;
          font-size: 1.1rem;
          border: 2px solid var(--color-border);
          border-radius: 12px;
          background-color: var(--color-bg-card);
          color: var(--color-text);
          transition: all 0.2s ease;
          box-shadow: 0 2px 4px rgba(0,0,0,0.05);
        }
        .search-input:focus {
          outline: none;
          border-color: var(--color-accent);
          box-shadow: 0 4px 12px rgba(var(--color-accent-rgb, 100, 100, 255), 0.15);
        }
        .search-results-summary {
          margin-bottom: 1.5rem;
          font-size: 0.9rem;
          color: var(--color-text-muted);
          padding-left: 0.5rem;
        }
        .search-results-list {
          display: flex;
          flex-direction: column;
          gap: 1rem;
        }
        .search-result-item {
          display: block;
          padding: 1.25rem;
          background-color: var(--color-bg-card);
          border: 1px solid var(--color-border);
          border-radius: 10px;
          text-decoration: none;
          color: inherit;
          transition: transform 0.2s ease, border-color 0.2s ease;
        }
        .search-result-item:hover {
          transform: translateY(-2px);
          border-color: var(--color-accent);
          background-color: var(--color-bg-card-hover, rgba(255,255,255,0.02));
        }
        .result-header {
          display: flex;
          align-items: baseline;
          gap: 1rem;
          margin-bottom: 0.5rem;
        }
        .result-date {
          font-size: 0.85rem;
          font-family: monospace;
          color: var(--color-text-muted);
          flex-shrink: 0;
        }
        .result-title {
          margin: 0;
          font-size: 1.1rem;
          font-weight: 600;
          color: var(--color-accent);
        }
        .result-meta {
          font-size: 0.9rem;
          color: var(--color-text-muted);
          margin-bottom: 0.75rem;
        }
        .result-excerpt {
          margin: 0;
          font-size: 0.9rem;
          line-height: 1.6;
          color: var(--color-text);
          opacity: 0.85;
          display: -webkit-box;
          -webkit-line-clamp: 2;
          -webkit-box-orient: vertical;
          overflow: hidden;
        }
        .spinner {
          position: absolute;
          right: 1.25rem;
          top: 50%;
          transform: translateY(-50%);
          width: 20px;
          height: 20px;
          border: 2px solid rgba(0,0,0,0.1);
          border-top-color: var(--color-accent);
          border-radius: 50%;
          animation: spin 1s linear infinite;
        }
        @keyframes spin {
          to { transform: translateY(-50%) rotate(360deg); }
        }
      `}</style>
    </div>
  );
};

export default SearchUI;

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

const HeaderSearch: React.FC = () => {
  const [query, setQuery] = useState('');
  const [results, setResults] = useState<any[]>([]);
  const [fuse, setFuse] = useState<Fuse<SearchResult> | null>(null);
  const [isOpen, setIsOpen] = useState(false);
  const containerRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const baseUrl = import.meta.env.BASE_URL.replace(/\/$/, '');
    fetch(`${baseUrl}/search-index.json`.replace('//', '/'))
      .then(res => res.json())
      .then(data => {
        const fuseInstance = new Fuse<SearchResult>(data, {
          keys: [
            { name: 'title', weight: 1.0 },
            { name: 'artists', weight: 0.8 },
            { name: 'venue', weight: 0.7 },
            { name: 'body', weight: 0.4 }
          ],
          threshold: 0.3,
          ignoreLocation: true,
          minMatchCharLength: 1,
          useExtendedSearch: true,
        });
        setFuse(fuseInstance);
      })
      .catch(err => {
        console.error('Failed to load search index:', err);
      });

    const handleClickOutside = (event: MouseEvent) => {
      if (containerRef.current && !containerRef.current.contains(event.target as Node)) {
        setIsOpen(false);
      }
    };

    document.addEventListener('mousedown', handleClickOutside);
    return () => document.removeEventListener('mousedown', handleClickOutside);
  }, []);

  const handleSearch = (e: React.ChangeEvent<HTMLInputElement>) => {
    const val = e.target.value;
    setQuery(val);

    if (!fuse || val.trim() === '') {
      setResults([]);
      setIsOpen(false);
      return;
    }

    const searchResults = fuse.search(val);
    setResults(searchResults.slice(0, 8));
    setIsOpen(true);
  };

  const baseUrl = import.meta.env.BASE_URL.replace(/\/$/, '');

  return (
    <div className="header-search-container" ref={containerRef}>
      <div className="header-search-input-wrapper">
        <input
          type="text"
          value={query}
          onChange={handleSearch}
          onFocus={() => query.trim() !== '' && setIsOpen(true)}
          placeholder="検索..."
          className="header-search-input"
        />
      </div>

      {isOpen && (
        <div className="header-search-dropdown shadow-lg">
          {results.length > 0 ? (
            <div className="search-results-mini">
              {results.map(({ item }) => (
                <a
                  key={item.id}
                  href={`${baseUrl}/live/report/${item.slug}/`}
                  className="search-result-mini-item"
                  onClick={() => {
                    setIsOpen(false);
                    setQuery('');
                  }}
                >
                  <div className="mini-result-date">{item.date}</div>
                  <div className="mini-result-title">{item.title}</div>
                  <div className="mini-result-meta">{item.venue}</div>
                </a>
              ))}
              <div className="search-dropdown-footer">
                <a href={`${baseUrl}/live/`}>すべての結果を表示...</a>
              </div>
            </div>
          ) : query.trim() !== '' && (
            <div className="search-no-results">見つかりませんでした</div>
          )}
        </div>
      )}

      <style>{`
        .header-search-container {
          position: relative;
          width: 200px;
        }
        .header-search-input-wrapper {
          position: relative;
          display: flex;
          align-items: center;
        }
        .header-search-input {
          width: 100%;
          padding: 0.4rem 0.8rem;
          font-size: 0.85rem;
          border: 1px solid var(--color-border);
          border-radius: 8px;
          background-color: var(--color-bg-card);
          color: var(--color-text);
        }
        .header-search-input:focus {
          outline: none;
          border-color: var(--color-accent);
          background-color: #fff;
        }
        .header-search-dropdown {
          position: absolute;
          top: calc(100% + 8px);
          right: 0;
          width: 300px;
          background: white;
          border: 1px solid var(--color-border);
          border-radius: 8px;
          z-index: 1000;
          box-shadow: 0 10px 25px rgba(0,0,0,0.1);
          overflow: hidden;
        }
        .search-results-mini {
          display: flex;
          flex-direction: column;
        }
        .search-result-mini-item {
          padding: 0.75rem 1rem;
          border-bottom: 1px solid #f0f0f0;
          text-decoration: none;
          color: inherit;
          display: block;
          transition: background 0.2s;
        }
        .search-result-mini-item:last-of-type {
          border-bottom: none;
        }
        .search-result-mini-item:hover {
          background-color: #f8fafc;
        }
        .mini-result-date {
          font-size: 0.7rem;
          font-family: monospace;
          color: var(--color-text-muted);
        }
        .mini-result-title {
          font-size: 0.9rem;
          font-weight: 600;
          white-space: nowrap;
          overflow: hidden;
          text-overflow: ellipsis;
          color: var(--color-text-heading);
          margin: 2px 0;
        }
        .mini-result-meta {
          font-size: 0.75rem;
          color: var(--color-text-muted);
          white-space: nowrap;
          overflow: hidden;
          text-overflow: ellipsis;
        }
        .search-dropdown-footer {
          background-color: #f1f5f9;
          padding: 0.5rem;
          text-align: center;
          font-size: 0.8rem;
        }
        .search-dropdown-footer a {
          color: var(--color-accent);
          font-weight: 500;
        }
        .search-no-results {
          padding: 1rem;
          text-align: center;
          font-size: 0.85rem;
          color: var(--color-text-muted);
        }

        @media (max-width: 640px) {
          .header-search-container {
            width: 100%;
            margin-top: 0.5rem;
          }
          .header-search-dropdown {
            width: 100%;
            left: 0;
          }
        }
      `}</style>
    </div>
  );
};

export default HeaderSearch;

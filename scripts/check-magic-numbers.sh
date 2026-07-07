#!/usr/bin/env bash
# Flags bare numeric literals (sentinel/magic values) not backed by a named
# const/#define. Heuristic, not a full parser — silence a false positive by
# adding `// magic-ok` on that line.
set -uo pipefail

fail=0
for f in "$@"; do
  [ -f "$f" ] || continue
  hits=$(grep -nE '[0-9]{4,}|[0-9]+e[0-9]+' "$f" | grep -vE 'const|#define|constexpr|magic-ok' || true)
  if [ -n "$hits" ]; then
    while IFS= read -r line; do
      echo "$f:$line"
    done <<< "$hits"
    fail=1
  fi
done
exit $fail

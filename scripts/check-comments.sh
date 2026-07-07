#!/usr/bin/env bash
# Requires at least one comment per file. Presence only — it can't judge
# whether the comment explains "why" instead of "what"; that part is on you
# at self-review time, not something a script can grade honestly.
set -uo pipefail

fail=0
for f in "$@"; do
  [ -f "$f" ] || continue
  if ! grep -qE '//|/\*' "$f"; then
    echo "$f: no comment found - add at least a one-line note on your approach/assumptions"
    fail=1
  fi
done
exit $fail

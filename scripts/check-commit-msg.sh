#!/usr/bin/env bash
# Rejects vague/placeholder commit messages.
#
# Two modes:
#   check-commit-msg.sh <commit-msg-file>   used as the commit-msg hook
#   check-commit-msg.sh --range <rev-range> used in CI, checks every commit in the range
set -euo pipefail

VAGUE_PATTERNS=(
  '^[0-9]{1,2}(st|nd|rd|th)? [A-Za-z]+$'   # "2nd July"
  '^[0-9]{1,2}/[0-9]{1,2}/[0-9]{2,4}'      # "16/09/24"
  '^Auto-commit'                            # broken auto-commit placeholder
  '^[Pp]roblem[ :]?[0-9]+ *$'               # "problem 44" with nothing else
)

check_one() {
  local first_line="$1"

  if [ "${#first_line}" -lt 12 ]; then
    echo "REJECTED: commit message too short to be meaningful: \"$first_line\""
    return 1
  fi

  for pat in "${VAGUE_PATTERNS[@]}"; do
    if echo "$first_line" | grep -qE "$pat"; then
      echo "REJECTED: commit message matches a known-vague pattern: \"$first_line\""
      echo "  Say what problem and what approach/fix, e.g.:"
      echo "  \"Rotate array by d: reversal algorithm, O(n)\""
      return 1
    fi
  done
  return 0
}

if [ "${1:-}" = "--range" ]; then
  range="$2"
  fail=0
  while IFS= read -r sha; do
    first_line=$(git log -1 --format=%s "$sha")
    if ! check_one "$first_line"; then
      echo "  -> commit $sha"
      fail=1
    fi
  done < <(git rev-list "$range")
  exit $fail
else
  msg_file="$1"
  first_line=$(head -1 "$msg_file")
  check_one "$first_line"
fi

#!/usr/bin/env bash
# Compiles each given .cpp and, if a matching input/<name>.in + output/<name>.out
# pair exists, runs it and diffs the output against expected. New problems must
# ship a test pair - this fails loud if one's missing for a file passed in.
#
# Expects the standard layout: <topic>/codes/<name>.cpp
#                               <topic>/input/<name>.in
#                               <topic>/output/<name>.out
set -uo pipefail

fail=0
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

for f in "$@"; do
  [ -f "$f" ] || continue
  name=$(basename "$f" .cpp)
  problem_set=$(dirname "$(dirname "$f")")
  in_file="$problem_set/input/$name.in"
  out_file="$problem_set/output/$name.out"
  bin="$tmp/$name"

  if ! g++ -O2 -std=c++17 -o "$bin" "$f" 2> "$tmp/$name.compile.log"; then
    echo "$f: FAILED to compile"
    cat "$tmp/$name.compile.log"
    fail=1
    continue
  fi

  if [ ! -f "$in_file" ] || [ ! -f "$out_file" ]; then
    echo "$f: no input/$name.in + output/$name.out found - add a sample I/O pair for new problems"
    fail=1
    continue
  fi

  actual=$("$bin" < "$in_file")
  expected=$(cat "$out_file")
  if [ "$actual" != "$expected" ]; then
    echo "$f: test FAILED"
    echo "  expected: $expected"
    echo "  actual:   $actual"
    fail=1
  else
    echo "$f: test passed"
  fi
done
exit $fail

#!/usr/bin/env bash

YEAR=${1:-$(date +%Y)}
DAY=${2:-$(date +%-d)}

. $(dirname $0)/.env
curl -L https://adventofcode.com/$YEAR/day/$DAY/input --cookie "session=$SESSION" > input.dat

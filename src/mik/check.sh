#!/usr/bin/env bash

[ -f $1 ] || exit 1

n=75

echo -n "Straight (1-${n} elements) " >&2
/usr/bin/time -f '%E' $1 -m 1 ${n} -s

echo -n "Memoize (1-${n} elements) " >&2
/usr/bin/time -f '%E' $1 1 ${n} -s

#!/usr/bin/env bash

[ -f $1 ] || exit 1

n=1000

echo -n "(1-${n} elements) " >&2
/usr/bin/time -f '%E' $1 1 ${n} -s

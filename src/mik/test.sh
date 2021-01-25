#!/usr/bin/env bash

[ -f $1 ] || exit 1

n=49

cmp -s ../../lib/1-${n}.data <(./$1 -v 1 ${n}) &&
cmp -s ../../lib/1-${n}.data <(./$1 -v -m 1 ${n})

#!/usr/bin/env bash

[ -f $1 ] || exit 1

n=49

exec cmp -s ../../lib/1-${n}.data <(./$1 -v 1 ${n})

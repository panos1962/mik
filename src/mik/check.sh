#!/usr/bin/env bash

[ -f $1 ] || exit 1

comm -3 1-49.data <(./$1 -v 1 49)
comm -3 1-49.data <(./$1 -v -m 1 49)

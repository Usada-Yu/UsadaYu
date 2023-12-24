#!/bin/bash

set -e

gcc -o main cpy_move.c

mkdir -p bin && mv main bin

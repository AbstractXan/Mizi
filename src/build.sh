#!/bin/bash

rm ../site/*.html
rm mizi
make

# Test
./mizi -t

# Build
./mizi

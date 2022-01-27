#!/bin/bash

rm ../site/*.html
rm mizi
make


# Test
./mizi -t

cd ../

# Build
./src/mizi

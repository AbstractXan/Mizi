#!/bin/bash

# Run the script to update the last commit date in config.conf
./updatetime_footer.sh

rm ../site/*.html
rm mizi
make


# Test
./mizi -t

cd ../

# Build
./src/mizi

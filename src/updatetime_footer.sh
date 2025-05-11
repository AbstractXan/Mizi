#!/bin/bash

# Get the current date and time
CURRENT_DATE=$(date +"%a %b %d %T %Y")

# Get the directory of the script
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# Define the config file path relative to the script's directory
CONFIG_FILE="$SCRIPT_DIR/../config.conf"

# Use `sed` to replace the "Last updated" placeholder in the footer
sed -i "s|Last updated:.*|Last updated: $CURRENT_DATE</p>|" "$CONFIG_FILE"

# Uncomment the following line if you want to log the update
echo "Updated last updated time in $CONFIG_FILE to: $CURRENT_DATE"
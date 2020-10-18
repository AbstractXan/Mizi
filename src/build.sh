#!/bin/bash

rm ../site/*
rm mizi

make

./mizi -t -a

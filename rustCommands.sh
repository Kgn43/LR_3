#!/bin/bash

cd rustCoverage/

cargo tarpaulin --out html

xdg-open ~/Desktop/LR_3/rustCoverage/tarpaulin-report.html

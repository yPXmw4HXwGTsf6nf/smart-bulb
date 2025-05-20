#!/usr/bin/env bash
set -e
idf.py build
idf.py -p "${1:-/dev/ttyUSB0}" flash monitor

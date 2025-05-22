#!/usr/bin/env bash
# flashes the firmware to the esp device then opens the serial monitor
set -eu
idf.py -p "${1:-/dev/ttyUSB0}" flash monitor

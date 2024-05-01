#!/bin/sh

MODE=$(echo "$1" | tr '[:upper:]' '[:lower:]')

if [ "${MODE}" = "release" ]; then
  MODE=Release
elif [ "${MODE}" = "debug" ]; then
  MODE=Debug
else
  echo "Usage: $0 [release|debug]"
  exit 1
fi

set -e

cmake -S . -B build -DCMAKE_BUILD_TYPE=${MODE} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
ln -sf assets build/bin/assets

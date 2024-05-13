#!/bin/sh

MODE=$(echo "$1" | tr '[:upper:]' '[:lower:]')

if [ "${MODE}" = "release" ]; then
  MODE=Release
  DEBUG_DISPLAY_COLLIDABLES=OFF
elif [ "${MODE}" = "debug" ]; then
  MODE=Debug
  DEBUG_DISPLAY_COLLIDABLES=ON
else
  echo "Usage: $0 [release|debug]"
  exit 1
fi

set -e

cmake -S . -B build -DCMAKE_BUILD_TYPE=${MODE} -DDEBUG_DISPLAY_COLLIDABLES=${DEBUG_DISPLAY_COLLIDABLES} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
ln -sf assets build/bin/assets

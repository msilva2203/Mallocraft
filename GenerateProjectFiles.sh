#!/bin/sh
set -xe

PREMAKE_ACTION=gmake2
COMPILER=clang

./Build/Linux/premake-5.0.0-beta2-linux/premake5 "$PREMAKE_ACTION" --cc="$COMPILER"

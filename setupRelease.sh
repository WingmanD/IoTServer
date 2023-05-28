﻿#!/bin/bash
BUILD_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

mkdir -p "$BUILD_PATH/build"

conan install . --build=missing -s cppstd=20 -s build_type=Release

cmake . -G Ninja

cmake --build . --config Release
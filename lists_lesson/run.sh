#!/bin/bash

# ─────────────────────────────────────────
#  Build script for lists_lesson
# ─────────────────────────────────────────

set -e  # stop immediately if any command fails

PROJECT_NAME="lists_lesson"
BUILD_DIR="build"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# ── Parse arguments ──────────────────────
CLEAN=false
RUN=false

for arg in "$@"; do
    case $arg in
        --clean) CLEAN=true ;;
        --run)   RUN=true ;;
        --help)
            echo "Usage: ./build.sh [--clean] [--run]"
            echo "  --clean  Remove build/ folder before building"
            echo "  --run    Run the executable after building"
            exit 0
            ;;
    esac
done

# ── Clean ────────────────────────────────
if [ "$CLEAN" = true ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# ── Generate ─────────────────────────────
if [ ! -d "$BUILD_DIR" ]; then
    echo "Generating build files..."
    cmake -S . -B "$BUILD_DIR"
fi

# ── Build ────────────────────────────────
echo "Building..."
cmake --build "$BUILD_DIR"

echo -e "${GREEN}Build successful!${NC}"

# ── Run ──────────────────────────────────
if [ "$RUN" = true ]; then
    echo "Running $PROJECT_NAME..."
    echo "─────────────────────────────────────────"
    ./"$BUILD_DIR"/"$PROJECT_NAME"
fi

#!/bin/sh

find . -maxdepth 1 ! -name "*.cpp" ! -name "*.hpp" ! -name $(basename "$0") ! -name "." -exec rm -rf {} \+

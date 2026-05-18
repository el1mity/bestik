#!/bin/sh

for f in *.cp *.c++ *.cc *.cxx; do [ -e "$f" ] && mv "$f" "${f%.*}.cpp"; done

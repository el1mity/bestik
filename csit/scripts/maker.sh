#!/bin/sh

mkdir -p Build

case "$1" in
    build)
 g++ "$2" -o Build/main
 ;;
    run)
 g++ "$2" -o Build/main
 ./Build/main
 ;;
    clean)
 rm -rf Build
 ;;
esac

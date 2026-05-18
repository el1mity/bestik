#!/bin/sh

ls main.cpp | entr -c g++ main.cpp -o main

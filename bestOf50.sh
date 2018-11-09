#!/bin/bash
if [ -f "$1" ]
then
  for i in {0..50}; 
  do 
    echo -n "$i ";
    ./sdlA $1 0 $i | grep DO | tail -n1; 
  done | sort -nk3 | head -n1;
else 
  echo "Usage: $0 file.csv"
fi
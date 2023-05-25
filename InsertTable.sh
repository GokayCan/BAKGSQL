#!/bin/bash

paramlist=("$@")

echo "Working directory: $(pwd)" 
echo "aaaa"

databasename=${paramlist[0]}
tablename=${paramlist[1]}
table=$tablename.bakg

echo -e "" >> "$databasename/$table" # sh çalıştığında bir alt satıra geçmesi için

for ((i=2; i<${#paramlist[@]};i++));do
  echo -n "${paramlist[$i]} "
done

for ((i=2; i<${#paramlist[@]};i++));do
  echo -n "${paramlist[$i]} " >> "$databasename/$table"
done
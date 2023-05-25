#!/bin/bash

paramlist=("$@")

databasename=${paramlist[0]}
tablename=${paramlist[1]}

if [ ! -d "$databasename" ]; then
  echo "Database bulunamadi..."
  exit 1
fi

table=$tablename.bakg
touch $databasename/$table


for ((i=2; i<${#paramlist[@]};i++));do
  echo -n "${paramlist[$i]} " >> "$databasename/$table"
done

# sonda kalan boşluğu silme
sed -i 's/ $//' "$databasename/$table"
echo >> "$databasename/$table"


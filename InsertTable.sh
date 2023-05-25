#!/bin/bash

#paramlist=("$@")

#databasename=${paramlist[0]}
#tablename=${paramlist[1]}
#table=$tablename.bakg

#echo "aaaa"

#echo -e "" >> "$databasename/$table" # sh çalıştığında bir alt satıra geçmesi için

#for ((i=2; i<${#paramlist[@]};i++));do
  #echo -n "${paramlist[$i]} "
#done

#for ((i=2; i<${#paramlist[@]};i++));do
  #echo -n "${paramlist[$i]} " >> "$databasename/$table"
#done

paramlist=("$@")
databasename="${paramlist[0]}"
tablename="${paramlist[1]}"
table="$tablename.bakg"

#echo >> "$databasename/$table" # sh çalıştığında bir alt satıra geçmesi için

for ((i=2; i<${#paramlist[@]}; i++)); do
  echo -n "${paramlist[$i]} " >> "$databasename/$table"
done

echo >> "$databasename/$table"  # Eklenen parametrelerden sonra bir boş satır daha ekleniyor

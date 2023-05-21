#!/bin/bash

paramlist=("$@")

databasename=${paramlist[0]}
tablename=${paramlist[1]}

# Gelen parametreden sayi kadar değişken oluşturma
for par in "$sayi";
do
    eval "param$i=$par"
done


# Değer ataması yapma
for ((i=2; i<${#paramlist[@]}; i++)); do
  eval "param$i=\"${paramlist[$i]}\""
done

table=$tablename.txt
touch $databasename/$table


for ((i=2; i<${#paramlist[@]};i++));do
  echo -n "${paramlist[$i]} " >> "$databasename/$table"
done

# sonda kalan boşluğu silme
sed -i 's/ $//' "$databasename/$table"


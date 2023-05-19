#!/bin/bash

paramlist=("$@")

tablename=${paramlist[0]}


# Gelen parametreden sayi kadar değişken oluşturma
for par in "$sayi";
do
    eval "param$i=$par"
done


# Değer ataması yapma
for ((i=1; i<${#paramlist[@]}; i++)); do
  eval "param$i=\"${paramlist[$i]}\""
done

table=$tablename.txt
touch $table


for ((i=1; i<${#paramlist[@]};i++));do
  echo -n "${paramlist[$i]} " >> "$table"
done

sed -i 's/ $//' "$table"


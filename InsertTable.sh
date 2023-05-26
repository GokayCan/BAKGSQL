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

#elleşmeyin buralara yarın şov yapcam burda
paramlist=("$@")
vsayac=0
pList=()
vList=()
tList=()
sList=()

databasename="${paramlist[0]}"
tablename="${paramlist[1]}"
table="$tablename.bakg"

file="$database/$table"

read -r ilk_satir < "$file"

tList=($ilk_satir)

for parametre in "${parametreler[@]}"; do
  if [[ $parametre == */* ]]; then
    ilk_kisim="${parametre%%/*}"
    ikinci_kisim="${parametre#*/}"

    pList+=("$ilk_kisim")
    vList+=("$ikinci_kisim")
  fi
done

for ((i=0; i<${#tList[@]}; i++)); do
  for ((j=0; j<${#vList[@]}; j++)); do
    if [[ "${tList[$i]}" == "${vList[$j]}" ]]; then
      sList+="${tList[$i]}"
    else
      sList+="nu"
    fi
  done
done


for ((i=0;i<${#tList[@]}; i++)); do
  if [[ "${tList[$i]}" == "${sList[$j]}" ]]; then
    ehco -n "${vList[$sayac]}" >> "$file"
    (($sayac++))
  else
    echo -n ", ," >> "$file"
  fi
done
#elleşmeyin buralara yarın şov yapcam burda
#echo >> "$databasename/$table" # sh çalıştığında bir alt satıra geçmesi için


echo >> "$file"  # Eklenen parametrelerden sonra bir boş satır daha ekleniyor

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


file="$databasename/$table"

ilk_satir=$(head -n 1 "$file" | tr -d '\r')  # İlk satırı okuma ve '\r' karakterlerini silme

IFS=',' read -ra parcalar <<< "$ilk_satir"  # İlk satırı parçalara ayırma

for parca in "${parcalar[@]}"; do
    parca=$(echo "$parca" | sed 's/^[[:space:]]*//; s/[[:space:]]*$//')  # Başındaki ve sonundaki boşlukları kaldırma
    if [[ -n "$parca" ]]; then  # Parça boş değilse tList'e ekleme
        tList+=(",$parca,")
    fi
done

#printf '%s\n' "${tList[@]}"

#plist vlist doldurma başlangıç
underIndex=""

for ((i = 2; i < ${#paramlist[@]}; i++)); do
  if [[ "${paramlist[i]}" == *_* ]]; then
    underIndex="$underIndex $i"
    break
  fi

done

sayac=0

for ((i = 2; i<$underIndex;i++)); do
  pList[$sayac]="${paramlist[$i]}"
  ((sayac++))
done

temp_array=("${pList[@]}")
willdelete=()
sayac=0
for ((i=0;i< ${#pList[@]};i++)); do
  element="${temp_array[i]}"
  last="${element: -1}"
  if [ "$last" != "," ]; then
    willdelete[$sayac]=$i
    ((sayac++))
    next=$((i+1))
    combined="${temp_array[i]} ${temp_array[i+1]}"
    #temp_array[$i]="$combined"
    temp_array[$next]="$combined"
  fi
done

for ((i=0;i< ${#willdelete[@]};i++)); do
  unset temp_array["${willdelete[i]}"]
done

pList=("${temp_array[@]}")


sayac=0
for ((i=$underIndex+1; i < ${#paramlist[@]}; i++)); do
  vList[$sayac]="${paramlist[$i]}"
  ((sayac++))
done

temp_array=("${vList[@]}")
willdelete=()
sayac=0
for ((i=0;i< ${#vList[@]};i++)); do
  element="${temp_array[i]}"
  last="${element: -1}"
  if [ "$last" != "," ]; then
    willdelete[$sayac]=$i
    ((sayac++))
    next=$((i+1))
    combined="${temp_array[i]} ${temp_array[i+1]}"
    #temp_array[$i]="$combined"
    temp_array[$next]="$combined"
  fi
done

for ((i=0;i< ${#willdelete[@]};i++)); do
  unset temp_array["${willdelete[i]}"]
done

vList=("${temp_array[@]}")

#insert into alperen/kisi adi,soyadi,tel no, values ,aaa,bbb,3425 2134,
#echo '------------------------'
#printf '%s\n' "${tList[@]}"
#echo '------------------------'
#printf '%s\n' "${pList[@]}"
#echo '------------------------'
#printf '%s\n' "${vList[@]}"
# plist vlist doldurma son

flag=0
for ((i=0; i<${#tList[@]}; i++)); do
  for ((j=0; j<${#pList[@]}; j++)); do
    if [[ "${tList[$i]}" = "${pList[$j]}" ]]; then
      sList[$i]="${pList[$j]}"
      flag=1
    fi
  done
  if [[ $flag = 0 ]]; then
    sList[$i]="nu"
  else  
    flag=0
  fi
done

echo '------------------------'
printf '%s\n' "${sList[@]}"
sayac=0
for ((i=0;i<${#tList[@]}; i++)); do
  if [[ "${tList[$i]}" = "${sList[$i]}" ]]; then
    echo -n "${vList[$sayac]} " >> "$file"
    ((sayac++))
  else
    echo -n ", , " >> "$file"
  fi
done
#elleşmeyin buralara yarın şov yapcam burda
#echo >> "$databasename/$table" # sh çalıştığında bir alt satıra geçmesi için


echo >> "$file"  # Eklenen parametrelerden sonra bir boş satır daha ekleniyor

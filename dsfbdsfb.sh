for ((i = 2; i < ${#param_array[@]}; i++)); do
  param="${param_array[i]}"
  param=${param%,}
  param=${param#*,}
  
  # _ karakterinden önceki parametreler pList'e eklenir, sonraki parametreler vList'e eklenir
  if [[ "$param" == "_" ]]; then
    addToPList=false
  elif [[ $addToPList == true ]]; then
    pList+=("$param")
  else
    vList+=("$param")
  fi
  
  # Boşluk karakteri kontrolü
  if [[ "$param" =~ [[:space:]] ]]; then
    addToPList=true
  else
    addToPList=false
  fi
done
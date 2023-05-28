#!/bin/sh


directory="$1"

if [ ! -d "$directory" ]; then
  echo "Uyarı: Database bulunamadı: $directory"
  echo
  exit 1
fi


if [ "$(ls -A "$directory")" ]; then

  read -p "Dizin dolu. İçeriğiyle birlikte silinsin mi? (Y/N): " choice
  
  if [ "$choice" = "Y" ] || [ "$choice" = "y" ]; then
    rm -r "$directory"
    echo "Database başarıyla silindi."

  else
    echo "İşlem iptal edildi, database silinmedi."
  fi

else
  rm -r "$directory"
  echo "Database başarıyla silindi."
fi
#!/bin/sh

#directory="$1"
#filename="$2"

#filepath="$directory/$filename"

filepath="$1"
fileEx=".bakg"

if [ ! -f "$filepath$fileEx" ]; then
  echo "Uyarı: Tablo bulunamadı: $filepath"
  echo
  exit 1
fi

read -p "Dosya mevcut. Silinsin mi? (Y/N): " choice

if [ "$choice" = "Y" ] || [ "$choice" = "y" ]; then
  rm "$filepath$fileEx"
  echo "Tablo başarıyla silindi."

else
  echo "İşlem iptal edildi, tablo silinmedi."
fi
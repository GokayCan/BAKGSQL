#!/bin/sh

directory=$(dirname "$0")  # Listelemek istediğiniz dizinin yolunu burada belirtin

# Dizin kontrolü
if [ ! -d "$directory" ]; then
  echo "Databaseler bulunamadı: $directory"
  exit 1
fi

# Dizin içerisindeki tüm dizinleri listeleme
for dir in "$directory"/*/; do
  dirname=$(basename "$dir")
  printf "%s " "$dirname"
done
echo
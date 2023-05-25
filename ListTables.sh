#!/bin/sh

directory="$1"  # Listelemek istediğiniz dizinin yolunu burada belirtin

# Dizin kontrolü
if [ ! -d "$directory" ]; then
  echo "Database bulunamadı: $directory"
  exit 1
fi

# Dizin içerisindeki tüm .txt dosyalarını listeleme
for file in "$directory"/*.bakg; do
  filename=$(basename "$file")
  filename_without_extension="${filename%.*}"
  printf "%s " "$filename_without_extension"
done
echo
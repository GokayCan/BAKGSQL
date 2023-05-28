#!/bin/bash

input="$@"
log_file="tablo.log"

# Tablo log dosyasının var olup olmadığını kontrol et
if [ ! -f "$log_file" ]; then
  touch "$log_file"
fi

# Tabloyu güncelle
echo "$input" >> "$log_file"

#!/bin/bash

input="$@"
log_file="tablo.log"
timestamp=$(date +"%Y-%m-%d %H:%M:%S")

# Tablo log dosyasının var olup olmadığını kontrol et
if [ ! -f "$log_file" ]; then
  touch "$log_file"
fi

# Tabloyu güncelle
echo "[$timestamp] --- $input" >> "$log_file"

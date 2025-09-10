#!/bin/bash

# Эталонный файл после расшифровки оригинального output.enc
REFERENCE="decrypted.txt"

# Проверка, что эталонный файл существует
if [ ! -f "$REFERENCE" ]; then
  echo "[!] Эталонный файл $REFERENCE не найден!"
  exit 1
fi

echo "[*] Эталонный хеш:"
sha256sum "$REFERENCE"
echo

# Сравнение хешей изменённых файлов
for file in decrypted_*.txt; do
  if [ "$file" != "$REFERENCE" ]; then
    echo "[*] Проверка файла: $file"
    sha256sum "$file"

    REF_HASH=$(sha256sum "$REFERENCE" | awk '{print $1}')
    FILE_HASH=$(sha256sum "$file" | awk '{print $1}')

    if [ "$REF_HASH" = "$FILE_HASH" ]; then
      echo " -> ✅ Совпадает с эталоном"
    else
      echo " -> ❌ Отличается от эталона"
    fi
    echo
  fi
done

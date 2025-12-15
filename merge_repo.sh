#!/bin/bash

# Nazwa pliku wynikowego
OUTPUT_FILE="full_code.txt"

# Wyczyść plik wynikowy jeśli istnieje
> "$OUTPUT_FILE"

echo "Generowanie pliku $OUTPUT_FILE..."

# Lista folderów do ignorowania (możesz dopisać własne)
# -prune zapobiega wchodzeniu do tych katalogów
find . \
    -type d \( \
        -name ".git" -o \
        -name "node_modules" -o \
        -name "venv" -o \
        -name "__pycache__" -o \
        -name "dist" -o \
        -name "build" -o \
        -name "RTE" -o \
        -name "Listings" -o \
        -name "Objects" -o \
        -name "vendor" \
    \) -prune \
    -o \
    -type f \( \
        ! -name "*lock*" \
        ! -name "*.png" \
        ! -name "*.jpg" \
        ! -name "*.jpeg" \
        ! -name "*.gif" \
        ! -name "*.svg" \
        ! -name "*.exe" \
        ! -name "*.bin" \
        ! -name "*.hpp" \
        ! -name "*.txt" \
        ! -name "$OUTPUT_FILE" \
        ! -name "merge_repo.sh" \
        ! -name "RC_Car.uvguix.kubak" \
        ! -name "RC_Car.uvoptx" \
        ! -name "RC_Car.uvprojx" \
        ! -name "MKL05Z4.h" \
        ! -name "README.md" \
        ! -name "milestones.md" \
        ! -name "RC_Car.uvoprojx" \
        ! -name "gitignore" \
    \) \
    -print0 | while IFS= read -r -d '' file; do
        
        # Sprawdzenie czy plik jest tekstowy (pomija binarki, jeśli find przepuścił)
        if grep -Iq . "$file"; then
            echo "Przetwarzanie: $file"
            
            # Nagłówek dla AI, żeby wiedziało jaki to plik
            echo "==================================================" >> "$OUTPUT_FILE"
            echo "FILE PATH: $file" >> "$OUTPUT_FILE"
            echo "==================================================" >> "$OUTPUT_FILE"
            
            # Zawartość pliku
            cat "$file" >> "$OUTPUT_FILE"
            
            # Odstęp
            echo -e "\n\n" >> "$OUTPUT_FILE"
        fi
done

echo "Gotowe! Cały kod znajduje się w pliku: $OUTPUT_FILE"

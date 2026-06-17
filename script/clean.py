#!/usr/bin/env python3

import sys
from pathlib import Path

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} filename.txt")
        sys.exit(1)

    input_file = Path(sys.argv[1])

    if not input_file.exists():
        print(f"Erreur : fichier introuvable : {input_file}")
        sys.exit(1)

    output_file = input_file.with_name(f"{input_file.stem}_clean{input_file.suffix}")

    with open(input_file, "r", encoding="utf-8") as fin, \
         open(output_file, "w", encoding="utf-8") as fout:

        for line in fin:
            stripped = line.strip()

            # Conserver uniquement les lignes représentant un entier signé
            try:
                int(stripped)
                fout.write(stripped + "\n")
            except ValueError:
                pass

    print(f"Fichier créé : {output_file}")

if __name__ == "__main__":
    main()
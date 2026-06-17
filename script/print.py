#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} fichier.txt")
    sys.exit(1)

with open(sys.argv[1], "r", encoding="utf-8") as f:
    for line in f:
        parts = line.strip().split()

        if len(parts) == 2 and parts[1] == "**":
            print(parts[0])
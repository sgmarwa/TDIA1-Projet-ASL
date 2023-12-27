#!/bin/bash

# Vérifiez le nombre d'arguments
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Changez le répertoire
cd "$1" || exit 1

# Exécutez le shell interactif pour que le changement persiste
bash

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ECHEC 1
#define SUCCES 0

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "La formule correcte est : %s <source> <destination>\n", argv[0]);
        exit(ECHEC);
    }

    const char *source = argv[1];
    const char *destination = argv[2];

    if (rename(source, destination) != 0) {
        perror("Erreur lors du déplacement du fichier");
        exit(ECHEC);
    }

    printf("Déplacement réussi de %s vers %s\n", source, destination);

    return SUCCES;
}


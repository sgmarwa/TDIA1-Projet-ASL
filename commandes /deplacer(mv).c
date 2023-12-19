#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "la formule correcte est : %s <source> <destination>\n", argv[0]);
        exit(ECHEC);
    }

    const char *source = argv[1];
    const char *destination = argv[2];

    if (rename(source, destination) != 0) {
        perror("Erreur lors du déplacement du fichier");
        exit(EXIT_FAILURE);
    }

    printf("Déplacement réussi de %s vers %s\n", source, destination);

    return SUCCES;
}

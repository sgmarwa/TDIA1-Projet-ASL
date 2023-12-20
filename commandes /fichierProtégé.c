#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 50
#define FILENAME "fichier_protecte.txt"

void createProtectedFile() {
    int fd;
    char password[MAX_PASSWORD_LENGTH];

    printf("Entrez le mot de passe pour le fichier : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Supprimer le retour à la ligne

    fd = open(FILENAME, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }

    write(fd, password, strlen(password));
    close(fd);

    printf("Fichier créé avec succès.\n");
}

void unlockFile() {
    int fd;
    char storedPassword[MAX_PASSWORD_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];

    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    read(fd, storedPassword, sizeof(storedPassword));
    close(fd);

    printf("Entrez le mot de passe pour accéder au fichier : ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0'; // Supprimer le retour à la ligne

    if (strcmp(storedPassword, enteredPassword) == 0) {
        printf("Mot de passe correct. Vous pouvez accéder au fichier.\n");
        // Ajoutez ici le code pour effectuer des opérations sur le fichier, par exemple cat, nano, etc.
    } else {
        printf("Mot de passe incorrect. Accès refusé.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "La formule correcte est : %s <create/unlock>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "create") == 0) {
        createProtectedFile();
    } else if (strcmp(argv[1], "unlock") == 0) {
        unlockFile();
    } else {
        fprintf(stderr, "Commande non reconnue. Utilisez 'create' pour créer un fichier ou 'unlock' pour le déverrouiller.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

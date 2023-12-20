#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 50

void creerFichierProtege(const char *nomFichier) {
    int fd;
    char motDePasse[MAX_PASSWORD_LENGTH];

    printf("Entrez le mot de passe pour le fichier '%s' : ", nomFichier);
    fgets(motDePasse, sizeof(motDePasse), stdin);
    motDePasse[strcspn(motDePasse, "\n")] = '\0'; // Supprimer le retour à la ligne

    fd = open(nomFichier, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }

    write(fd, motDePasse, strlen(motDePasse));
    close(fd);

    printf("Fichier créé avec succès.\n");
}

void deverouillerFichier(const char *nomFichier) {
    int fd;
    char motDePasseStocke[MAX_PASSWORD_LENGTH];
    char motDePasseEntree[MAX_PASSWORD_LENGTH];

    fd = open(nomFichier, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    read(fd, motDePasseStocke, sizeof(motDePasseStocke));
    close(fd);

    printf("Entrez le mot de passe pour accéder au fichier '%s' : ", nomFichier);
    fgets(motDePasseEntree, sizeof(motDePasseEntree), stdin);
    motDePasseEntree[strcspn(motDePasseEntree, "\n")] = '\0'; // Supprimer le retour à la ligne

    if (strcmp(motDePasseStocke, motDePasseEntree) == 0) {
        printf("Mot de passe correct. Vous pouvez accéder au fichier '%s'.\n", nomFichier);
        // Ajoutez ici le code pour effectuer des opérations sur le fichier, par exemple cat, nano, etc.
    } else {
        printf("Mot de passe incorrect. Accès refusé.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "La formule correcte est : %s <creer/deverouiller> <nomFichier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *commande = argv[1];
    const char *nomFichier = argv[2];

    if (strcmp(commande, "creer") == 0) {
        creerFichierProtege(nomFichier);
    } else if (strcmp(commande, "deverouiller") == 0) {
        deverouillerFichier(nomFichier);
    } else {
        fprintf(stderr, "Commande non reconnue. Utilisez 'creer' pour créer un fichier ou 'deverouiller' pour le déverrouiller.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

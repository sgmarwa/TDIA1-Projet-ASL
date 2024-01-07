#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h> // Pour close
#include <time.h>   // Pour time
//#include "loggin.h"
#include "usr.h"
char utilisateur[50];
int mytouch(const char *filename) {
/*FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);*/
    int fd;
    struct utimbuf new_times;

    // Ouvre le fichier en lecture/écriture s'il existe, sinon le crée
    fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }
  //  logMessage2("DEBUG","utilisation du commande <creer>",utilisateur);
    // Ferme le fichier
    close(fd);

    // Obtient l'heure actuelle
    new_times.actime = time(NULL);
    new_times.modtime = new_times.actime;

    // Met à jour l'horodatage d'accès et de modification du fichier
    if (utime(filename, &new_times) < 0) {
        perror("utime");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    if (mytouch(argv[1]) != 0) {
        printf("Erreur lors de la création/modification du fichier.\n");
        return 1;
    }

    printf("Fichier '%s' créé ou mis à jour avec succès.\n", argv[1]);
    return 0;
}

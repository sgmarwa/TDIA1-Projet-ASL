#include <stdio.h>
#include <stdlib.h>
//#include "loggin.h"
#include "usr.h"
#include "permissions.h"
//char utilisateur[50];
int main(int argc, char *argv[]) {
    FILE *source_file, *destination_file;
    char ch;
/*FILE *f3 = fopen("connecteur.txt", "r");
    if (f3== NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);*/
    // Vérifie le nombre d'arguments
    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    int p1,p2,val=0;//variables pour les permissions
    p1=permission(argv[1],val);
    if(p1==0)
            return 1;
    else if(p1==3)
            val=1;
            p2=permission(argv[2],val);
            if(p2==0)
                    return 1;
    // Ouvre le fichier source en lecture
    source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
// logMessage2("DEBUG","utilisation du commande <copy>: fichier non trouvé",utilisateur );
        printf("Impossible d'ouvrir le fichier source '%s'\n", argv[1]);
        return 1;
    }

    // Ouvre le fichier destination en écriture
    destination_file = fopen(argv[2], "w");
    if (destination_file == NULL) {
        printf("Impossible d'ouvrir le fichier destination '%s'\n", argv[2]);
        fclose(source_file);
        return 1;
    }

    // Copie le contenu du fichier source vers le fichier destination
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, destination_file);
    }

    // Ferme les fichiers
    fclose(source_file);
    fclose(destination_file);

    printf("Le fichier '%s' a été copié vers '%s'\n", argv[1], argv[2]);
  //   logMessage2("DEBUG","utilisation du commande <copy>: ",utilisateur);
  //  fclose(f3);
    return 0;
}

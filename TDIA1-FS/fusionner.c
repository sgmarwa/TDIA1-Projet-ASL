#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "loggin.h"
#include "usr.h"
#include "permissions.h"
#define SUCCES 0
#define ECHEC 1
// char utilisateur[50];
int main(int argc, char *argv[]) {
 /*   FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3); */
    if (argc != 4) {
        fprintf(stderr, "La formule correcte est : %s <source1> <source2> <destination>\n", argv[0]);
        exit(ECHEC);
    }

    const char *source1 = argv[1];
    const char *source2 = argv[2];
    const char *destination = argv[3];

    // Ouverture du premier fichier en lecture
    FILE *fichier1 = fopen(source1, "r");
    if (fichier1 == NULL) {
        perror("Erreur lors de l'ouverture du premier fichier");
        exit(ECHEC);
    }

    // Ouverture du deuxième fichier en lecture
    FILE *fichier2 = fopen(source2, "r");
    if (fichier2 == NULL) {
        perror("Erreur lors de l'ouverture du deuxième fichier");
        fclose(fichier1);
        exit(ECHEC);
    }
//cotés permissions:-------
 int val=0;
    int p1,p2;
    p1=permission(source1,val);
    if(p1==0)
	    return 1;
    else if(p1==3)
	    val=1;
	    p2=permission(source2,val);
	    if(p2==0)
		    return 1;
	    else if(p2==3)
		    val=1;
		    if(permission(destination,val)==0)
                        return 1;
 //------------
    // Ouverture du fichier de sortie en écriture
    FILE *fichierSortie = fopen(destination, "w");
    if (fichierSortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        fclose(fichier1);
        fclose(fichier2);
        exit(ECHEC);
    }

    // Fusion des fichiers
    int caractere;
    while ((caractere = fgetc(fichier1)) != EOF) {
        fputc(caractere, fichierSortie);
    }

    while ((caractere = fgetc(fichier2)) != EOF) {
        fputc(caractere, fichierSortie);
    }

    // Fermeture des fichiers
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichierSortie);
  //  logMessage2("DEBUG","utilisation du commande <fusionner>: fichier non trouvé",utilisateur);
    printf("Fusion réussie de %s et %s vers %s\n", source1, source2, destination);

    return SUCCES;
}

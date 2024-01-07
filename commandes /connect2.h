#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
//#include "loggin.h"
#include "user.h"
//#include "chdf.h"
int hashPassword1(usr us, char *m_passe) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, us.mot_de_passe, strlen(us.mot_de_passe));

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    char hash_string[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    return strcmp(m_passe, hash_string) == 0;
}

/*int connecter(usr us) {
      char utilisateur[50];
    strcpy(utilisateur, us.nom_uti);
FILE *f1 = fopen("connecteur.txt", "w");
    if (f1 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }*/

    char chemin_vers_fichier_utilisateurs[PATH_MAX];
        construireCheminDuFichierUsers(chemin_vers_fichier_utilisateurs);
    FILE *f = fopen(chemin_vers_fichier_utilisateurs, "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    char ligne[200];
    char mot_passe[300];
    char partie_gauche[300];

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (sscanf(ligne, "%[^:]:%s", partie_gauche, mot_passe) == 2) {
            if (strcmp(us.nom_uti, partie_gauche) == 0) {
                if (hashPassword1(us, mot_passe)) {
                    fclose(f);
//logMessage("INFO","authentification réussite ",utilisateur);
//fprintf(f1,"%s",us.nom_uti);
                    return 1;
                } else {
                    fclose(f);
//logMessage("ERROR","FAILED TO CONNECT -->mot de passe erroné",utilisateur);

                    return 0;
                }
            }
        }
    }

    fclose(f);
//logMessage("ERROR","FAILED TO CONNECT -->nom utilisateur n'existe pas ",utilisateur);
    return 0;
}

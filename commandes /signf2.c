#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <limits.h>
#include "chdf.h"
#include "user.h"
// Structure pour stocker les informations de l'utilisateur
/*typedef struct {
    char nom_uti[100];
    char mot_de_passe[100];
} usr;*/
// Fonction pour hacher le mot de passe et l'ajouter dans le fichier
void hashPassword(usr us) {
	char chemin_vers_fichier_Users[PATH_MAX];
	construireCheminDuFichierUsers(chemin_vers_fichier_Users);
    FILE *fb = fopen(chemin_vers_fichier_Users, "a+");
    if (fb == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        perror("Erreur lors de l'initialisation du hachage");
        fclose(fb);
        return;
    }

    SHA256_Update(&sha256, us.mot_de_passe, strlen(us.mot_de_passe));

    // Stocker le hachage dans un tableau de caractères
    unsigned char hash[SHA256_DIGEST_LENGTH];
    if (!SHA256_Final(hash, &sha256)) {
        perror("Erreur lors de la finalisation du hachage");
        fclose(fb);
        return;
    }
    // Écrire dans le fichier avec le format "nom_utilisateur:mot_de_passe_haché"
    fprintf(fb, "%s:", us.nom_uti);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(fb, "%02x", hash[i]);
    }
    fprintf(fb, "\n");
    fclose(fb);
}
// Fonction pour hacher le mot de passe et le comparer
int hashPassword1(usr us, char *m_passe) {
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        perror("Erreur lors de l'initialisation du hachage");
        return 0;
    }

    SHA256_Update(&sha256, us.mot_de_passe, strlen(us.mot_de_passe));

    // Stocker le hachage dans un tableau de caractères
    unsigned char hash[SHA256_DIGEST_LENGTH];
    if (!SHA256_Final(hash, &sha256)) {
        perror("Erreur lors de la finalisation du hachage");
        return 0;
    }

    // Convertir le hachage en chaîne hexadécimale
    char hash_string[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    // Comparer les hachages
    if (strcmp(m_passe, hash_string) == 0) {
        return 1; // Les hachages correspondent
    } else {
        return 0; // Les hachages ne correspondent pas
    }
}

// Fonction pour supprimer un utilisateur
void supprimerUtilisateur(usr us) {
	char chemin_vers_fichier_Users[PATH_MAX];
	construireCheminDuFichierUsers(chemin_vers_fichier_Users);
    FILE *f = fopen(chemin_vers_fichier_Users, "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int mot_de_passe_correct = 0;
    char chemin_vers_fichier_Temp[PATH_MAX];
	construireCheminDuFichierTemp(chemin_vers_fichier_Temp);
    FILE *temp = fopen(chemin_vers_fichier_Temp, "w");
    if (temp == NULL) {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        fclose(f);
        return;
    }

    char ligne[200];
    char mot_passe[300];
char partie_gauche[300];
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (sscanf(ligne, "%[^:]:%s", partie_gauche, mot_passe) == 2) {
            if (strcmp(us.nom_uti, partie_gauche) == 0) {
                mot_de_passe_correct = hashPassword1(us, mot_passe);

                if (!mot_de_passe_correct) {
                    printf("Mot de passe erroné.\n");
                    fclose(f);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            } else {
                fprintf(temp, "%s", ligne);
            }
        }
    }

    fclose(f);
    fclose(temp);

    if (mot_de_passe_correct) {
        remove(chemin_vers_fichier_Users);
        rename(chemin_vers_fichier_Temp, chemin_vers_fichier_Users);
        printf("Utilisateur supprimé avec succès.\n");
    } else {
printf("erreur le nom utilisateur n'existe pas\n");
        remove("temp.txt");
    }
}

// Fonction pour ajouter un nouvel utilisateur
void ajouterUtilisateur(usr us) {
	char chemin_vers_fichier_Users[PATH_MAX];
	construireCheminDuFichierUsers(chemin_vers_fichier_Users);
    FILE *f = fopen(chemin_vers_fichier_Users, "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char partie_gauche[100];
    char ligne[200]; // Ajusté pour gérer des lignes plus longues

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (sscanf(ligne, "%[^:]", partie_gauche) == 1) {
            if (strcmp(us.nom_uti, partie_gauche) == 0) {
                printf("L'utilisateur existe déjà.\n");
                fclose(f);
                return;
            }
        }
    }

    fclose(f);
    hashPassword(us);
    printf("Utilisateur ajouté avec succès.\n");
//jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
	char chemin_vers_repertoire_home2[PATH_MAX];

	construireCheminAbsoluRepHome2(chemin_vers_repertoire_home2);	
    	construireCheminAbsoluRepPersoETRepgroup(chemin_vers_repertoire_home2,us);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erreur : Usage sign -d or -u\n");
        return EXIT_FAILURE;
    }

    if (!strcmp(argv[1], "-u")) {
        usr us;

        printf("Veuillez saisir votre nom utilisateur : ");
        scanf("%s", us.nom_uti);

        printf("Veuillez saisir votre mot de passe : ");
        scanf("%s", us.mot_de_passe);

        ajouterUtilisateur(us);

        return 0;
    } else if (!strcmp(argv[1], "-d")) {
        usr us;

        printf("Veuillez saisir nom utilisateur à supprimer : ");
        scanf("%s", us.nom_uti);

        printf("Veuillez saisir votre mot de passe : ");
        scanf("%s", us.mot_de_passe);

        supprimerUtilisateur(us);

        return 0;
    } else {
        printf("Erreur : veuillez saisir -u pour ajouter utilisateur ou -d pour supprimer\n");
        return EXIT_FAILURE;
    }
}

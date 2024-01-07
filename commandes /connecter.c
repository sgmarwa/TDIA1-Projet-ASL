include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <openssl/sha.h>
//#include "loggin.h"
#include "chdf.h"
#include "usr.h"
#include "connect.h"
#define TAILLE_MAX 100
#define TAILLE_MAX2 100

/*typedef struct {
    char nom_uti[100];
    char mot_de_passe[100];
} usr;*/
/*typedef struct info{
        char sta[7];
        char user[20];
} info;*/
int main(int argc,char **argv) {
    if(argc<2 || argc>2){
                fprintf(stderr, "Usage : %s <path>\n", argv[0]);
                return 1;
        }
usr u;
const char *username=argv[1];
//char specific_path[PATH_MAX]="/home/mohammed2/home2/";
char commande[TAILLE_MAX];
saisir2(&u,username);
char chemin_vers_repertoire_home2[PATH_MAX];
char chemin_vers_fichier_statu[PATH_MAX]; 
/*char chemin_vers_fichier_utilisateurs[PATH_MAX];
        construireCheminDuFichierUsers(chemin_vers_fichier_utilisateurs);*/
if(connecter(u) == 0){
	printf("nom d'utilisateur ou mot de passe inconue");
	return 1;
}
else{
	construireCheminDuFichierStatu(chemin_vers_fichier_statu);
	construireCheminAbsoluRepHome2(chemin_vers_repertoire_home2);
	changeStatut(1, u,chemin_vers_fichier_statu);
	//strncat(chemin_vers_repertoire_home2, u.username, PATH_MAX - strlen(chemin_vers_repertoire_home2) - 1);
	strcat(chemin_vers_repertoire_home2, u.nom_uti);
	
	snprintf(commande, sizeof(commande), "cds.sh %s", chemin_vers_repertoire_home2);
                        // Exécutez la commande avec system
                        system(commande);
}
}

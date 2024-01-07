 #include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <openssl/sha.h>
#define TAILLE_MAX 100
#define TAILLE_MAX2 100
#include "crep.h"
#include "permissions.h"
int main(int argc, char *argv[]) {
    /*const char *chemin_utilisateur = argv[argc - 1];
    if(permission(chemin_utilisateur)==0){
                return EXIT_FAILURE;
    }
    else{*/
    int option;
    int opt_p = 0;
    int opt_m = 0;
    int opt_g = 0;
    int nbop=0;
    mode_t mode = 0777;//le mode par deffaut
    int j;
    char *endptr;
    // Utilisation de getopt pour traiter les options de ligne de commande
    while ((option = getopt(argc, argv, "pmg")) != -1) {
        switch (option) {
            case 'p':{
                opt_p = 1;
                nbop++;}
                break;
            case 'm':{
                opt_m = 1;
                nbop++;}
                break;
	   case 'g':{
                opt_g = 1;
                nbop++;}
                break;
            case '?':
                fprintf(stderr, "Option inconnue '-%c'.\n", optopt);
                return 1;
            default:
                fprintf(stderr, "Utilisation : %s [-m] [-p] fichier\n", argv[0]);
                return 1;
        }
    }
    int i = optind;
    //si l'utilisateur a taper l'optin -m alors il doit entrer en premier parametre après le choix des option le mode de création des dossiers
    if(opt_m == 1){
	    //tester le prochain parametre si c'est un mode valide ou non pour ne pas avoir des erreurs
	    for(j=0;j<3;j++){
		    if(argv[i][j] != '0' && argv[i][j] != '1' && argv[i][j] != '2' && argv[i][j] != '3' && argv[i][j] != '4' && argv[i][j] != '5' && argv[i][j] != '6' && argv[i][j] != '7'){
			    ind:
			    fprintf(stderr, "mode inconnu : '%s' .\n", argv[i]);
			    return 1;//erreur
			} 
    		}
	    if(argv[i][j] != '\0')//depasser 3 chifre
                            goto ind;
	    printf("%s\n",argv[i]);
	    mode = strtol(argv[i], &endptr, 8);//convertire ce premier parametre en mode(octale)
    	    printf("Les permissions sont : %o\n", mode);
    }
    const char *path = argv[argc - 1];
    if(opt_g==1){
    char chemin_vers_repertoire_home2[PATH_MAX];
	construireCheminAbsoluRepHome2(chemin_vers_repertoire_home2);
	strcat(chemin_vers_repertoire_home2,"grouprep/");
	strcat(chemin_vers_repertoire_home2,argv[argc - 1]);
	creerDossier(chemin_vers_repertoire_home2, mode);
    	//goto ind;
	//return 0;
    }
    if(opt_p == 1){	    
	int val1=0;
	//les permissions sont dans la fonction par deffaut:
	creerDossier_p(path, mode, &val1);
	}
    //si l'user n'a pas saisi l'option 'p'
    if(opt_g==0 && opt_p==0){
	    //int val2=0;
	    if(permission(path, 0)==0)
		    return 1;
	    creerDossier(path, mode);
	    return 0;
    }
    return 0;
}

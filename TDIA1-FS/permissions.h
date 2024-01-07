#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <openssl/sha.h>
#include "connect.h"
#include "chdf.h"
#include "usr.h"
#define TAILLE_MAX 100
#define TAILLE_MAX2 100
void listadmin(usr *u,char *fichier_users) {
    FILE* fichier = fopen(fichier_users, "r");  
    if (fichier == NULL) 
        printf("Erreur lors de l'ouverture du fichier users");
    char ligne[TAILLE_MAX];
    if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
        printf("Erreur lors de la lecture du fichier");
        fclose(fichier);}
    if (sscanf(ligne, "%[^:]:%s",u->nom_uti,u->mot_de_passe) != 2) {
        printf("Erreur lors de l'extraction du user_name et du password");
        fclose(fichier);
    }
    fclose(fichier);
 }
//la valeur val c'est pour savoire s'il a executer la commande en tant qu'admin dans linstruction precedente de la commande 
int permission(const char *chemin_utilisateur,int val){
//	const char *chemin_utilisateur = argv[1];
	char chemin_absolu[PATH_MAX];
	usr admin;
	char chemin[PATH_MAX];//recevoire le chemin absolu pour subir les changements
	char mots[20][50];
	int nombreDeMots;//dans le chemin
	info in;//structure qui contient la statut de connection et le nom d'user
	usr u;//structure qui contient le nom d'user et son mdp
	char commande[100];
	char chemin_vers_fichier_statut[PATH_MAX];
	char chemin_vers_fichier_utilisateurs[PATH_MAX];
	char choix;
	int test=0;
	// obtenir le chemin absolu:fonction predifini:
	
	//verifier_existance(chemin_utilisateur) si il n'existe pas on creer un repertoire sous le nom de ce chemin après on le suprime
    if(verifier_existance(chemin_utilisateur)!=1){
		    mkdir(chemin_utilisateur,0777);
		    test=1;
		    }

    if (realpath(chemin_utilisateur, chemin_absolu) == NULL) {
        perror("Error");
        return EXIT_FAILURE;
    }
    //copier le chemin absolu dans le chemin pour en faire des changements
	strcpy(chemin,chemin_absolu);
	if(test==1)
	rmdir(chemin_utilisateur);
    //changements sur chmin en le divisant:
    diviserCheminEnMots(chemin, mots, &nombreDeMots, "/");
    //extraire le chemin vers le fichier statu et celui vers le fichier utilisateurs:
    construireCheminDuFichierStatu(chemin_vers_fichier_statut);
    construireCheminDuFichierUsers(chemin_vers_fichier_utilisateurs);    
    //passe par le repertoire home2
    //printf("\n%s\n%s\n",chemin_vers_fichier_utilisateurs,chemin_vers_fichier_statut);
    if (strcmp(mots[2],"home2")==0){
             //printf("Le chemin %s passe par le répertoire spécifique %s.\n", chemin_absolu, mots[2]);//----------------------------verification
	//obtenir si il y a un user connecter ou non fichier statut:
	in=getStatut(chemin_vers_fichier_statut);
	//si il y a un user connecter
	if(strcmp(in.sta,"on")==0){
		if(nombreDeMots > 3){
		if (strcmp(mots[3],in.user)==0 || strcmp(mots[3],"grouprep")==0){
		//printf("Le chemin %s passe par le répertoire de l'user connecté %s.\n", chemin_absolu, mots[3]);//-----------------verification
			return 1;//il a la permission de faire ce qu'il veut.
		}
		else{
			//printf("Le chemin %s ne passe pas par le répertoire de l'user connecté %s ni par le repertoir du groupe.\n", chemin_absolu, in.user);//--------------verif
			fprintf(stderr, "permition denied\n");	
			return 0;//n'a pas la permission d'executer la commande
		}
		}else{//nbr_de_mot==2(juste l'home2)
		      //printf("passe par home2 mais ne rentre pas a qulque chose");
			return 1;
		}


	}else{//si la statut est off(aucun user du group n'est connecté):
	       	printf("statoff\n");	       
		fprintf(stderr,"vous devez ce connecter avec la commande : cu <nom de l'utilisateur>\n");
	 	return 0;
	}
    }else{//si l'utilisateur au nom du groupe veut acceder à un autre repertoir sans celui du home1
	if(val != 1){
	    in = getStatut(chemin_vers_fichier_statut);
	//admin = adminlist(chemin_vers_fichier_utilisateurs);
	listadmin(&admin,chemin_vers_fichier_utilisateurs);
	if(strcmp(in.sta,"on") == 0 && strcmp(in.user,admin.nom_uti) != 0){
			printf("vous devez vous connecter comme admin avec la commande cu <nom de l'admin du groupe>\n");
			printf("utiliser la commande comme admin pour une seul fois?[y/n]");
			scanf("%c",&choix);
		switch(choix){
		case 'y':{
			getchar();
			saisir2(&u,admin.nom_uti);
			if(connecter(u) != 1){
                                printf("pass:%s\n",u.mot_de_passe);
				fprintf(stderr, "permition denied\n");
                                return 0;
                        }else{//executer la commande sans changer la statu:
				//printf("pass:%s\n",u.mot_de_passe);
				return 3;
                        }
		}
			 break;
		case 'n':{
				fprintf(stderr, "permition denied\n");                                
				return 0;
		}
			 break;
		}
	}
	else if(strcmp(in.sta,"on") != 0){
		printf("statoff\n");
                fprintf(stderr,"vous devez ce connecter avec la commande : cu <nom de l'utilisateur>\n");
                return 0;
	}else	
		return 1;//c'est l'admin du groupe
    }else return 3;
}
}

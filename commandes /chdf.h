//fichier qui contien des outils:
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "usr.h"
//structure du statut
typedef struct info{
	char sta[7];
	char user[20];
} info;
//structur de userr qui contient l'username et password
/*typedef struct userr{
	char username[20];
	char mdp[20];
} userr;
typedef struct {
    char nom_uti[100];
    char mot_de_passe[100];
} usr;*/
//getStatut:
info getStatut(const char *fichierStatut){
	FILE *f=fopen(fichierStatut,"rb");
	if(f==NULL){
		perror("erreur lors de l'ouverture du fichier de statut");
		exit(1);//sortir avec une erreur
	}
	info in;
	fread(&in,sizeof(info),1,f);
	fclose(f);
	return in;
}
//saisie des infos (username et mdp):------------------------------------------------------------
/*void saisir(usr *u){
	printf("username:");
	fgets(u->nom_uti,20,stdin);
	// Supprimer le caractere de nouvelle ligne ajouter par fgets
    	if (u->nom_uti[strlen(u->nom_uti) - 1] == '\n') {
        	u->nom_uti[strlen(u->nom_uti) - 1] = '\0';
    	}
	printf("password:");
	fgets(u->mot_de_passe,strlen(u->mot_de_passe),stdin);
	// Supprimer le caractÃšre de nouvelle ligne ajoutÃ© par fgets
        if (u->mot_de_passe[strlen(u->mot_de_passe) - 1] == '\n') {
                u->mot_de_passe[strlen(u->mot_de_passe) - 1] = '\0';
        }

}*/
//saisir2:-----------------------------------------------------------------------------------
/*void saisir2(usr *u,const char *nom_user_a_connecter){
        strcpy(u->nom_uti,nom_user_a_connecter);
	printf("username:%s\n",u->nom_uti);
	
        printf("password:");
        fgets(u->mot_de_passe,strlen(u->mot_de_passe),stdin);
        // Supprimer le caractÃšre de nouvelle ligne ajoutÃ© par fgets
        if (u->mot_de_passe[strlen(u->mot_de_passe) - 1] == '\n') {
                u->mot_de_passe[strlen(u->mot_de_passe) - 1] = '\0';
        }
}*/
/*void saisir2(usr *u, const char *nom_user_a_connecter) {
    strcpy(u->nom_uti, nom_user_a_connecter);

    printf("username: %s\n", u->nom_uti);

    printf("password: ");

    fgets(u->mot_de_passe, sizeof(u->mot_de_passe), stdin);

    // Supprimer le caractÃšre de nouvelle ligne ajoutÃ© par fgets
    size_t len = strlen(u->mot_de_passe);
    if (len > 0 && u->mot_de_passe[len - 1] == '\n') {
        u->mot_de_passe[len - 1] = '\0';
    }
}*/
void saisir(usr *u){
        printf("username:");
        fgets(u->nom_uti,20,stdin);
        // Supprimer le caractere de nouvelle ligne ajouter par fgets
        if (u->nom_uti[strlen(u->nom_uti) - 1] == '\n') {
                u->nom_uti[strlen(u->nom_uti) - 1] = '\0';
        }
        char *password = getpass("password: ");
        strcpy(u->mot_de_passe,password);
        //printf("password:");
        //fgets(u->mot_de_passe,strlen(u->mot_de_passe),stdin);
        // Supprimer le caractÃšre de nouvelle ligne ajoutÃ© par fgets
        //if (u->mot_de_passe[strlen(u->mot_de_passe) - 1] == '\n') {
                //u->mot_de_passe[strlen(u->mot_de_passe) - 1] = '\0';
}
void saisir2(usr *u, const char *nom_user_a_connecter) {
    strcpy(u->nom_uti, nom_user_a_connecter);
    char *password = getpass("password: ");
        strcpy(u->mot_de_passe,password);
    // Supprimer le caractÃšre de nouvelle ligne ajoutÃ© par fgets
    size_t len = strlen(u->mot_de_passe);
    if (len > 0 && u->mot_de_passe[len - 1] == '\n') {
        u->mot_de_passe[len - 1] = '\0';
    }
}
//-------------------------------------------------------------------------------------------------------
int changeStatut(int statu, usr u,const char *fichierStatut){
	FILE *f=fopen(fichierStatut,"wb");
        if(f==NULL){
                perror("erreur lors de l'ouverture du fichier de statut");
                exit(1);//sortir avec une erreur
        }
	info in;
        if(statu == 1){
		strcpy(in.sta,"on");
		strcpy(in.user,u.nom_uti);
	}
	else{ 
		strcpy(in.sta, "off");
		in.user[0]='\0';
	}

	if(fwrite(&in,sizeof(info),1,f)!=1){
	       	perror("echec du changement de statu");
		fclose(f);
		return -1;
	}
	fclose(f);
	return 1;
}
//diviser un chemin en mot et fair revenire le nombre de mots contenus dans le chemin:
void diviserCheminEnMots(char *chemin, char mots[][50], int *nombreDeMots, const char *delimiteur) {
    // Utilisation de la fonction strtok pour diviser le chemin en mots
    char *token = strtok(chemin, delimiteur);
    
    *nombreDeMots = 0;
    
    // Boucle pour extraire et stocker chaque mot
    while (token != NULL) {
        strcpy(mots[*nombreDeMots], token);
        (*nombreDeMots)++;
        token = strtok(NULL, delimiteur);
    }
}
//verifier l'existance d'un chemin (fichier/dossier):
int verifier_existance(const char *chemin){
    // Utilisez access pour vérifier l'existence du chemin
    if (access(chemin, F_OK) != -1) {
        return 1;
    } else {
        return -1;
    }
}
//fonction qui construit le chemin vers le repertoire ou on va stocker la statu et l'utilisateurs connectÃ©.
void construireCheminDuFichierStatu(char chemin_vers_fichier_statu[PATH_MAX]){
        char repertoirCourant[PATH_MAX];
        char mots[20][50];
        int nombreDeMots;
        FILE *f=NULL;
        // Obtient le rÃ©pertoire de travail actuel
    if (getcwd(repertoirCourant, sizeof(repertoirCourant)) != NULL) {
    } else {
        perror("Erreur lors de l'obtention du rÃ©pertoire courant");
        exit(1);
    }
    diviserCheminEnMots(repertoirCourant, mots, &nombreDeMots, "/");
        strcpy(chemin_vers_fichier_statu,"/home/");//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user;
    //obtenir le chemin vers les fichiers de la status et de users
    strcat(chemin_vers_fichier_statu,mots[1]);//obtenire le repertoire du groupe dans notre distribution personnalisÃ©e.
    strcat(chemin_vers_fichier_statu,"/secure/");
    //fichier users:
    strcat(chemin_vers_fichier_statu,"statu.bin");
    //ouvrir et fermer le fichier en mode ajout:
    f=fopen(chemin_vers_fichier_statu,"ab");
    if(f==NULL){
            perror("error");
            exit(1);
    }
    fclose(f);
}
//fonction qui construit le chemin vers l'home2 (repertoire ou se trouve les repertoires personnels des utilisateurs):
void construireCheminAbsoluRepHome2(char chemin_vers_repertoire_home2[PATH_MAX]){
        char repertoirCourant[PATH_MAX];
        char mots[20][50];
        int nombreDeMots;
        FILE *f=NULL;
        // Obtient le rÃ©pertoire de travail actuel
    if (getcwd(repertoirCourant, sizeof(repertoirCourant)) != NULL) {
    } else {
        perror("Erreur lors de l'obtention du rÃ©pertoire courant");
        exit(1);
    }
    diviserCheminEnMots(repertoirCourant, mots, &nombreDeMots, "/");
        strcpy(chemin_vers_repertoire_home2,"/home/");//va etre concatener on se basant sur le chemin absolu du rep courant;
    //obtenir le chemin vers les fichiers de la status et de users
    strcat(chemin_vers_repertoire_home2,mots[1]);//obtenire le repertoire du groupe dans notre distribution personnalisÃ©e.
    strcat(chemin_vers_repertoire_home2,"/home2/");
    mkdir(chemin_vers_repertoire_home2,0700);
}
//fonction qui crÃer le repertoire personnel de l'user dÃs quand il s'inscrit;
void construireCheminAbsoluRepPersoETRepgroup(char chemin_vers_repertoire_home2[PATH_MAX],usr u){
	char cheminperso[PATH_MAX];
	char chemingrp[PATH_MAX];
	strcpy(cheminperso,chemin_vers_repertoire_home2);
	strcpy(chemingrp,chemin_vers_repertoire_home2);
	strcat(cheminperso,u.nom_uti);
	strcat(chemingrp,"grouprep");
	mkdir(cheminperso,0700);//il va se crÃer
	mkdir(chemingrp,0700);//si il n'est pas crÃer il va se crÃer sinon il est deja crÃer
}
//fonction qui construit le chemin vers le repertoire ou on va stocker les utilisateur.
void construireCheminDuFichierUsers(char chemin_vers_fichier_utilisateurs[PATH_MAX]){
        char repertoirCourant[PATH_MAX];
        char mots[20][50];
        int nombreDeMots;
        FILE *f=NULL;
        // Obtient le rÃ©pertoire de travail actuel
    if (getcwd(repertoirCourant, sizeof(repertoirCourant)) != NULL) {
    } else {
        perror("Erreur lors de l'obtention du rÃ©pertoire courant");
        exit(1);
    }
    diviserCheminEnMots(repertoirCourant, mots, &nombreDeMots, "/");
        //char chemin_des_informations[PATH_MAX] = "/home/";//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user
        strcpy(chemin_vers_fichier_utilisateurs,"/home/");//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user;
    //obtenir le chemin vers les fichiers de la status et de users
    strcat(chemin_vers_fichier_utilisateurs,mots[1]);//obtenire le repertoire du groupe dans notre distribution personnalisÃ©e.
    strcat(chemin_vers_fichier_utilisateurs,"/secure/");
    mkdir(chemin_vers_fichier_utilisateurs,0700);
    //fichier users:
    strcat(chemin_vers_fichier_utilisateurs,"user.txt");
    //ouvrir et fermer le fichier en mode ajout:
    f=fopen(chemin_vers_fichier_utilisateurs,"a");
    if(f==NULL){
            perror("error");
            exit(1);
    }
    fclose(f);
}
void construireCheminDuFichierTemp(char chemin_vers_fichier_Temp[PATH_MAX]){
        char repertoirCourant[PATH_MAX];
        char mots[20][50];
        int nombreDeMots;
        FILE *f=NULL;
        // Obtient le rÃ©pertoire de travail actuel
    if (getcwd(repertoirCourant, sizeof(repertoirCourant)) != NULL) {
    } else {
        perror("Erreur lors de l'obtention du rÃ©pertoire courant");
        exit(1);
    }
    diviserCheminEnMots(repertoirCourant, mots, &nombreDeMots, "/");
        //char chemin_des_informations[PATH_MAX] = "/home/";//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user
        strcpy(chemin_vers_fichier_Temp,"/home/");//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user;
    //obtenir le chemin vers les fichiers de la status et de users
    strcat(chemin_vers_fichier_Temp,mots[1]);//obtenire le repertoire du groupe dans notre distribution personnalisÃ©e.
    strcat(chemin_vers_fichier_Temp,"/secure/");
    
    strcat(chemin_vers_fichier_Temp,"temp.txt");
    //ouvrir et fermer le fichier en mode ajout:
    f=fopen(chemin_vers_fichier_Temp,"a");
    if(f==NULL){
            perror("error");
            exit(1);
    }
    fclose(f);
}

void creer_ouvrir_FichierDansSecure(char chemin_vers_fichier[PATH_MAX],char *nom_fichier){
	char repertoirCourant[PATH_MAX];
        char mots[20][50];
        int nombreDeMots;
        FILE *f=NULL;
        // Obtient le rÃ©pertoire de travail actuel
    if (getcwd(repertoirCourant, sizeof(repertoirCourant)) != NULL) {
    } else {
        perror("Erreur lors de l'obtention du rÃ©pertoire courant");
        exit(1);
    }
    diviserCheminEnMots(repertoirCourant, mots, &nombreDeMots, "/");
        //char chemin_des_informations[PATH_MAX] = "/home/";//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user
        strcpy(chemin_vers_fichier,"/home/");//va etre concatener aprÃ©s la division du chemin entrÃ© par l'user;
    //obtenir le chemin vers les fichiers de la status et de users
    strcat(chemin_vers_fichier,mots[1]);//obtenire le repertoire du groupe dans notre distribution personnalisÃ©e.
    strcat(chemin_vers_fichier,"/secure/");
    //fichier users:
    strcat(chemin_vers_fichier,nom_fichier);
    //ouvrir et fermer le fichier en mode ajout:
    f=fopen(chemin_vers_fichier,"a");
    if(f==NULL){
            perror("error");
            exit(1);
    }
    fclose(f);
}

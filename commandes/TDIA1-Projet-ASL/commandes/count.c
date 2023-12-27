#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "compter.h"

int main(int argc, char *argv[]) {
    int option;
    int line_count = 0;
    int char_count = 0;
    int word_count = 0;
    int nline,nchar,nword;
    int nbop=0;
    int test = 0;//pour le test si il y a plusieur fichier just pour l'affichage. 
    int test2=0;
    // Utilisation de getopt pour traiter les options de ligne de commande
    while ((option = getopt(argc, argv, "lwc")) != -1) {
        switch (option) {
            case 'l':{
                line_count = 1;
                nbop++;}
		break;
            case 'w':{
                word_count = 1;
                nbop++;}
		break;
            case 'c':{
                char_count = 1;
                nbop++;}
		break;
            case '?':
                fprintf(stderr, "Option inconnue '-%c'.\n", optopt);
                return 1;
            default:
                fprintf(stderr, "Utilisation : %s [-l] [-w] [-c] fichier\n", argv[0]);
                return 1;
        }
    }
        // Traiter chaque fichier spécifié
	if((argc-optind) > 1) 
	   test = 1;
        for (int i = optind; i < argc; i++){
	     char *nmfich = argv[i];
	   if(test == 1)
             printf("%s:\t",nmfich);
	     if((line_count == 0 && char_count == 0 && word_count == 0)||(line_count == 1 && char_count == 1 && word_count == 1)){
	     	test2=1;
		nchar = caracteres(nmfich);
		nline = lines(nmfich);
		nword = words(nmfich);
		printf("lines\twords\tcharacters\n");
		if(test==1)
			printf("\t\t%d\t%d\t%d\n",nline,nword,nchar);
		else printf("%d\t%d\t%d\n",nline,nword,nchar);
		}
	     if(line_count == 1 && test2 != 1){
		nbop--;
		nline = lines(nmfich);
		printf("%d\t",nline);
		if(nbop==0)
		    printf("\n");
		}
	     if(char_count == 1 && test2 != 1){
		nbop--;
                nchar = caracteres(nmfich);
                printf("%d\t",nchar);
		if(nbop==0)
                    printf("\n");
                }
	     if(word_count == 1 && test2 != 1){
		nbop--;
                nword = words(nmfich);
                printf("%d\t",nword);
		if(nbop==0)
                    printf("\n");
                }
	} 
	//coté affichage
	if(line_count != 0 && char_count != 0 && word_count != 0 ||(test==1 && test2!=1)) //&& (test == 1)
	printf("\n");
      return 0;
}

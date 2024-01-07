#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "chdf.h"
int main(){
        char chemin_vers_fichier_statu[PATH_MAX];
        construireCheminDuFichierStatu(chemin_vers_fichier_statu);
        FILE *f=fopen(chemin_vers_fichier_statu,"wb");
        info i;
        strcpy(i.sta,"off");
        i.user[0]='\0';
        if(fwrite(&i,sizeof(info),1,f)){
                printf("statut off\n");
        }
        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <openssl/sha.h>
#include "permissions.h"
int main(int argc,char **argv) {
    if(argc<2 || argc>2){
                fprintf(stderr, "Usage : %s <path>\n", argv[0]);
                return 1;
        }
    	char commande[100];
        const char *chemin_utilisateur = argv[1];
	if(permission(chemin_utilisateur)==0){
		return EXIT_FAILURE;
                        }else{
                                snprintf(commande, sizeof(commande), "cds.sh %s",chemin_utilisateur);
                                        // Exécutez la commande avec system
                                system(commande);
                                //chdir(chemin_absolu);
                        }
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
int creerDossier(const char *path, mode_t mode) {
    if (mkdir(path, mode) == 0) {
        printf("Répertoire créé avec succès : %s\n", path);
        return 0; // Succès
    } else {
        perror("Erreur lors de la création du répertoire");
        return 1; // Échec
    }
}
int creerDossier_p(const char *path, mode_t mode,int *val) {
    // Vérifier si le répertoire existe déjà
    struct stat st;
    int p;//pour la permission
    if (stat(path, &st) == 0) {
        // Le répertoire existe déjà
        return 0;
    }

    // Essayez de créer le répertoire
    if (mkdir(path, mode) == 0) {
        p=permission(path,*val);
    	if(p==0){
	  rmdir(path);//s'il n a pas l'autorisation: suprimer le repertoir qu'on vient de créer
            return 1;
	}
   	 else if(p==3)
            *val=1;
		return 0; // Succès
    } else {
        // Le répertoire n'a pas pu être créé, essayez de créer le répertoire parent
        char *parent_path = strdup(path);
        char *last_slash = strrchr(parent_path, '/');
        if (last_slash != NULL) {
            *last_slash = '\0';
            if (creerDossier_p(parent_path, mode,val) == 0) {
                // Réessayer de créer le répertoire original après la création du parent
                if (mkdir(path, mode) == 0) {
                    printf("Répertoire créé avec succès : %s\n", path);
                    p=permission(path,*val);		    
            	    if(p==0){
          		rmdir(path);//de memme s'il n a pas l'autorisation: suprimer le repertoir qu'on vient de créer mais cette fois sortire du programe
            		return 1;
        	    }
         		else if(p==3)
            		*val=1;
		    free(parent_path);
                    return 0; // Succès
                }
            }
        }
        free(parent_path);
        return 1; // Échec
    }
}


int creerDossier(const char *path, mode_t mode) {
    if (mkdir(path, mode) == 0) {
        printf("Répertoire créé avec succès : %s\n", path);
        return 0; // Succès
    } else {
        perror("Erreur lors de la création du répertoire");
        return 1; // Échec
    }
}
//option -p
int creerDossier_p(const char *path, mode_t mode) {
    // Vérifier si le répertoire existe déjà
    struct stat st;
    if (stat(path, &st) == 0) {
        // Le répertoire existe déjà
        return 0;
    }

    // Essayez de créer le répertoire
    if (mkdir(path, mode) == 0) {
        printf("Répertoire créé avec succès : %s\n", path);
        return 0; // Succès
    } else {
        // Le répertoire n'a pas pu être créé, essayez de créer le répertoire parent
        char *parent_path = strdup(path);
        char *last_slash = strrchr(parent_path, '/');
        if (last_slash != NULL) {
            *last_slash = '\0';
            if (creerDossier_p(parent_path, mode) == 0) {
                // Réessayer de créer le répertoire original après la création du parent
                if (mkdir(path, mode) == 0) {
                    printf("Répertoire créé avec succès : %s\n", path);
                    free(parent_path);
                    return 0; // Succès
                }
            }
        }

        perror("Erreur lors de la création du répertoire");
        free(parent_path);
        return 1; // Échec
    }
}

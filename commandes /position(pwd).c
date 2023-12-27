#include <stdio.h>
#include <unistd.h>
#include "loggin.h"
int main() {
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Position: %s\n", cwd);
        logMessage2("DEBUG","utilisation du commande <position>",usr us );
    } else {
        perror("Erreur lors de la récupération du répertoire actuel");
        return 1;
    }

    return 0;
}

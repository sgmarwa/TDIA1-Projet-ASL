#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>

int mychgrp(const char *filename, const char *groupname) {
    struct group *grp;
    gid_t gid;

    // Obtient l'ID du groupe à partir du nom du groupe
    grp = getgrnam(groupname);
    if (grp == NULL) {
        perror("getgrnam");
        return 1;
    }

    gid = grp->gr_gid;

    // Change le groupe du fichier
    if (chown(filename, -1, gid) == -1) {
        perror("chown");
        return 1;
    }

    printf("Le groupe de '%s' a été changé avec succès.\n", filename);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s filename groupname\n", argv[0]);
        return 1;
    }

    if (mychgrp(argv[1], argv[2]) != 0) {
        printf("Erreur lors du changement de groupe pour '%s'.\n", argv[1]);
        return 1;
    }

    return 0;
}

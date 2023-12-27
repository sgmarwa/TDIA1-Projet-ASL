#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "usr.h"

int notificationCounter = 0;
// Fonction de journalisation
void logMessage(const char *type,const char *message,usr us ) {
// Ouvrir le fichier en mode lecture
    FILE *fichier = fopen("logfile.txt", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    // Compter le nombre de lignes dans le fichier
    int nombreLignes = 0;
    char caractere;

    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '\n') {
            nombreLignes++;
        }
    }
nombreLignes++;
    // Fermer le fichier
    fclose(fichier);
    FILE *logFile = fopen("logfile.txt", "a");
    if (logFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier journal");
    }

    // Obtenir la date et l'heure actuelles
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Formater le message avec la date et l'heure
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Écrire le message dans le fichier journal
    notificationCounter++;
    fprintf(logFile, "[%d] %s :system: [%s] :%s%s\n", nombreLignes,type,timestamp,us.nom_uti ,message);
    // Fermer le fichier journal
    fclose(logFile);
}

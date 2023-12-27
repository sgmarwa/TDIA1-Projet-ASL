#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "usr.h"
char utilisateur[50];
// Fonction de journalisation
void logMessage(const char *type,const char *message,char *uti) {
FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);
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
    fprintf(logFile, "[%d] %s :system: [%s] :%s%s\n", nombreLignes,type,timestamp,uti,message);
    // Fermer le fichier journal
    fclose(logFile);
}
void logMessage2(const char *type,const char *message,char *uti ) {
// Ouvrir le fichier en mode lecture
FILE *f3 = fopen("connecteur.txt", "r");
    if (f3 == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
fgets(utilisateur, sizeof(utilisateur), f3);
fclose(f3);

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
    fprintf(logFile, "[%d] %s :%s: [%s] :%s\n", nombreLignes,type,uti,timestamp,message);
    // Fermer le fichier journal
    fclose(logFile);
}



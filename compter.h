
int caracteres(char *nmfich){
    FILE *f=fopen(nmfich,"r");
    if(f == NULL){
     perror("erreur");
     return -1;
    }
    char c;
    int count=0;
    while((c=fgetc(f))!=EOF){
    count++;
    }
    fclose(f);
    return count;
}
int lines(char *nmfich){
    FILE *f=fopen(nmfich,"r");
    int count=0;
    char c;
    if(f == NULL){
     perror("erreur");
     return -1;
    }
    while((c=(char)fgetc(f))!=EOF){
    if(c == '\n')
    count++;
    }
    fclose(f);
    return count;
}
//#include <ctype.h>
int words (char *nmfich){
    FILE *f=fopen(nmfich,"r");
    if(f == NULL){
     perror("erreur");
     return -1;
    }
    int count=0;
    int inword=0;
    int c;
    while((c=fgetc(f))!=EOF){
    if ( c == ' ' || c == '\t' || c == '\n') {
       //on controle si le caractere precedent est un mot ou juste un espace ou '\n' ou '\t':
         if (inword == 1){
       //si on etait dans un mot on reinitialise inword et on incremente le nombre de mots
            inword = 0;
            count++;
            }
   }
   //si le caractere lu n'est pas un espace alors on est au debut ou a l'interieur ou à la fin du mot
   else
         inword = 1; 
   }
   fclose(f);
   return count;
}

 

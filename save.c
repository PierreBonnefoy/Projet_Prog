#include <stdio.h>
#include <stdlib.h>
#include "partie1.c"

void sauvegarde(point * p, char * nom, int * info){
    int i=0;
    FILE * save;
    /* Création du fichier de sauvegarde */
    save = fopen(nom,"w+");
    fprintf(save,info);

    while (p[i]!=0)
    {
        fprintf(save,p[i]);
        i++;
    }
    
    fclose(save);

} 


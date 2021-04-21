#include <stdio.h>
#include <stdlib.h>
#include "partie1.c"

void sauvegarde_fichier(point * p, char * nom, int * info){
    int i=0;
    FILE * save;
    /* Création du fichier de sauvegarde */
    save = fopen(nom,"w+");
    fprintf(save,"%d %d %d",info[0],info[1],info[2]);

    while (p[i].classe!=0)
    {
        fprintf(save,"%f %f %d",&p[i].x,&p[i].y,&p[i].classe);
        i++;
    }
    
    fclose(save);
} 


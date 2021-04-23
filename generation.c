#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void alea(int size,int nbr,char* nom){
  int i = 0,classe;
  float x,y;
  FILE *save;
  /* Création du fichier de sauvegarde */

  save = fopen(nom, "w+");
  fprintf(save, "%d %d %d\n",size,2,nbr);

  for(i=0;i<size;i++)
  {
    x=(((float)rand()/(float)RAND_MAX)*2)-1;
    y=(((float)rand()/(float)RAND_MAX)*2)-1;
    classe=(rand()%2)+1;
    fprintf(save, "%d %f %f\n",classe,x,y);
  }

  fclose(save);
}
int main(int argc,char** argv){
    int size,classe;
    char *nom;
    if(argc != 4){
        printf("usage: ./generation <taille> <nbrclasse> <nomfichier> !!\n");
        exit (-1);
    }
    size=atoi(argv[1]);
    classe=atoi(argv[2]);
    nom=argv[3];
    srand((unsigned int)time(NULL));
    alea(size,classe,nom);
}
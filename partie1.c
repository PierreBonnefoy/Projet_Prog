#include "partie1.h"
#include <MLV/MLV_all.h>

point * chargement_fichier(char *chemin){
    point *tab;
    int taille,dimension,nbr_classe,i;
    FILE *fichier;
    fichier=fopen(chemin,"r");
    fscanf(fichier,"%d %d %d",&taille,&dimension,&nbr_classe);
    tab=(point*)malloc(taille*sizeof(point));
    if(tab==NULL){
        fprintf(stderr,"erreur allocution pointeur !");
        exit(-1);
    }
    for(i=0;i<taille;i++){
        fscanf(fichier,"%d %f %f",&tab[i].classe,&tab[i].x,&tab[i].y);
    }
    fclose(fichier);
    return tab;
}

int main(int argc,char **argv){
    int i=0;
    point *tab;
    MLV_create_window("Partie 1","partie1",200,200);
    if(argc!=2){
        printf("Erreur : usage ./partie1 <nom_fichier>\n");
        exit(-1);
    }
    tab=chargement_fichier(argv[1]);
    while(tab[i+1].classe!=NULL){
        printf("x = %f y = %f classe = %d\n",tab[i].x,tab[i].y,tab[i].classe);
	if(tab[i].classe==1){
	  MLV_draw_filled_circle((tab[i].x+1)*100,(tab[i].y+1)*100,2,MLV_COLOR_BLUE);
	}
	if(tab[i].classe==2){
	  MLV_draw_filled_circle((tab[i].x+1)*100,(tab[i].y+1)*100,2,MLV_COLOR_RED);
	}
        i++;
	MLV_actualise_window();
    }
    MLV_wait_seconds(10);
    MLV_free_window();
}

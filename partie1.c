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
  int i=0,taille=750;
  int x,y;
    point *tab;
    char *fichier2;
    MLV_create_window("Partie 1","partie1",taille+200,taille);
    MLV_draw_text_box(
                taille+10,80,
                150,20,
                "Load File",
                1,
                MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
                MLV_TEXT_LEFT,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
    );

    MLV_draw_line(taille,1,taille,taille-1,MLV_COLOR_WHITE);
    MLV_actualise_window();
    MLV_wait_mouse(&x,&y);
    if(x>taille+10 && x<taille+10+150 && y>80 && y<100){
      printf("Bouton cliqué\n");
      MLV_wait_input_box(taille+10,10,taille+40,20,MLV_COLOR_RED,MLV_COLOR_GREEN,MLV_COLOR_BLACK,"fichier :",&fichier2);
    }
    tab=chargement_fichier(fichier2);
    free(fichier2);
    MLV_actualise_window();
    while(tab[i+1].classe!=0){
        printf("x = %f y = %f classe = %d\n",tab[i].x,tab[i].y,tab[i].classe);
	if(tab[i].classe==1){
	  MLV_draw_filled_circle((tab[i].x+1)*(taille/2),(tab[i].y+1)*(taille/2),2,MLV_COLOR_BLUE);
	}
	if(tab[i].classe==2){
	  MLV_draw_filled_circle((tab[i].x+1)*(taille/2),(tab[i].y+1)*(taille/2),2,MLV_COLOR_RED);
	}
        i++;
	MLV_actualise_window();
    }
    MLV_wait_seconds(10);
    MLV_free_window();
}

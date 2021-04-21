#ifndef PARTIE1_H
#define PARTIE1_H
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    float x;
    float y;
    int classe;
}point;

point* chargement_fichier(point *tab,char *path);
point* inserer_point(int x,int y,int classe,point *tab,int taille);
void affichage_points(int taille,point *tab);
#endif
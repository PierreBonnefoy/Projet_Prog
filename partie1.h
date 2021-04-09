#ifndef PARTIE1_H
#define PARTIE1_H
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
    float x;
    float y;
    int classe;
}point;

point* chargement_fichier(char *path);
#endif
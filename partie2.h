#ifndef PARTIE2_H
#define PARTIE2_H
#include <stdio.h>
#include <stdlib.h>
#include "partie1.h"

typedef struct noeud *arbre_kd;
struct noeud{
	point noeud;
	arbre_kd pere;
	arbre_kd filsgauche;
	arbre_kd filsdroit;
}noeud;
typedef struct zone
{
	int num;
	point * tab;
}zone;


int est_vide(arbre_kd *a);
arbre_kd inserer(arbre_kd a, point p,int choix );
point * recherche(arbre_kd a,point p,int k,int choix);
point * maj_liste(point *point_tmp,point * liste);
point * point_proche_dans_zone(point *p, zone z_tmp);
int est_dans_zone(point *p, zone z_tmp);

#endif
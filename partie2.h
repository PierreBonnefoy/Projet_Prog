#ifndef PARTIE2_H
#define PARTIE2_H
#include <stdio.h>
#include <stdlib.h>
#include "partie1.h"
typedef point* zone;
typedef struct noeud *arbre_kd;
struct noeud{
	zone zone;
	point noeud;
	arbre_kd pere;
	arbre_kd filsgauche;
	arbre_kd filsdroit;
}noeud;

int est_vide(arbre_kd a);
arbre_kd inserer(arbre_kd a, point p,int choix );
point *recherche(arbre_kd a,point p,int k,point *liste);
point * maj_liste(point point_tmp,point * liste,int k,point kpos);
point point_proche_dans_zone(point p, zone z_tmp);
int est_dans_zone(point p, zone z_tmp);
zone rajoute_point(zone z,point p);
float distance(point p_tmp,point kpos);
#endif
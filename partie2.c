#include "partie2.h"
#include <MLV/MLV_all.h>
#include <math.h>

int est_vide(arbre_kd a)
{
  if (a == NULL)
  {
    return 1;
  }
  return 0;
}

arbre_kd inserer(arbre_kd a, point p, int choix)
{
  if (a == NULL)
  {
    a = (arbre_kd)malloc(sizeof(noeud));
    a->filsgauche = NULL;
    a->filsdroit = NULL;
    a->noeud.x = p.x;
    a->noeud.y = p.y;
    a->noeud.classe = p.classe;

    return a;
  }
  if (choix % 2 == 0)
  {
    if (a->noeud.x < p.x)
    {
      a->filsdroit = inserer(a->filsdroit, p, choix + 1);
      return a;
    }
    else
    {
      a->filsgauche = inserer(a->filsgauche, p, choix + 1);
      return a;
    }
  }
  else
  {
    if (a->noeud.y < p.y)
    {
      a->filsdroit = inserer(a->filsdroit, p, choix + 1);
      return a;
    }
    else
    {
      a->filsgauche = inserer(a->filsgauche, p, choix + 1);
      return a;
    }
  }
}

point *recherche(arbre_kd a, point p, int k)
{
  point *liste;
  liste = (point *)calloc(k, sizeof(point));
  liste = maj_liste(a->noeud, liste);
  if (est_vide(a->filsdroit) && est_vide(a->filsdroit))
  {
    return liste;
  }
  else
  {
    liste = recherche(a->filsgauche, p, k);
    if (est_dans_zone(p,a->filsdroit->zone /* zone associer è fils droit */))
    {
      liste = recherche(a->filsdroit, p, k);
    }
  }
  return liste;
}

point *maj_liste(point p_tmp, point *liste)
{
  int i = 0, j = 0;
  point temp;

  while (liste[i].classe != 0)
  {

    if (liste[i].classe != 0)
    {
      i++;
    }
    else
    {
      liste[i].classe = p_tmp.classe;
      liste[i].x = p_tmp.x;
      liste[i].y = p_tmp.y;
      break;
    }
  }
  for (j = 0; j < i; j++)
  {
    if (fabsf(sqrt(pow((liste[j].x - p_tmp.x), 2) + pow((liste[i].y - p_tmp.y), 2))) > fabsf(sqrt(pow((liste[i].x - p_tmp.x), 2) + pow((liste[i].y - p_tmp.y), 2))))
    {
      temp = liste[j + 1];
      liste[j + 1] = liste[j];
      liste[j] = temp;
    }
  }
  for (j = 0; j < i; j++)
  {
    if (fabsf(sqrt(pow((liste[j].x - p_tmp.x), 2) + pow((liste[i].y - p_tmp.y), 2))) > fabsf(sqrt(pow((liste[i].x - p_tmp.x), 2) + pow((liste[i].y - p_tmp.y), 2))))
      {
        liste[j].classe = p_tmp.classe;
        liste[j].x = p_tmp.x;
        liste[j].y = p_tmp.y;
        return liste;
      }
  }
  return liste;
}

point point_proche_dans_zone(point p, zone z_tmp)
{
  int i = 0, indexmin = 0;
  float dist = 0, dmin = 10;
  while (z_tmp[i].classe != 0)
  {
    dist = fabsf(sqrt(pow((z_tmp[i].x - p.x), 2) + pow((z_tmp[i].y - p.y), 2)));
    if (dist < dmin)
    {
      dmin = dist;
      indexmin = i;
    }
    i++;
  }
  return z_tmp[indexmin];
}

arbre_kd maj_zone(arbre_kd a,point p){
  if(est_vide(a->filsdroit) && est_vide(a->filsgauche)){
    printf("vide\n");
    a->zone=(zone)calloc(1,sizeof(point));
    a->zone[0]=p;
    return a;
  }
  if(est_vide(a->filsdroit)){
    printf("filsgauche\n");
    a->filsgauche=maj_zone(a->filsgauche,p);
    a->zone=concat(a->zone,a->filsgauche->zone);
    return a;
  }
  if(est_vide(a->filsgauche)){
    printf("filsdroit\n");
    a->filsdroit=maj_zone(a->filsdroit,p);
    a->zone=concat(a->zone,a->filsdroit->zone);
    return a;
  }
  if(!est_vide(a->filsgauche) && !est_vide(a->filsdroit)){
    printf("tout\n");
    a->filsgauche=maj_zone(a->filsgauche,p);
    a->filsdroit=maj_zone(a->filsdroit,p);
    a->zone=concat(a->filsgauche->zone,a->filsdroit->zone);
    return a;
  }
  return a;
}
int est_dans_zone(point p, zone z_tmp)
{
  int i = 0;
  while (z_tmp[i].classe != 0)
  {
    if (z_tmp[i].x == p.x && z_tmp[i].y == p.y && z_tmp[i].classe == p.classe)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

void affichage_zone(point * z){
  int i=0;
  while(z[i].classe!=0){
    printf("(%f,%f,%d) ",z[i].x,z[i].y,z[i].classe);
    i++;
  }
  printf("\n");
}

zone concat(zone zone1,zone zone2){
  int i=0,j=0,k=0,l=0;
  zone z3;
  while(zone1[i].classe != 0){
    i++;
  }
  while(zone2[j].classe != 0){
    j++;
  }
  z3=(zone)calloc((i+j)+2,sizeof(point));
  for(k=0;k<i;k++){
    
    z3[k]=zone1[k];
  }
  for(k=i;k<(i+j);k++){
    z3[k]=zone2[l];
    l++;
  }
  return z3;
}

int main()
{
  int taille = 750;
  int x, y, i = 0, classe, k;
  int info[3];
  arbre_kd a;
  point *tab;
  char *fichier2, *classetxt;
  tab = (point *)calloc(1, sizeof(point));
  a = NULL;
  if (tab == NULL)
  {
    fprintf(stderr, "Erreur allocaion !\n");
    exit(-1);
  }
  /*---Affichage de la fenetre et des boutons ---*/

  MLV_create_window("Partie 1", "partie1", taille + 200, taille);
  MLV_draw_text_box(
      taille + 10, 80,
      150, 20,
      "Load File",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 130,
      150, 20,
      "Manual insert",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 200,
      150, 20,
      "Quit",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 250,
      150, 20,
      "Save",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 280,
      150, 20,
      "Undo",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 310,
      150, 20,
      "Search KPPV",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_text_box(
      taille + 10, 350,
      150, 20,
      "KPPV decision",
      1,
      MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
      MLV_TEXT_LEFT,
      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_line(taille, 1, taille, taille - 1, MLV_COLOR_WHITE);
  MLV_actualise_window();

  /*---Attente du clic sur un des deux boutons---*/

  while (1 == 1)
  {
    MLV_wait_mouse(&x, &y);

    /*---Si bouton insert bouton ---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 130 && y < 150)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Classe :", &classetxt);
      classe = atoi(classetxt);
      MLV_wait_mouse(&x, &y);
      tab = inserer_point(x, y, classe, tab, taille);
      while (tab[i].classe != 0)
      {
        i++;
      }
      i--;
      a = inserer(a, tab[i], 0);
      a=maj_zone(a,tab[i]);
      affichage_zone(a->zone);
      affichage_points(taille, tab);
    }

    /*---Si chargement d'un fichier ---*/
    if (x > taille + 10 && x < taille + 10 + 150 && y > 80 && y < 100)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "fichier :", &fichier2);
      tab = chargement_fichier(tab, fichier2);
      free(fichier2);
      affichage_points(taille, tab);
    }

    /*--Si quitt---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 200 && y < 220)
    {
      /*printf("%d %d %d\n", a->noeud.classe, a->filsgauche->noeud.classe, a->filsdroit->noeud.classe);
      printf("%d %d\n", a->filsgauche->filsgauche->noeud.classe, a->filsgauche->filsdroit->noeud.classe);*/
      MLV_free_window();
      exit(0);
    }
    if (x > taille + 10 && x < taille + 10 + 150 && y > 250 && y < 270)
    {
      info[1] = 2;
      info[2] = 2;
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "nom fichier :", &fichier2);
      sauvegarde_fichier(tab, fichier2, info);
    }

    /*---Si undo---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 280 && y < 300)
    {
      tab = undo(tab);
      affichage_points(taille, tab);
    }

    /*---Si kppv ---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 310 && y < 330)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Valeur k :", &classetxt);
      k = atoi(classetxt);
      MLV_wait_mouse(&x, &y);
      kppv(k, x, y, taille, tab);
    }
    if (x > taille + 10 && x < taille + 10 + 150 && y > 350 && y < 370)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Valeur k :", &classetxt);
      k = atoi(classetxt);
      MLV_wait_mouse(&x, &y);
      tab = kppvpdd(k, x, y, taille, tab);
    }
  }
}
/*rectifier la concatenation, et la maj du coup, puis verifier si les autres fonction marche grace à ça*/
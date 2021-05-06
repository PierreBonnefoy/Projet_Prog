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
    a->zone = (zone)calloc(1, sizeof(point));
    a->zone[0] = p;
    a->filsgauche = NULL;
    a->filsdroit = NULL;
    a->noeud.x = p.x;
    a->noeud.y = p.y;
    a->noeud.classe = p.classe;

    return a;
  }
  a->zone = rajoute_point(a->zone, p);
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

point *recherche(arbre_kd a, point p, int k,point *liste){
  float dist1,dist2;
  liste=maj_liste(a->noeud,liste,k,p);
  if (est_vide(a->filsgauche) && est_vide(a->filsdroit))
  {
    return liste;
  }
  if(est_vide(a->filsgauche))
  {
    liste=recherche(a->filsdroit,p,k,liste);
    return liste;
  }
  if(est_vide(a->filsdroit))
  {
    liste=recherche(a->filsgauche,p,k,liste);
    return liste;
  }
  if(est_dans_zone(p,a->filsgauche->zone)){
    liste=recherche(a->filsgauche,p,k,liste);
    return liste;
  }
  if(est_dans_zone(p,a->filsdroit->zone)){
    liste=recherche(a->filsdroit,p,k,liste);
    return liste;
  }
  else{
    dist1=distance(point_proche_dans_zone(p,a->filsgauche->zone),p);
    printf("d1=%f ",dist1);
    dist2=distance(point_proche_dans_zone(p,a->filsdroit->zone),p);
    printf("d2=%f\n",dist2);
    if(dist1 <= dist2){
      printf("gauche !\n");
      liste=recherche(a->filsgauche,p,k,liste);
      printf("x = %f\n",liste[0].x);
      liste=recherche(a->filsdroit,p,k,liste);
      return liste;
    }
    if(dist1 > dist2){
      printf("droite !\n");
      liste=recherche(a->filsdroit,p,k,liste);
      liste=recherche(a->filsgauche,p,k,liste);
      return liste;
    }
  }
  return liste;
}

point *maj_liste(point p_tmp, point * liste,int k, point kpos) 
  {
    int i = 0, j = 0;
    point temp;
    if(liste[0].classe == 0){
      liste[0]=p_tmp;
      return liste;
    }
    while (liste[i].classe != 0)
    {
      if(i==(k-1)){
        break;
      }
      i++;
    }
    if(i==(k-1)){
      for (j = 0; j < i; j++)
      {
        if (distance(liste[j],kpos) < distance(liste[j+1],kpos))
        {
          temp = liste[j + 1];
          liste[j + 1] = liste[j];
          liste[j] = temp;
        }
      }
      for (j = 0; j <= i; j++)
      {
        if (distance(kpos,p_tmp) < distance(kpos,liste[j]))
        {
          liste[j].classe = p_tmp.classe;
          liste[j].x = p_tmp.x;
          liste[j].y = p_tmp.y;
          return liste;
        }
      }
    }
    else{
      liste[i]=p_tmp;
      return liste;
    }
    return liste;
  }

void affiche_kppv(point* tab,int taille){
  int i=0;
  while(tab[i].classe != 0){
    MLV_draw_filled_circle((tab[i].x + 1) * (taille / 2), taille - ((tab[i].y + 1) * (taille / 2)), 3, MLV_COLOR_GREEN);
    i++;
  }
  MLV_actualise_window();
}

float distance(point p_tmp,point kpos){
  return (fabsf(sqrt(pow((p_tmp.x - kpos.x), 2) + pow((p_tmp.y - kpos.y), 2))));
}

  point point_proche_dans_zone(point p, zone z_tmp)
  {
    int i = 0, indexmin = 0;
    float dist = 0, dmin = 100;
    while (z_tmp[i].classe != 0)
    {
      dist=distance(p,z_tmp[i]);
      if (dist < dmin)
      {
        dmin = dist;
        indexmin = i;
      }
      i++;
    }
    return z_tmp[indexmin];
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

  void affichage_zone(point * z)
  {
    int i = 0;
    while (z[i].classe != 0)
    {
      printf("(%f,%f,%d) ", z[i].x, z[i].y, z[i].classe);
      i++;
    }
    printf("\n");
  }

  zone rajoute_point(zone z, point p)
  {
    zone z_bis;
    int i = 0, j;
    while (z[i].classe != 0)
    {
      i++;
    }
    z_bis = (zone)calloc((i + 2), sizeof(point));
    for (j = 0; j < i; j++)
    {
      z_bis[j] = z[j];
    }
    z_bis[i] = p;
    return z_bis;
  }

int main()
  {
    int taille = 750;
    int x, y, i = 0, classe, k;
    float x2,y2;
    int info[3];
    arbre_kd a;
    point *tab;
    point temp;
    char *fichier2, *classetxt;
    point * zkppv;
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
    MLV_draw_text_box(
        taille + 10, 400,
        150, 20,
        "KPPV arbre",
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
        affichage_zone(a->zone);
        affichage_points(taille, tab);
      }

      /*---Si chargement d'un fichier ---*/
      if (x > taille + 10 && x < taille + 10 + 150 && y > 80 && y < 100)
      {
        MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "fichier :", &fichier2);
        tab = chargement_fichier(tab, fichier2);
        i = 0;
        while (tab[i].classe != 0)
        {
          a = inserer(a, tab[i], 0);
          i++;
        }
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

      /*si kppv arbre*/
      if (x > taille + 10 && x < taille + 10 + 150 && y > 400 && y < 420)
      {
	affichage_points(taille, tab);
        MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Valeur k :", &classetxt);
        k = atoi(classetxt);
        MLV_wait_mouse(&x, &y);
        x2 = ((x * 1.000000) / (taille / 2)) - 1;
        y2 = 1 - ((y * 1.000000) / (taille / 2));
        temp.x = x2;
        temp.y = y2;
        temp.classe = 0;
        zkppv = (point*)calloc((k+1),sizeof(point));
        if (zkppv == NULL)
        {
          printf("Erreur d'allocation !\n");
          exit(-1);
        }
        zkppv=recherche(a,temp,k,zkppv);
        affichage_zone(zkppv);
        affiche_kppv(zkppv,taille);
        free(zkppv);
      }
    }
  }

#include "partie2.h"
#include <MLV/MLV_all.h>
#include <math.h>

int est_vide(arbre_kd a)
{
  /*---Verification si l'arbre donné est vide---*/
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
    /*--Si c'est une feuille, on ajoute le point a la zone, et on initialise le noeud avec le point---*/
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
    /*---Une fois sur deux on verifie le point avec son x---*/
    if (a->noeud.x < p.x)
    {
      /*----Si son x est superieur au noeud, on verifie avec son fils droit---*/
      a->filsdroit = inserer(a->filsdroit, p, choix + 1);
      return a;
    }
    else
    {
      /*---Sinon on vérifie son filsgauche ---*/
      a->filsgauche = inserer(a->filsgauche, p, choix + 1);
      return a;
    }
  }
  else
  {
    /*---Une fois sur deux on verifie le point avec son y---*/
    if (a->noeud.y < p.y)
    {
      /*----Si son y est superieur au noeud, on verifie avec son fils droit---*/
      a->filsdroit = inserer(a->filsdroit, p, choix + 1);
      return a;
    }
    else
    {
      /*---Sinon on vérifie son filsgauche ---*/
      a->filsgauche = inserer(a->filsgauche, p, choix + 1);
      return a;
    }
  }
}

point *recherche(arbre_kd a, point p, int k, point *liste)
{
  float dist1, dist2;
  liste = maj_liste(a->noeud, liste, k, p);
  if (est_vide(a->filsgauche) && est_vide(a->filsdroit))
  {
    /*---Si c'est une feuille, on renvoie la liste des kppv---*/
    return liste;
  }
  if (est_vide(a->filsgauche))
  {
    /*---Si il n'y a pas de filsgauche, on recherche dans le filsdroit---*/
    liste = recherche(a->filsdroit, p, k, liste);
    return liste;
  }
  if (est_vide(a->filsdroit))
  {
    /*---Si il n'y a pas de filsdroit, on recherche dans le filsgauche---*/
    liste = recherche(a->filsgauche, p, k, liste);
    return liste;
  }
  if (est_dans_zone(p, a->filsgauche->zone))
  {
    /*---Si le point appartient a la zone gauche, on recherche dans le filsgauche---*/
    liste = recherche(a->filsgauche, p, k, liste);
    return liste;
  }
  if (est_dans_zone(p, a->filsdroit->zone))
  {
    /*---Si le point appartient a la zone droite, on recherche dans le filsdroit---*/
    liste = recherche(a->filsdroit, p, k, liste);
    return liste;
  }
  else
  {
    /*---Sinon on recherche dans quel zone est le point le plus proche et on effectue la recherche dans cette zone---*/
    dist1 = distance(point_proche_dans_zone(p, a->filsgauche->zone), p);
    dist2 = distance(point_proche_dans_zone(p, a->filsdroit->zone), p);
    if (dist1 <= dist2)
    {
      liste = recherche(a->filsgauche, p, k, liste);
      liste = recherche(a->filsdroit, p, k, liste);
      return liste;
    }
    if (dist1 > dist2)
    {
      liste = recherche(a->filsdroit, p, k, liste);
      liste = recherche(a->filsgauche, p, k, liste);
      return liste;
    }
  }
  return liste;
}

point *maj_liste(point p_tmp, point *liste, int k, point kpos)
{
  int i = 0, j = 0;
  point temp;
  if (liste[0].classe == 0)
  {
    /*---si la liste est vide, on met le point dans la liste---*/
    liste[0] = p_tmp;
    return liste;
  }
  while (liste[i].classe != 0)
  {
    /*---On parcours la liste donné---*/
    if (i == (k - 1))
    {
      break;
    }
    i++;
  }
  if (i == (k - 1))
  {
    /*---si la liste est pleine(de taille k)---*/
    for (j = 0; j < i; j++)
    {
      if (distance(liste[j], kpos) < distance(liste[j + 1], kpos))
      {
        /*---On parcourt la liste des kppv pour les triés---*/
        temp = liste[j + 1];
        liste[j + 1] = liste[j];
        liste[j] = temp;
      }
    }
    for (j = 0; j <= i; j++)
    {
      if (distance(kpos, p_tmp) < distance(kpos, liste[j]))
      {
        /*---On vérifie si le point donné est plus petit que l'un des points de la liste---*/
        liste[j].classe = p_tmp.classe;
        liste[j].x = p_tmp.x;
        liste[j].y = p_tmp.y;
        return liste;
      }
    }
  }
  else
  {
    /*---Si sa taille est plus petite que k, on rajoute le point---*/
    liste[i] = p_tmp;
    return liste;
  }
  return liste;
}

void affiche_kppv(point *tab, int taille)
{
  int i = 0;
  /*---Cette fonction parcourt la liste des kppv trouvé dans l'arbre pour les mettre en valeur dans l'interface---*/
  while (tab[i].classe != 0)
  {
    MLV_draw_filled_circle((tab[i].x + 1) * (taille / 2), taille - ((tab[i].y + 1) * (taille / 2)), 3, MLV_COLOR_GREEN);
    i++;
  }
  MLV_actualise_window();
}

float distance(point p_tmp, point kpos)
{
  /*---Une fonction qui renvoie la distance entre 2 points---*/
  return (fabsf(sqrt(pow((p_tmp.x - kpos.x), 2) + pow((p_tmp.y - kpos.y), 2))));
}

point point_proche_dans_zone(point p, zone z_tmp)
{
  int i = 0, indexmin = 0;
  float dist = 0, dmin = 100;
  while (z_tmp[i].classe != 0)
  {
    /*---Parcours la liste des point pour renvoyer le point de plus faible distance avec le point donné---*/
    dist = distance(p, z_tmp[i]);
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
    /*---Parcours la liste des points et verifie si le point donné est dedans---*/
    if (z_tmp[i].x == p.x && z_tmp[i].y == p.y && z_tmp[i].classe == p.classe)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

zone rajoute_point(zone z, point p)
{
  /*---Cette fonction parcourt la liste donné et rajoute un point a la fin---*/
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
  float x2, y2;
  int info[3];
  arbre_kd a;
  point *tab;
  point temp;
  char *fichier2, *classetxt;
  point *zkppv;
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
      affichage_points(taille, tab);
    }

    /*---Si chargement d'un fichier ---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 80 && y < 100)
    {
      i = 0;
      while (tab[i].classe != 0)
      {
        i++;
      }
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "fichier :", &fichier2);
      tab = chargement_fichier(tab, fichier2);
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
      MLV_free_window();
      exit(0);
    }

    /*---Si sauvegarde fichier---*/

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

    /*---Si KPPV avec prise de décision---*/
    
    if (x > taille + 10 && x < taille + 10 + 150 && y > 350 && y < 370)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "Valeur k :", &classetxt);
      k = atoi(classetxt);
      MLV_wait_mouse(&x, &y);
      tab = kppvpdd(k, x, y, taille, tab);
    }

    /*---Si kppv arbre---*/
    
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
      zkppv = (point *)calloc((k + 1), sizeof(point));
      if (zkppv == NULL)
      {
        printf("Erreur d'allocation !\n");
        exit(-1);
      }
      zkppv = recherche(a, temp, k, zkppv);
      affiche_kppv(zkppv, taille);
      free(zkppv);
    }
  }
}

#include "partie1.h"
#include <MLV/MLV_all.h>
#include <math.h>

point *chargement_fichier(point *tab, char *chemin)
{
  int taille, dimension, nbr_classe, i = 0, j = 0;
  FILE *fichier;
  point *tab_bis;

  while (tab[i].classe != 0)
  {
    i++;
  }

  /*---Ouverture du fichier---*/

  fichier = fopen(chemin, "r");

  /*--Ecriture de la premiere ligne---*/

  fscanf(fichier, "%d %d %d", &taille, &dimension, &nbr_classe);

  /*---Allocation---*/

  tab_bis = (point *)calloc((i + taille + 1), sizeof(point));
  i = 0;
  while (tab[i].classe != 0)
  {
    tab_bis[i] = tab[i];
    i++;
  }
  free(tab);
  if (tab_bis == NULL)
  {
    fprintf(stderr, "erreur allocution pointeur !");
    exit(-1);
  }

  /*---Lecture du fichier texte + creation du tableau de points---*/
  printf("taille+i = %d\n", taille + i);

  for (j = i; j <= taille + i; j++)
  {
    fscanf(fichier, "%d %f %f", &tab_bis[j].classe, &tab_bis[j].x, &tab_bis[j].y);
  }
  fclose(fichier);
  return tab_bis;
}

point *inserer_point(int x, int y, int classe, point *tab, int taille)
{
  point *tab_bis;
  int i = 0;
  float x2, y2;

  /*---parcours du tableau de points jusqua la fin ---*/

  while (tab[i].classe != 0)
  {
    i++;
  }
  tab_bis = (point *)calloc((i + 2), sizeof(point));
  i = 0;
  while (tab[i].classe != 0)
  {
    tab_bis[i] = tab[i];
    i++;
  }
  free(tab);
  /*---Conversion pour rentrer dans le tablea---*/
  x2 = ((x * 1.000000) / (taille / 2)) - 1;
  y2 = 1 - ((y * 1.000000) / (taille / 2));

  /*---Insertion du point a la fin---*/
  tab_bis[i].x = x2;
  tab_bis[i].y = y2;
  tab_bis[i].classe = classe;
  return tab_bis;
}

point *undo(point *tab)
{
  point *tab_bis;
  int i = 0;
  while (tab[i].classe != 0)
  {
    i++;
  }
  tab_bis = (point *)calloc((i), sizeof(point));
  i = 0;
  while (tab[i + 1].classe != 0)
  {
    tab_bis[i] = tab[i];
    i++;
  }
  free(tab);
  return tab_bis;
}

point *kppv(int k, int x, int y, int taille, point *tab)
{
  float x2, y2, distance,temp;
  int i = 0, j = 0,l,tempi,radius;
  float *kp;
  int *kpbis;
  kp = (int *)malloc(k * sizeof(float));
  kpbis=(int *)malloc(k*sizeof(int));
  for (i = 0; i < k; i++)
  {
    kp[i] = 100;
    kpbis[i]=0;
  }
  
  i = 0;
  x2 = ((x * 1.000000) / (taille / 2)) - 1;
  y2 = 1 - ((y * 1.000000) / (taille / 2));
  while (tab[i].classe != 0)
  {
    distance = fabsf(sqrt(pow((tab[i].x - x2), 2) + pow((tab[i].y - y2), 2)));

    for (j = 0; j < k; j++)
    {
      if(distance<kp[j]){
        for(l=0;l<k;l++){
          if(kp[l]<kp[l+1]){
            temp=kp[l+1];
            kp[l+1]=kp[l];
            kp[l]=temp;
            tempi=kpbis[l+1];
            kpbis[l+1]=kpbis[l];
            kpbis[l]=tempi;
          }
        }
        kp[0]=distance;
        kpbis[0]=i;
        break;
      }
      printf("i = %d dis = %f\n",kpbis[j],kp[j]);
    }
    printf("\n");
    i++;
  }
  for(l=0;l<k;l++){
          if(kp[l]<kp[l+1]){
            temp=kp[l+1];
            kp[l+1]=kp[l];
            kp[l]=temp;
            tempi=kpbis[l+1];
            kpbis[l+1]=kpbis[l];
            kpbis[l]=tempi;
          }
        }
  for(j=0;j<k;j++){
    tab[kpbis[j]].classe=3;
  }
  radius=kp[0] * (taille / 2);
  affichage_points(taille, tab);
  MLV_draw_circle(x,y,radius,MLV_COLOR_WHITE);
  MLV_draw_filled_circle(	x,	y,2,
		MLV_COLOR_WHITE 
	);
  MLV_actualise_window();
  return tab;
}

point *kppvpdd(int k,int x,int y,int taille,point *tab){
  float x2, y2, distance,temp;
  int i = 0, j = 0,l,tempi,radius,*tabclasse,max=0;
  float *kp;
  int *kpbis;
  kp = (float *)malloc(k * sizeof(float));
  kpbis=(int *)malloc(k*sizeof(int));
  tabclasse=(int *)malloc(k*sizeof(int));
  for (i = 0; i < k; i++)
  {
    kp[i] = 100;
    kpbis[i]=0;
    tabclasse[i]=0;
  }
  
  i = 0;
  x2 = ((x * 1.000000) / (taille / 2)) - 1;
  y2 = 1 - ((y * 1.000000) / (taille / 2));
  while (tab[i].classe != 0)
  {
    distance = fabsf(sqrt(pow((tab[i].x - x2), 2) + pow((tab[i].y - y2), 2)));

    for (j = 0; j < k; j++)
    {
      if(distance<kp[j]){
        for(l=0;l<k;l++){
          if(kp[l]<kp[l+1]){
            temp=kp[l+1];
            kp[l+1]=kp[l];
            kp[l]=temp;
            tempi=kpbis[l+1];
            kpbis[l+1]=kpbis[l];
            kpbis[l]=tempi;
          }
        }
        kp[0]=distance;
        kpbis[0]=i;
        break;
      }
      printf("i = %d dis = %f\n",kpbis[j],kp[j]);
    }
    printf("\n");
    i++;
  }
  for(l=0;l<k;l++){
          if(kp[l]<kp[l+1]){
            temp=kp[l+1];
            kp[l+1]=kp[l];
            kp[l]=temp;
            tempi=kpbis[l+1];
            kpbis[l+1]=kpbis[l];
            kpbis[l]=tempi;
          }
        }
  for(j=0;j<k;j++){
    printf("%d\n",kpbis[i]);
    tabclasse[tab[kpbis[j]].classe]+=1;
  }
  for(j=1;j<=2;j++){
    if(tabclasse[j]>max){
      max=j;
    }
  }
  printf("max = %d",max);
  tab=inserer_point(x,y,max,tab,taille);
  return tab;
}

void affichage_points(int taille, point *tab)
{
  int i = 0;
  MLV_draw_filled_rectangle(0, 0, taille, taille, MLV_COLOR_BLACK);
  /*---affichage des points sur la fenetre---*/

  while (tab[i].classe != 0)
  {
    printf("x = %f y = %f classe = %d i = %d\n", tab[i].x, tab[i].y, tab[i].classe, i);
    if (tab[i].classe == 3)
    {
      MLV_draw_filled_circle((tab[i].x + 1) * (taille / 2), taille - ((tab[i].y + 1) * (taille / 2)), 3, MLV_COLOR_GREEN);
    }
    if (tab[i].classe == 1)
    {
      MLV_draw_filled_circle((tab[i].x + 1) * (taille / 2), taille - ((tab[i].y + 1) * (taille / 2)), 3, MLV_COLOR_BLUE);
    }
    if (tab[i].classe == 2)
    {
      MLV_draw_filled_circle((tab[i].x + 1) * (taille / 2), taille - ((tab[i].y + 1) * (taille / 2)), 3, MLV_COLOR_RED);
    }
    i++;
    MLV_actualise_window();
  }
  printf("\n");
}

void sauvegarde_fichier(point *p, char *nom, int *info)
{
  int i = 0;
  FILE *save;
  while (p[i].classe != 0)
  {
    i++;
  }
  info[0] = i;
  i = 0;
  /* Création du fichier de sauvegarde */

  save = fopen(nom, "w+");
  fprintf(save, "%d %d %d\n", info[0], info[1], info[2]);

  while (p[i].classe != 0)
  {
    fprintf(save, "%d %f %f\n", p[i].classe, p[i].x, p[i].y);
    i++;
  }

  fclose(save);
}

int main(int argc, char **argv)
{
  int i = 0, taille = 750;
  int x, y, classe, k;
  int info[3];
  point *tab;
  char *fichier2, *classetxt;
  tab = (point *)calloc(1, sizeof(point));
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
      affichage_points(taille, tab);
      printf("\n");
    }

    /*---Si chargement d'un fichier ---*/
    if (x > taille + 10 && x < taille + 10 + 150 && y > 80 && y < 100)
    {
      MLV_wait_input_box(taille + 10, 10, taille + 40, 20, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK, "fichier :", &fichier2);
      tab = chargement_fichier(tab, fichier2);
      free(fichier2);
      affichage_points(taille, tab);
      printf("\n");
    }

    /*--Si quitt---*/

    if (x > taille + 10 && x < taille + 10 + 150 && y > 200 && y < 220)
    {
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
      tab=kppvpdd(k, x, y, taille, tab);
      affichage_points(taille,tab);
    }
  }
}
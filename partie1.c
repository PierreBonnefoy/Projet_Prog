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

  if(fscanf(fichier, "%d %d %d", &taille, &dimension, &nbr_classe)==EOF){
    fprintf(stderr,"Pb lecture du fichier !\n");
    exit(-1);
  }

  /*---Allocation---*/

  tab_bis = (point *)calloc((i + taille + 1), sizeof(point));
  if(tab_bis==NULL){
    fprintf(stderr,"Erreur allocaion !\n");
    exit (-1);
  }
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

  for (j = i; j < taille + i; j++)
  {
    if(fscanf(fichier, "%d %f %f", &tab_bis[j].classe, &tab_bis[j].x, &tab_bis[j].y)==EOF){
    fprintf(stderr,"Pb lecture du fichier2 !\n");
    exit(-1);
  }
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
  if(tab_bis==NULL){
    fprintf(stderr,"Erreur allocaion !\n");
    exit (-1);
  }
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
  if(tab_bis==NULL){
    fprintf(stderr,"Erreur allocaion !\n");
    exit (-1);
  }
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
  kp = (float *)malloc(k * sizeof(float));
  kpbis=(int *)malloc(k*sizeof(int));
  if(kp==NULL || kpbis==NULL){
    fprintf(stderr,"Erreur allocaion !\n");
    exit (-1);
  }
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
    }
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
    MLV_draw_filled_circle((tab[kpbis[j]].x + 1) * (taille / 2), taille - ((tab[kpbis[j]].y + 1) * (taille / 2)),3,
		MLV_COLOR_GREEN
	);
  }
  radius=kp[0] * (taille / 2);
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
  if(tabclasse==NULL || kp==NULL || kpbis==NULL){
    fprintf(stderr,"Erreur allocaion !\n");
    exit (-1);
  }
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
    }
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
    tabclasse[tab[kpbis[j]].classe]+=1;
  }
  for(j=1;j<=2;j++){
    if(tabclasse[j]>max){
      max=j;
    }
  }
  tab=inserer_point(x,y,max,tab,taille);
  radius=kp[0] * (taille / 2);
  affichage_points(taille, tab);
  MLV_draw_circle(x,y,radius,MLV_COLOR_WHITE);
  MLV_actualise_window();
  return tab;
}

void affichage_points(int taille, point *tab)
{
  int i = 0;
  MLV_draw_filled_rectangle(0, 0, taille, taille, MLV_COLOR_BLACK);
  /*---affichage des points sur la fenetre---*/

  while (tab[i].classe != 0)
  {
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

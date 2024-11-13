
/*---------------------------------------------*/
/*                                             */
/*partie de Code specifique a  chaque probleme */
/*                                             */
/*---------------------------------------------*/

/* La file grand taxi-marocain Modulee, 2 batchs d'arrivée, chanque transition change le nombre de clients puis soit je reste en phase0 soit je change de phase */	
		

/* codage des evenements Pour le batch1 {0,1,2} */
/* 1 : arrive d'0 paquet (Batch1,phase0) et trans vers (Batch1+0,phase0) */
/* 2 : arrive d'0 paquet (Batch1,phase0) et switch vers (Batch1+0,phase1) */
/* 3 : arrive d'1 paquet (Batch1,phase0) et trans vers (Batch1+1,phase0) 
 * 4 : arrive d'1 paquet (Batch1,phase0) et switch vers (Batch1+1,phase1) 
 * 5 : arrive d'2 paquet (Batch1,phase0) et trans vers (Batch1+2,phase0) 
 * 6 : arrive d'2 paquet (Batch1,phase0) et switch vers (Batch1+2,phase1)  
 * 7 : arrive d'3 paquet (Batch1,phase0) et trans vers (Batch1+3,phase0) 
 * 8 : arrive d'3 paquet (Batch1,phase0) et switch vers (Batch1+3,phase1)  */
 
/* codage des evenements Pour le batch2 {0,1,2} */
/* 1 : arrive d'0 paquet (Batch2,phase0) et trans vers (Batch1+0,phase0) */
/* 2 : arrive d'0 paquet (Batch2,phase0) et switch vers (Batch1+0,phase1) */
/* 3 : arrive d'1 paquet (Batch2,phase0) et trans vers (Batch1+1,phase0) 
 * 4 : arrive d'1 paquet (Batch2,phase0) et switch vers (Batch1+1,phase1) 
 * 5 : arrive d'2 paquet (Batch2,phase0) et trans vers (Batch1+2,phase0) 
 * 6 : arrive d'2 paquet (Batch2,phase0) et switch vers (Batch1+2,phase1)  
 * 7 : arrive d'3 paquet (Batch2,phase0) et trans vers (Batch1+3,phase0) 
 * 8 : arrive d'3 paquet (Batch2,phase0) et switch vers (Batch1+3,phase1)  */


#include <math.h>

/* proba des evenements */ 
#define p00  0.1
#define p01  0.15
#define p02  0.25		
#define p03  0.50
#define palpha01 0.2 // proba de changement de phase 0 -> 1

#define p10  0.5
#define p11  0.25
#define p12  0.15		
#define p13  0.1
#define palpha10 0.1 // proba de changement de phase 0 -> 1






/* Parametres du probleme */

#define Buffer 140
//#define Deadline 10
//#define seuil 0.8
//et un Buffer = 67 , int a[3] = {7,27,666};  B= 666/* tableau du nombre de paquets qui arrives par evenements */
//int a[3] = {2,3,4}; /* tableau du nombre de paquets qui arrives par evenements */

int a0[4] = {0,1,2,3};
int a1[4] = {0,1,2,3};

void InitEtendue(int Deadline)
{
  Min[0] = 0;
  Max[0] = Buffer;
  Min[1] = 0;
  Max[1] = Deadline;
  Min[2] = 0;
  Max[2] = 1;
}


void EtatInitial(E)
int *E;
{
  /*donne a E la valeur de l'etat racine de l'arbre de generation*/
  E[0] = 0;
  E[1] = 0;
  E[2] = 0;
}



long double Probabilite(indexevt, E)
int indexevt;
int *E;
{
  /* retourne la probabilite d'apparition de l'evenement indexevt */
  double p;
  
  
  if(E[2] == 0)
  {
      switch (indexevt) {
		  case 1:
		   {    p = p00 * (1-palpha01); //je reste dans ma phase actuelle avec proba 1-alpha01
				break; }
		  case 2:
		   {    p = p00 * palpha01; // je change de phase avec proba alpha01
				break; }
		  case 3:
		   {    p = p01 * (1-palpha01);
				break; }
		  case 4:
		   {    p = p01 * palpha01;
				break; }
		  case 5:
		   {    p = p02 * (1-palpha01);
				break; }
		  case 6:
		   {    p = p02 * palpha01;
				break; }
		  case 7:
		   {    p = p03 * (1-palpha01);
				break; }
		  case 8:
		   {    p = p03 * palpha01;
				break; }
		  default: 
		   { printf("erreur indice event \n");
			  exit(0);}
		   }
  return p;  
  }
  
  
		switch (indexevt) {
		  case 1:
		   {    p = p10 * (1- palpha10); //je reste dans ma phase actuelle avec proba 1-alpha10
				break; }
		  case 2:
		   {    p = p10 * palpha10;     //je change de phase avec alpha10
				break; }
		  case 3:
		   {    p = p11 * (1- palpha10);
				break; }
		  case 4:
		   {    p = p11 * palpha10;
				break; }
		  case 5:
		   {    p = p12 * (1- palpha10);
				break; }
		  case 6:
		   {    p = p12 * palpha10;
				break; }
		  case 7:
		   {    p = p13 * (1- palpha10);
				break; }
		  case 8:
		   {    p = p13 * palpha10;
				break; }
		  default: 
		   { printf("erreur indice event \n");
			  exit(0);}
		   }
  return p;  
  
 
}


void Equation(E, indexevt, F, R, seuil, Deadline)
int *E;
int indexevt,Deadline;
int *F, *R;
int seuil;
{
  /*ecriture de l'equation d'evolution, transformation de E en F grace a l'evenemnt indexevt, mesure de la recompense R sur cette transition*/
  double r;
  int bool = 0;
  F[0] = E[0];
  F[1] = E[1];
  F[2] = E[2];
  
	  if(F[2] == 0)
	  {
		if(F[1] == 0 && a0[(int)(ceil(indexevt/2.0)-1)] == 0 )
			{   bool = 1; }
		if( (F[0]>seuil) || (F[1] == Max[1]) )
			{   F[0] =0; F[1] =0; bool=1; }
		if(bool==0)
		    {   //printf("Index = %d et J'accede a : a0[%d]  et ceil(0.5) = %f \n",indexevt,(int)(ceil(indexevt/2.0))-1);
				F[0] += a0[(int)(ceil(indexevt/2.0)-1)]; 
				F[1]++;
			}			  
		  if(indexevt%2 == 0) // Changement de phase
		  {
			  F[2] = 1;
		  }
		  return;
	  }
	  
	  bool = 0;
	  if(F[2] == 1)
	  {
		if(F[1] == 0 && a1[(int)(ceil(indexevt/2.0))-1] == 0 )
			{   bool = 1; }
		if( (F[0]>seuil) || (F[1] == Max[1]) )
			{   F[0] =0; F[1] =0; bool=1; }
		if(bool==0)
		    {  
				//printf("Index = %d et J'accede a : a1[%d] \n",indexevt,((int)(ceil(indexevt/2.0)))-1);
				F[0] += a1[(int)(ceil(indexevt/2.0))-1]; 
				F[1]++;
			}			  
		  if(indexevt%2 == 0) // Changement de phase
		  {
			  F[2] = 0;
		  }
		  return;
	  }
	  

}


  
void InitParticuliere()
{
    
}

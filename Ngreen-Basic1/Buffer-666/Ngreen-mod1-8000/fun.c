
/*---------------------------------------------*/
/*                                             */
/*partie de Code specifique a  chaque probleme */
/*                                             */
/*---------------------------------------------*/

/* La file grand taxi-marocain */	
		

/* codage des evenements */
/* 1 : arrive d'1 paquet */
/* 2 : arrivee de 2 paquets */
/* 3 : arrivee de 3 paquets */

/* proba des evenements */ 

#define p0  0.05
#define p1  0.8		
#define p2  0.1		
#define p3  0.05

/* Parametres du probleme */

#define Buffer 666
//#define Deadline 10
//#define seuil 0.8
//et un Buffer = 67 , int a[3] = {7,27,666};  B= 666/* tableau du nombre de paquets qui arrives par evenements */
//int a[3] = {2,3,4}; /* tableau du nombre de paquets qui arrives par evenements */

int a[4] = {0,5,10,20};

void InitEtendue(int Deadline)
{
  Min[0] = 0;
  Max[0] = Buffer;
  Min[1] = 0;
  Max[1] = Deadline;
}


void EtatInitial(E)
int *E;
{
  /*donne a E la valeur de l'etat racine de l'arbre de generation*/
  E[0] = 0;
  E[1] = 0;
}



double Probabilite(indexevt, E)
int indexevt;
int *E;
{
  /* retourne la probabilite d'apparition de l'evenement indexevt */
  double p;
  switch (indexevt) {
  case 1:
   { p = p0;
    break; }
  case 2:
   { p = p1;
    break; }
  case 3:
   { p = p2;
    break; }
  case 4:
   { p = p3;
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
double seuil;
{
  /*ecriture de l'equation d'evolution, transformation de E en F grace a l'evenemnt indexevt, mesure de la recompense R sur cette transition*/
  int bool = 0;
  F[0] = E[0];
  F[1] = E[1];
  //printf("(%d,%d) \n",F[0],F[1]);
  
  if(F[0]>Max[0])
	{	F[0] -= Max[0]; F[1] = 0 ; bool=1; }
  if( (F[0]>seuil*Max[0]) || (F[1] == Max[1]) )
	{   F[0] =0; F[1] =0; bool=1; }
  if(bool==0)
   { 
	  F[0] += a[indexevt-1]; 
	  F[1]++;
   }

}


  
void InitParticuliere()
{
    
}

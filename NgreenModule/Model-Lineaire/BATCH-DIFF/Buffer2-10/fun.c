
/*---------------------------------------------*/
/*                                             */
/*partie de Code specifique a  chaque probleme */
/*                                             */
/*---------------------------------------------*/

/* La file grand taxi-marocain Modulee avec un etat racine */	
		

/* codage des evenements */
/* 1 : arrive d'1 paquet */
/* 2 : arrivee de 2 paquets */
/* 3 : arrivee de 3 paquets 
 * 4 : transition alpha1 ves alpha0 ou l'inverse
 * 5 : transition racine vers (0,0,0)
 * 6 : transition racine vers (0,0,1) */

/* proba des evenements */ 


#define p00  0.1
#define p01  0.15		
#define p02  0.65
#define alpha01 0.1

#define p10  0.699
#define p11  0.2		
#define p12  0.1
#define alpha10 0.001


#define p1 0.5 
#define p2 0.5

/* Parametres du probleme */

#define Buffer 25
//#define Deadline 10
//#define seuil 0.8
//et un Buffer = 67 , int a[3] = {7,27,666};  B= 666/* tableau du nombre de paquets qui arrives par evenements */
//int a[3] = {2,3,4}; /* tableau du nombre de paquets qui arrives par evenements */

int a0[3] = {3,5,7};
int a1[3] = {4,6,8};

void InitEtendue(int Deadline)
{
  Min[0] = -1;
  Max[0] = Buffer;
  Min[1] = -1;
  Max[1] = Deadline;
  Min[2] = -1;
  Max[2] = 1;
}


void EtatInitial(E)
int *E;
{
  /*donne a E la valeur de l'etat racine de l'arbre de generation*/
  E[0] = -1;
  E[1] = -1;
  E[2] = -1;
}



long double Probabilite(indexevt, E)
int indexevt;
int *E;
{
  /* retourne la probabilite d'apparition de l'evenement indexevt */
  double p;
  
  if(E[0] == -1 && E[1] == -1 && E[2] == -1 )
  {
      switch (indexevt) {
		  case 1:
		   {    p = 0;
				break; }
		  case 2:
		   {    p = 0;
				break; }
		  case 3:
		   {    p = 0;
				break; }
		  case 4:
		   {    p = 0;
				break; }
		  case 5:
		   {    p = p1;
				break; }
		  case 6:
		   {    p = p2;
				break; }
		  default: 
		   { printf("erreur indice event \n");
			  exit(0);}
		   }
  return p;  
  }
  
  if(E[2] == 0)
  {
      switch (indexevt) {
		  case 1:
		   {    p = p00;
				break; }
		  case 2:
		   {    p = p01;
				break; }
		  case 3:
		   {    p = p02;
				break; }
		  case 4:
		   {    p = alpha01;
				break; }
		  case 5:
		   {    p = 0;
				break; }
		  case 6:
		   {    p = 0;
				break; }
		  default: 
		   { printf("erreur indice event \n");
			  exit(0);}
		   }
  return p;  
  }
  
  
		switch (indexevt) {
		  case 1:
		   {    p = p10;
				break; }
		  case 2:
		   {    p = p11;
				break; }
		  case 3:
		   {    p = p12;
				break; }
		  case 4:
		   {    p = alpha10;
				break; }
		  case 5:
		   {    p = 0;
				break; }
		  case 6:
		   {    p = 0;
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
  //printf("\n (%d,%d,%d) event : %d ",F[0],F[1],F[2],indexevt);
  
  if(indexevt == 6)
  {
	if(F[0] == -1 && F[1] == -1 && F[2] == -1 )  
	{
		F[0] =0; F[1] =0; F[2] =1;		
	}  
  }
  
  if(indexevt == 5)
  {
	if(F[0] == -1 && F[1] == -1 && F[2] == -1 )  
	{
		F[0] =0; F[1] =0; F[2] =0;		
	}  
  }
  
  if(indexevt == 4)
  {
   if(F[2] == 0) 
	{	
		if( (F[0]<=seuil) && (F[1] != Max[1]) )
		   F[2] =1;
		if( (F[0]>seuil) || (F[1] == Max[1]) )
		   {F[0] =-1; F[1] =-1; F[2] =-1;}
	}
   else	
	{
		if( (F[0]<=seuil) && (F[1] != Max[1]) )
			F[2] =0;
		if( (F[0]>seuil) || (F[1] == Max[1]) )
		   {F[0] =-1; F[1] =-1; F[2] =-1;}
	}
  }
  
  if(indexevt == 1 || indexevt == 2 || indexevt == 3)
  {
	  /*if(F[0]>Max[0])
		{	F[0] -= Max[0]; F[1] = 0; bool=1; }*/
	  if( (F[0]>seuil) || (F[1] == Deadline) )
		{   F[0] =-1; F[1] =-1; F[2] =-1; bool=1;}
	  if(bool==0)
	   {  if(F[2] == 0)
		  { 
		  F[0] += a0[indexevt-1]; 
		  }
		  if(F[2] == 1)
		  { 
		  F[0] += a1[indexevt-1]; 
		  }
		  F[1]++;
	   }
  }

}


  
void InitParticuliere()
{
    
}
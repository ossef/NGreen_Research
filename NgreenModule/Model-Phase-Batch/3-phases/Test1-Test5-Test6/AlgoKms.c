/* 
 * Youssef V1.0 le 01/03/2018
 * Algorithme KMS : Algorithme itératif pour le calcul de la distribution stationnaire
 * prend en entrée une approximation de la distribution stationnaire
 * Convergence rapide vers la distribution stationnaire
 * Condition : La matrice en entrée doit être NCD, c'est à dire decomposable en Block (avec une forte masse de proba sur les blocs diagonales)
 * En entrée :
 * 					- Matrice Stochastique ergodique
 * 					- Approximation initiale du vecteur de probabilité stationnaire
 * En Sortie: 		- La distribution stationnaire
 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Kms.h"


void usage() { 
    printf("\nusage : ./AlgoKms -f model method exp  \n");
    printf(" model.sz, model.cd, model.Cii , model.pi0 and model.exp.part must exist before \n");
    printf(" Explication : \n");
    printf("	Matrice en entrée : model.sz, model.cd, model.Cii \n");
    printf("	Partition 	  : model.method.exp.part (method must be 'tarjan')  \n");
    printf("	Approxim initiale : model.pi0 \n");
    exit(1); 
}

void  ProblemeMemoire()
{
	printf("Pas assez de memoire de stockage \n");
	printf("Diminuer la taille des elements à stocker \n");
	exit(1);
}

int * alloc_tabI(int n)
{
	int *tab = calloc(n, sizeof(int)); 
    if (tab == NULL) 
		ProblemeMemoire();
	return tab;	
}


long double * alloc_tabLD(int n)
{
	long double *tab = calloc(n, sizeof(long double)); 
    if (tab == NULL) 
		ProblemeMemoire();
	return tab;	
}


long double **alloc_mat(int m,int n)// matrice non carrée (mxn) (pour la matrice Intermediare Pi*M)
{
    if(n<0 || m<0)
    {
        printf("taille non valide");
        exit(-1);
    }
    int i;
	long double ** mat = calloc(m,sizeof(long double *));
    
    if(mat == NULL)
    {
        ProblemeMemoire()   ;
    }
    for( i=0 ; i<m ; i++)
    {
        mat[i] = calloc(n,sizeof(long double));
        if(mat[i] == NULL)
            ProblemeMemoire();
    }
    //printf("OK! alloc \n");
    return mat;
}

long double *init_tab(long double *tab1, int n)
{
	for (int i = 0; i < n; i++) 
		{
			tab1[i] = 0;
		}
		return tab1;
}

long double **init_Mat(long double **Mat, int m,int n)
{
	int i,j;
	for (i = 0; i < m; i++) 
		{
			for (j = 0; j < n; j++) 
			{
				Mat[i][j] = 0;
			}
		}
		return Mat;
}


long double som_tab(long double *tab, int n)
{
	long double s=0;
	for(int i=0 ; i<n ; i++) 
	{
		s += tab[i];
	}	
	return s;
}

long double * copie(long double *tab1, int n)
{
	long double * tab2 = alloc_tabLD(n);
	for (int i = 0; i < n; i++) 
		{
			tab2[i] = tab1[i];
		}
	return tab2;	
}


int Partition(int etat,int *TabD, int *TabF, int n)
{
for( int i=0 ; i<n ; i++) 
	{
		if(etat>=TabD[i] && etat<=TabF[i])
		{
			return i;
		}
	}	
		
} 

long double * GTH (long double *piA, long double **A,int size)
{
int i,j,k,n;
long  double Tot, S;
long double *P = alloc_tabLD(size*size);

	for( i=0 ; i<size ; i++) 
	{ 
		for( j=0 ; j<size ; j++) 
			P[i*size + j] = A[i][j];	
	}

	  for (n = size-1; n >= 1; n--) {
		S = 0.0L;
		for (j = 0; j < n; j++) {
		  S +=P[n*size+j];  /* P[n,j]; */
	/*  printf("Pr %lf %lf\n", P[n*NSommets+j], S); */
		  }
		if (S == 0.0) {
		  printf("Probleme en %d %Lf\n", n,S);
		exit(1);
		}
		  for (i = 0; i < n; i++)
		  P[i*size+n] /= S; /* P[i,j]; */
		for (i = 0; i < n; i++) {
		  for (j = 0; j < n; j++) 
			P[i*size+j] += P[i*size+n] * P[n*size+j];
		}
	  }
	  Tot = 1.0L;
	  piA[0] = 1.0L;
	  for (j = 1; j < size; j++) {
		piA[j] = P[j];  /*  P[0,j] */
		for (k = 1; k < j; k++)
		  piA[j] += piA[k] * P[k*size+j]; /* P[k][j] */
		Tot += piA[j];
	  }
	  for (j = 0; j < size; j++) piA[j] /= Tot;

	
return piA;	
}

void afficherMatrice(long double **M, int n, int m)
{
int i,j;

printf("\n");
for( i=0 ; i<n ; i++)  
	{
		for( j=0 ; j<m ; j++)  
			{ 
				printf("%Lf ",M[i][j]);
			}
			printf("\n");
	}
	
}


int Index(int i,int j,int n)
{
    return (i*n+j);
}

void PrintMatrix(int s, long double *B)
{
    int i,j;
    for (i=0;i<s;i++) 
    {
        for (j=0;j<s;j++)
        {
            printf("%Lf ",B[Index(i,j,s)]);
        }
        printf("\n");
    }
}

long double ** Fundamental(FILE*fcii, int NSommets, int d, int f )
{
	int i, j, c, degre, jx, k, arcf;
	long double x,sx;
	long double *B ;

	int size = 2 * NSommets;
    B = alloc_tabLD(size*size);

	fseek( fcii, 0, SEEK_SET );
	for (i = 0; i < NSommets ; i++) {
		fscanf(fcii,"%d", &c);
		fscanf(fcii,"%d", &degre);
 		for (j = 0; j < degre; j++) {
			fscanf(fcii,"%Lf", &x);
			fscanf(fcii,"%d", &jx);
			if( c <= f && c >= d && jx <= f && jx >= d)
			{
				B[Index(NSommets+i,NSommets+jx,size)]=x;
			}
            
		}
    } 
    for (i = 0; i < NSommets ; i++) {
        B[Index(i,NSommets+i,size)]=1.0;
        B[Index(NSommets+i,i,size)]=1.0;
    }
    
    if (DEBUG==3) {PrintMatrix(size,B);}
    
    for (k=size;k!=NSommets;k--){
        for(i=0;i<k-1;i++){
            for(j=0;j<k-1;j++)
            {
                sx = B[Index(k-1,j,size)]*B[Index(i,k-1,size)];
                sx /= (1-B[Index(k-1,k-1,size)]);
                B[Index(i,j,size)] += sx;
            }
        }
        if (DEBUG==3) {
            printf("After iteration %d \n",k);
            PrintMatrix(size,B);
        }
    }
    
    arcf=0;
    for (i = 0; i<NSommets ; i++) {
        for (j=0; j<NSommets; j++) {
            x = B[Index(i,j,size)];
            if (x > EPSILON_FUND) {
                arcf++ ;
            }
            else if (x < -EPSILON_FUND){
                printf("negative value %Lf entry %d %d \n",x,i,j );
                exit(1);
            }
        }
    }
    
    long double **MatFund = alloc_mat(f-d+1,f-d+1);
    for (i = 0; i<NSommets ; i++) { //f-d+1
        for (j=0; j<NSommets; j++) {
            if  (B[Index(j,i,size)]>EPSILON_FUND && B[Index(j,i,size)] != 1 ) {
                 MatFund[i-d][j-d] = B[Index(j,i,size)]; //printf(" %d %d %Lf ",i,j, B[Index(j,i,size)]); 
            }  
        }  
          
    }
	return MatFund;
}

long double * Gauss_Seidel_Iter(long double *pi, long double *piZ, int size, int *tabD, int *tabF, int parts, FILE*fcii)
{
	int i, j, it, degre, e ,k ,t, parte;;
	long double prb; 
	long double s;
	long double **fond;
	long double *pin;
	fseek( fcii, 0, SEEK_SET );
	fpos_t pos;
	
	/*
	printf("\n");
	for( i=0 ; i<size ; i++)  
	{ 
		printf("pi[%d] = %Lf \n",i,pi[i]);
	}
	
		printf("\n");
	for( i=0 ; i<size ; i++)  
	{ 
		printf("piZ[%d] = %Lf \n",i,piZ[i]);
	}*/
	
	for( i=0 ; i<parts ; i++) 
		{
			for( j=tabD[i]; j<tabF[i]+1 ; j++) 
			{
				fscanf(fcii,"%d %d",&it,&degre);
				s = 0;
				for( t=0 ; t<degre ; t++) 
				{
					fscanf(fcii,"%Lf %d",&prb,&e);
					parte = Partition(e,tabD,tabF,parts);
					if( parte > i)
						{	
							s += piZ[e]*prb; 
						}
					if( parte < i)
						{ 
							s += pi[e]*prb; 
						} 
				}	
				pi[j] = s;
			}
			fgetpos (fcii,&pos);
			fond = Fundamental(fcii, size, tabD[i], tabF[i]);
			s = 0;
			pin = copie(pi,size);
			for( j=tabD[i]; j<tabF[i]+1 ; j++) 
			{
				s = 0;
			for( k=tabD[i]; k<tabF[i]+1 ; k++) 
				{
					s += pin[k]*fond[k - tabD[i] ][ j-tabD[i] ];
				}
			pi[j] = s;
			}
			fsetpos (fcii,&pos);
		
	}
	
	/*	printf("\n");
	for( i=0 ; i<size ; i++)  
	{ 
		printf("pi[%d] = %Lf \n",i,pi[i]);
	}*/
	
	
	/*pi[0] = 0.0000678;
	pi[1] = 0.0000745;
	pi[2] = 0.0000559; 
	pi[3] = 0.0004270;
	pi[4] = 0.0003862;
	pi[5] = 0.0000838;   
	pi[6] = 0.0000753; 
	pi[7] = 0.0000409;  */
	
		/*long double **fond;
		long double * pinew = alloc_tabLD(size);
		for( i=0 ; i<parts ; i++) 
		{
			fond = Fundamental(fcii, size, tabD[i], tabF[i]);
			for( j=tabD[i]; j<tabF[i]+1 ; j++) 
			{
				s = 0;
				for( k=tabD[i]; k<tabF[i]+1 ; k++) 
					{
						s += pi[k]*fond[k - tabD[i] ][ j-tabD[i] ];
					}
					pinew[j] = s;
			}	
		}*/

return pi; 		
}


/*long double * Gauss_Seidel_Iter(long double *pi, long double *piZ, int size, int *tabD, int *tabF, int parts, FILE*fcii)
{
	int i, j, it, degre, e;
	long double prb,prbdiag; 
	long double s;
	fseek( fcii, 0, SEEK_SET );
	
	for( i=0 ; i<size ; i++)  
	{
		fscanf(fcii,"%d %d",&it,&degre);
		s = 0;
		for( j=0 ; j<degre ; j++) 
		{
			fscanf(fcii,"%Lf %d",&prb,&e);
			if(e>i)
				s += piZ[e]*prb; //s += piZtmp[e]*prb;
			if(e<i)
				s += pi[e]*prb; //s += pitmp[e]*prb;
			if(e==i)
				prbdiag = prb;
		}	
		pi[i] = s/(1-prbdiag);
	}	

return pi; 		
}*/



int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
	int NArcs,size,i,j,k,c,parts,part,degre,e,it;
	long double s,prb;
	FILE *fsz,*fcii,*fcd,*fpi0,*fpart;
	char s1[50], s2[50],s3[50], s4[50], s5[50]; 
    
/* On recupere le nom du modele et on verifie que le fichier existe */
    if (argc!=5) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
			
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            strcpy(s2,s1); 
            strcpy(s3,s1); 
            strcpy(s4,s1); 
            strcpy(s5,s1);
            
            /* on ajoute .sz, .rii, .cd, .pi0 et .exp.part  */
            strcat(s1,".sz"); 
            strcat(s2,".cd");
            strcat(s3,".Cii");
            strcat(s4,".pi0");
            
            ++argv;
            if(strcmp(*argv,"tarjan")) usage();
            strcat(s5,".tarjan.");
            
            ++argv;
            strcat(s5,*argv);
            strcat(s5,".part");
         
		
            if ((fsz=fopen(s1,"r"))==NULL) usage();
            if ((fcd=fopen(s2,"r"))==NULL) usage();
            if ((fcii=fopen(s3,"r"))==NULL) usage();
            if ((fpi0=fopen(s4,"r"))==NULL) usage();
            if ((fpart=fopen(s5,"r"))==NULL) usage();
            break; 
        } 
        default : usage(); 
    } 
    
/* On recupere les tailles dans le fichier "model.sz" */
    fsz=fopen(s1,"r"); 
    fscanf(fsz,"%12d\n", &NArcs);  // elements non nul
    fscanf(fsz,"%12d\n",&size); // nombre d'etats
    printf("---- Algorithme  KMS ---- \nNArcs = %d size = %d ---\n",NArcs,size);
    fclose(fsz);
    
	
/* On recupére les partitions de notre chaine, lecture de "model.method.exp.part" */

	fpart=fopen(s5,"r");
	fscanf(fpart,"%d", &parts);
	int *tabD = alloc_tabI(parts);
	int *tabF = alloc_tabI(parts);
	for( i=0 ; i<parts ; i++) 
	{
		fscanf(fpart,"%d %d",&part,&degre);
		for( j=0 ; j<degre ; j++) 
		{
			fscanf(fpart,"%d",&e);
			if( j==0 )	
				tabD[part] = e;
			if( j==degre-1)
				tabF[part] = e;
		}

	}
	fclose(fpart);
	
#if (DEBUG==1)
	for( i=0 ; i<parts ; i++) 
	{
		printf("Partition[%d] = [%d,%d] \n",i,tabD[i],tabF[i]);
	}
#endif

/* 1- On recupére l'approximation de Pi dans le fichier "model.pi0" */
	
	fpi0=fopen(s4,"r");
	long double *pi = alloc_tabLD(size);
	for( i=0 ; i<size ; i++) 
	{
		fscanf(fpi0,"%Lf", &pi[i]);
	}
	fclose(fpi0);
	
#if (DEBUG==1)
	printf(" \n");
	for( i=0 ; i<size ; i++) 
	{
		printf("PI0[%d] = %Lf \n",i,pi[i] );
	}
#endif

long double *norm = alloc_tabLD(parts);
long double *phi = alloc_tabLD(size);
long double **Inter = alloc_mat(parts,size);
long double **A = alloc_mat(parts,parts);
long double *piA = alloc_tabLD(parts);
long double *piZ = alloc_tabLD(size);
long double *piAvnt;
long double diff;
int iter = 0;

do
{ // Debut de l'algo KMS

/* 2- Normalisation par block du Vecteur Pi actuelle */
++iter;
	
	for( i=0 ; i<parts ; i++) 
	{
		s = 0;
		for( j=tabD[i]; j<tabF[i]+1 ; j++) 
		{
			s += pi[j];
		}
		norm[i] = s;
	}
	
	for( i=0 ; i<parts ; i++) 
	{
		for( j=tabD[i]; j<tabF[i]+1 ; j++) 
		{
			phi[j] = pi[j]/norm[i];
		}
	}

#if (DEBUG==1 || DEBUG==2 )
	printf("\n Iteration %d",iter );
#endif

#if (DEBUG==1)
	for( i=0 ; i<size ; i++) 
	{
		printf("PHI[%d] = %Lf \n",i,phi[i] );
	}
#endif

/* 3- Construction de la matrice Intermediare (Pi*M) puis la matrice d'aggregation A */
	
	Inter = init_Mat(Inter,parts,size);
	c=0;
	for( i=0 ; i<size ; i++)  
		{
			fscanf(fcii,"%d %d",&it,&degre);
			
			for( j=0 ; j<degre ; j++) 
			{
				fscanf(fcii,"%Lf %d",&prb,&e);
				Inter[Partition(e,tabD,tabF,parts)][c] += phi[e]*prb;
			}
			c++;
		}
		

	for( i=0 ; i<parts ; i++) 
	{
		for( j=0 ; j<parts ; j++) 
			{
				s = 0;
				for( k=tabD[j] ; k<tabF[j]+1 ; k++) 
					{			
						s += Inter[i][k];
					}
			A[i][j] = s;
			}
	}

#if (DEBUG==1)
printf("\n Matrice Intermediare Inter:\n");
	for( i=0 ; i<parts ; i++) 
	{
		for( j=0 ; j<size ; j++) 
			{
				printf("%Lf ", Inter[i][j]);
			}
			printf("\n");
	}
#endif
	

#if (DEBUG==1 )	
printf("\n Matrice D'aggregation A :\n");
	for( i=0 ; i<parts ; i++) 
	{
		for( j=0 ; j<parts ; j++) 
			{
				printf("%Lf ", A[i][j]);
			}
			printf("\n");
	}
#endif

/* 4 - Resolution (Calcul de la distribution stationnaire) de la Matrice d'aggreation 'A' grâce à l'algorithme GTH (en plein) */

piA = init_tab(piA,parts);
piA = GTH(piA,A,parts);

#if (DEBUG==1)
printf("\n Distrib Stat de A :\n");
	for( i=0 ; i<parts ; i++) 
		{
			printf("%.10Le ", piA[i]);
		}
printf("\n");
#endif

/* 5 - 1 Calcul du "nouveau" vecteur de probabilité */


for( i=0 ; i<parts ; i++) 
	{
		for( j=tabD[i]; j<tabF[i]+1 ; j++) 
		{
			piZ[j] = phi[j]*piA[i];
		}
	}

#if (DEBUG==1)
printf("\nle \"nouveau\" vecteur piZ de M :\n");
	for( i=0 ; i<size ; i++) 
		{
			printf("%.10Le ", piZ[i]);
		}
printf("\n");
#endif

/* 5 - 2 Effectuer une iteration de l'agorithme itératif de gauss-seidel (ou Puissance), en prenant pi et piZ en entrée */

piAvnt = copie(pi,size);
pi = Gauss_Seidel_Iter(pi,piZ,size,tabD,tabF,parts,fcii);

/* 5 - 3 Normalisation du vecteur de proba generé par gauss-seidel (car ceci se base sur l'ancien vect de l'actuel vect de proba) */

	s = 0.0;
	for( i=0 ; i<size ; i++) { s+= pi[i]; }
	for( i=0 ; i<size ; i++) { pi[i] /= s; }


/* 5 - 4 Calcul du residu */

#if (Residu==2) //residu entre PI-Old et PI-New
 diff = 0.0;
     for (i = 0; i < size; i++) {
	  if (piAvnt[i]>0) {
		  diff += fabs(pi[i] - piAvnt[i])/piAvnt[i];
	      }
	      else {
		  diff += fabs(pi[i]);
	      }
	  }
#endif

#if (Residu==1) //residu stewart norme2(Pi- (PI*M))
 fseek( fcii, 0, SEEK_SET );
 long double * pidiff = alloc_tabLD(size);
 diff = 0.0;
     for( i=0 ; i<size ; i++)  
		{
			fscanf(fcii,"%d %d",&it,&degre);
			s = 0;
			for( j=0 ; j<degre ; j++) 
			{
				fscanf(fcii,"%Lf %d",&prb,&e);
				s += pi[e]*prb;
			}
			pidiff[i] = (pi[i] - s);
			pidiff[i] = pidiff[i]*pidiff[i];
			diff += pidiff[i];
		}
	diff = sqrtl(diff);
#endif

#if (DEBUG==1 || DEBUG==2)
printf("\n Residu %.11Le :\n", diff);
	for( i=0 ; i<size ; i++) 
		{
			printf("%.11Le ", pi[i]); //%.10Le
		}
printf("\n");
#endif	  

	

	
	

fseek( fcii, 0, SEEK_SET );
} while ((iter != maxiter) && (diff >= maxdiff) );


#if (DEBUG==0)
printf("\nIteration %d :  Residu  %.10Le \n",iter, diff);
for( i=0 ; i<size ; i++) 
		{
			printf("%.10Le ", pi[i]); //%.10Le
		}
printf("\n");
#endif

fclose(fcii);
//Fin

    exit(0); 
}

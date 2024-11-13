#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#define Buffer 250
#define DEBUG 0

void afficherEtats(int *t1,int *t2,int *t3,int *t4, long double *t5, int n)
{
	printf("[\n");
		for(int i=0;i<n;i++)
		printf("%d  %d  %d %d : %.10Le \n",t1[i],t2[i],t3[i],t4[i],t5[i]);
	printf("] \n");
}

void TrierEtats(int *t1,int *t2,int *t3,int *t4 ,long double *t5, int n) //5 éme tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1>Y2
{

 int i,tmp1,tmp2,tmp3,tmp4;
 long double tmp5;
 int en_desordre =1;


 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++)
	{
		if( (t4[i]>t4[i+1]) || (t4[i] == t4[i+1] && t3[i]>t3[i+1]) || (t4[i] == t4[i+1] && t3[i] == t3[i+1] && t2[i]>t2[i+1]) )
		{
			tmp1 = t1[i+1];
			t1[i+1] = t1[i];
			t1[i] = tmp1;

			tmp2 = t2[i+1];
			t2[i+1] = t2[i];
			t2[i] = tmp2;

			tmp3 = t3[i+1];
			t3[i+1] = t3[i];
			t3[i] = tmp3;
			
			tmp4 = t4[i+1];
			t4[i+1] = t4[i];
			t4[i] = tmp4;
			
			tmp5 = t5[i+1];
			t5[i+1] = t5[i];
			t5[i] = tmp5;


			en_desordre = 1;
		}
	}

  }
  
}


int Rechercher(int *I,int e,int n)
{
for(int i=0;i<n;i++)
	 {
		if (I[i] == e)
		return i; 	 
     }		
}



FILE* Open_file(char s[100])
{ 
	FILE *f = fopen(s,"w");
	if(f == NULL)
	exit(2);
	
	return f;
}



int main(int argc, char *argv[])
{
  
 
 FILE *fcd,*fsz,*fcdout,*fszout,*fpi,*fpiout;
 char sz[100], cd[100],szout[100], cdout[100], pi[100],piout[100];
 int *I,*X,*H,*M;
 long double *PI;
 /*int I[50000];
 int X[50000];
 int H[50000];
 int M[50000];*/
 long double proba,seuil;
 int deadline;
 int i,n1,n2,n; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 4)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./reordonner model50 seuil deadline\n");
 	exit(1);
 }
	 
	 
	 
	 strcpy(sz,argv[1]); 
	 strcpy(szout,argv[1]); 
	 strcpy(cd,argv[1]);
	 strcpy(cdout,argv[1]);
	 strcpy(pi,argv[1]);
	 strcpy(piout,argv[1]); 
	 
	 seuil = atof(argv[2])/Buffer;
	 deadline =atoi(argv[3]);
	 printf("seuil = %.10Le et deadline = %d \n",seuil,deadline);


  	 strcat(sz,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cd,".cd");
  	 strcat(pi,".pi");
  	 strcat(szout,"-reordre.sz"); 
	 strcat(cdout,"-reordre.cd");
	 strcat(piout,"-reordre.pi");


   

 fsz = fopen(sz,"r");
 if(fsz == NULL)
 exit(2);


 fcd = fopen(cd,"r");
 if(fcd == NULL)
 exit(2);


 fpi = fopen(pi,"r");
 if(fpi == NULL)
 exit(2);


 fszout = fopen(szout,"w");
 if(fszout == NULL)
 exit(2);

 
 fcdout = fopen(cdout,"w");
 if(fcdout == NULL)
 exit(2);
 
 
 fpiout = fopen(piout,"w");
 if(fpiout == NULL)
 exit(2);


/*-------------------- Lecture du fichier ".sz" et ecriture dans ".reorder.sz" --------------*/

 fscanf(fsz,"%d",&n1);
 fscanf(fsz,"%d",&n);
 fscanf(fsz,"%d",&n2);
 
 printf("n = %d \n",n);
 fprintf(fszout,"%12d \n%12d \n%12d \n",n1,n,n2);
 
 fclose(fsz);
 fclose(fszout);
 
 
/*-------------------- Lecture du fichier ".cd" et ".pi" -----------------*/

I = calloc(n,sizeof(int));
X = calloc(n,sizeof(int));
H = calloc(n,sizeof(int));
M = calloc(n,sizeof(int));
PI = calloc(n,sizeof(long double));

for(i=0;i<n;i++)
 {
	fscanf(fcd,"%d %d %d %d",&I[i],&X[i],&H[i],&M[i]);
	fscanf(fpi,"%Lf",&PI[i]);
 }

 fclose(fcd);
 fclose(fpi);


if(DEBUG == 1)
{
  printf("Avant trie :\n");
  afficherEtats(I,X,H,M,PI,n);
}

/*------------------ Tri des états !! ----------------------------*/

  TrierEtats(I,X,H,M,PI,n);


if(DEBUG == 1)
{  
  printf("\n Aprés trie :\n");
  afficherEtats(I,X,H,M,PI,n);
}

/*-----------------Ecriture du nouveau fichier reorder.cd et reorder.pi.........*/

  for(i=0;i<n;i++)
  {
	fprintf(fcdout,"%12d %12d %12d %12d \n",i,X[i],H[i],M[i]);
	fprintf(fpiout,"%.10Le \n",PI[i]);
  }
  
  fclose(fcdout);
  fclose(fpiout);
	
	
	
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#define Buffer 25
#define DEBUG 0

void afficherEtats(int t1[10000],int t2[10000],int t3[10000],int t4[10000],int n)
{
	printf("[\n");
		for(int i=0;i<n;i++)
		printf("%d  %d  %d %d \n",t1[i],t2[i],t3[i],t4[i]);
	printf("] \n");
}

void TrierEtats(int t1[10000],int t2[10000],int t3[10000],int t4[10000],int n) //5 éme tri lecxicographique: (X1,Y1)<(X2,Y2) si X1<X2 ou que X1=X2 et Y1>Y2
{

 int i,tmp1,tmp2,tmp3,tmp4;
 int en_desordre =1;


 while(en_desordre)
  {
	en_desordre = 0;

	for(i=0;i<n-1;i++) //if( (t4[i]>t4[i+1]) || (t4[i] == t4[i+1] && t3[i]>t3[i+1]) || (t4[i] == t4[i+1] && t3[i] == t3[i+1] && t2[i]>t2[i+1]) )
	{
		if( (t3[i]>t3[i+1]) || (t3[i] == t3[i+1]  && t4[i]>t4[i+1])  || (t3[i] == t3[i+1]  && t4[i] == t4[i+1] && t2[i]>t2[i+1] ) )
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


			en_desordre = 1;
		}
	}

  }
  
}


int Rechercher(int I[10000],int e,int n)
{
for(int i=0;i<n;i++)
	 {
		if (I[i] == e)
		return i; 	 
     }	

printf("Etat %d introuvable \n",e);
exit(2);	
}

void OrdonnerMatrice(FILE *frii,int I[10000],char s[100],char rii[100],int n)
{
FILE *friiout;
char  riiout[100];
int i,j,c;
int t=0;

strcpy(riiout,s);
strcat(riiout,"-reordre.Rii");

friiout = fopen(riiout,"w");
if(friiout == NULL)
 exit(2);


int iter,degre,e,k,arret;
long double proba;
c= 0;

while(c <n)
 {
	for(i=0;i<n;i++)
	 {
		fscanf(frii,"%d %d",&iter,&degre);
		if(iter == I[c])
		 {
			  fprintf(friiout,"%12d %12d ",t++,degre);
			  for(j=0;j<degre;j++)
			  {
				fscanf(frii,"%Le %d",&proba,&e);
				fprintf(friiout,"% .15LE%12d",proba,Rechercher(I,e,n)); // recherche le nouvel emplacement de l'etats
			  }
				fprintf(friiout,"\n");
			c++;	
		 }
		 else
		 {
			   for(j=0;j<degre;j++)
				fscanf(frii,"%Le %d",&proba,&e);
		 }
	 }
	 frii=fopen(rii,"r");
 }
 
 fclose(friiout);	
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
  
 
 FILE *fcd,*fsz,*fpi,*friiout,*fszout,*fcdout,*frii;
 char sz[100], cd[100], rii[100],szout[100], cdout[100];
 int I[10000];
 int X[10000];
 int H[10000];
 int M[10000];
 long double proba,seuil;
 int deadline;
 int i,n1,n2,n; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 4)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./reordonner model50 seuil deadline\n");
 	exit(1);
 }
	 
	 
	 
	 strcpy(sz,argv[1]); 
	 strcpy(cd,argv[1]);
	 strcpy(rii,argv[1]);
	 strcpy(szout,argv[1]); 
	 strcpy(cdout,argv[1]);
	 
	 seuil = atof(argv[2])/Buffer;
	 deadline =atoi(argv[3]);
	 printf("seuil = %Lf et deadline = %d \n",seuil,deadline);


  	 strcat(sz,".sz"); // On concatène chaine2 dans chaine1
  	 strcat(cd,".cd");
  	 strcat(rii,".Rii");
  	 strcat(szout,"-reordre.sz"); 
	 strcat(cdout,"-reordre.cd");


   

 fsz = fopen(sz,"r");
 if(fsz == NULL)
 exit(2);


 fcd = fopen(cd,"r");
 if(fcd == NULL)
 exit(2);


 frii = fopen(rii,"r");
 if(frii == NULL)
 exit(2);


 fszout = fopen(szout,"w");
 if(fszout == NULL)
 exit(2);

 
 fcdout = fopen(cdout,"w");
 if(fcdout == NULL)
 exit(2);


/*-------------------- Lecture du fichier ".sz" et ecriture dans ".reorder.sz" --------------*/

 fscanf(fsz,"%d",&n1);
 fscanf(fsz,"%d",&n);
 fscanf(fsz,"%d",&n2);
 printf("n = %d \n",n);
 fprintf(fszout,"%12d \n%12d \n%12d \n",n1,n,n2);
 
 
/*-------------------- Lecture du fichier ".cd" -----------------*/

for(i=0;i<n;i++)
 {
	fscanf(fcd,"%d %d %d %d",&I[i],&X[i],&H[i],&M[i]);
 }


if(DEBUG == 1)
{
  printf("Avant trie :\n");
  afficherEtats(I,X,H,M,n);
}

/*------------------ Tri des états !! ----------------------------*/

  TrierEtats(I,X,H,M,n);


if(DEBUG == 1)
{  
  printf("\n Aprés trie :\n");
  afficherEtats(I,X,H,M,n);
}

/*-----------------Ecriture du nouveau fichier reorder.cd .........*/

  for(i=0;i<n;i++)
	fprintf(fcdout,"%12d %12d %12d %12d \n",i,X[i],H[i],M[i]);
	

/*---------------- Re ordonner et ecriture de la nouvel matrice ".reorder.Rii" !! -----*/
 
  OrdonnerMatrice(frii,I,argv[1],rii,n); 
  //Decoupage_NCD(X,H,M,argv[1],seuil,deadline,n);
 

  
 
	fclose(fsz);
	fclose(fcd);
	fclose(frii);
	fclose(fszout);
	fclose(fcdout);
	
	
  return 0;
}

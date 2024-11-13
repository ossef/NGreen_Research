#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Buffer 15
#define VERSION 1 // ou 1
#define alpha01 0.1
#define alpha10 0.01


int main(int argc, char *argv[])
{
 
 FILE *fpi,*fz,*fpiout;
 char pi[100], piout[100],sz[100];
 long double proba,p;
 int i,n1,n2,n; //16 4      2.580645e-02 9 1.612903e-01 15 5.870968e-01 16 2.258065e-01 17

 
 if(argc != 2)
 {
 	printf(" Erreur passez en parametre le nom du model \n <Exemple d'usage > ./Multi model50 \n");
 	exit(1);
 }
	 
	 
	 strcpy(sz,argv[1]);
	 strcpy(pi,argv[1]); 
	 strcpy(piout,argv[1]);
	 
	 strcat(sz,".sz");
  	 strcat(pi,".pi"); 
	 strcat(piout,".pi.finale");

	 fz = fopen(sz,"r");
	 if(fz == NULL)
	 exit(2);
	 
	 fpi = fopen(pi,"r");
	 if(fpi == NULL)
	 exit(2);
	 
	 printf("%s \n",sz);
	 printf("%s \n",pi);


/*-------------------- Lecture du fichier ".sz"  --------------*/

	 fscanf(fz,"%d",&n1);
	 fscanf(fz,"%d",&n);
	 fscanf(fz,"%d",&n2);
	 printf("n = %d \n",n);
 
 
/*-------------------- Lecture du fichier ".pi" et ecriture dans ".pi.finale" -----------------*/

	p = 0;
	if(VERSION == 0)
	{	
		p = alpha01/(alpha01+alpha10);
	}
	if(VERSION == 1)
	{	
		p = alpha10/(alpha01+alpha10);
	}
	
	fpiout = fopen(piout,"w");
	for(i=0;i<n;i++)
	{
			fscanf(fpi,"%Lf",&proba);
			fprintf(fpiout," %.18Le\n", proba*p);
			//printf("tab[%d] = %.18Le \n", (proba*p)/(alpha01+alpha10));
	}
	
 
	fclose(fz);
	fclose(fpi);
	fclose(fpiout);

	
	
  return 0;
}

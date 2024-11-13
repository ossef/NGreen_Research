
/* 
 calcul de la distribution stationnaire à partir de la matrice
 transposée de la matrice de probabilites (Modele ngreen)
 
 V1.0 le 26/10/17
 
 Hypotheses  de fonctionnement : 
 l'argument est le nom du modele : filename 
 la taille est dans le fichiez filename.sz
 le codage dans filename.cd,
 la matrice est dans le fichier filename.Cii 
 */

#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define DEBUG 0
#define EPSILON 1e-10 //comparaison de flottants
#define seuil 70



long double *pi; 
FILE *fcd,*fcii,*frii,*fsz,*fpi; 
long double A,B,alpha01,alpha10;



void usage() { 
    printf("usage : ./Pi-ngreen -f filename \n");
    printf("filename.sz and filename.Cii and filename.Rii and filename.cd must exist before \n");
    exit(1); 
}

void ProblemeMemoire() { printf("Sorry, not enougth memory \n"); exit(1); }
void erreur(int ligne, char s[50]){printf("Erreur dans la ligne %d du fichier %s: format de matrice incorrecte \n",ligne,s); exit(1);}

int recherche1(int tab[],int n,int val)
{
int c = 0;
	for (int i = 0; i < n; i++) 
	{
		c += 2*tab[i];
		if(val <= c)
			return tab[i-1];
	}
printf("Erreur l'etat %d n'existe pas ! \n",val);
exit(2);
}

long double recherche2(long double tab1[],long double tab2[],int n, long double proba)
{
int i;
for (i = 0; i < n; i++) 
	{
		if( fabs(proba - tab1[i]) < EPSILON )
			return tab2[i];
	}	
	printf("erreur %Lf n'est pas dans : [",proba);
	for (i = 0; i < n; i++) printf("%Lf ,",tab1[i]);	
	printf("]\n");
	exit(2);
}


int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
	int NArcs,size,k,i,j,d,e,c;
	long double prb,som,test;
    char s1[50], s2[50], s3[50],s4[50],s5[50];
    int Deadline,it,x,h,m,Tbatch;
    
/* On recupere le nom du modele et on verifie que les fichiers existent */
    if (argc!=3) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            /* on ajoute .sz, .cd et Cii  */ 
            strcpy(s2,s1);
            strcpy(s3,s1); 
            strcpy(s4,s1); 
            strcpy(s5,s1); 
            strcat(s1,".sz"); 
            strcat(s2,".cd");
            strcat(s3,".Cii"); 
            strcat(s4,".pi"); 
            strcat(s5,".Rii");
			
            if ((fsz=fopen(s1,"r"))==NULL) usage(); 
            if ((fcd=fopen(s2,"r"))==NULL) usage(); 
            if ((fcii=fopen(s3,"r"))==NULL) usage(); 
            if ((frii=fopen(s5,"r"))==NULL) usage(); 
            
            
            break; 
        } 
        default : usage(); 
    } 
    
/* On recupere les tailles dans le fichier filename.sz */
    fsz=fopen(s1,"r"); 
    fscanf(fsz,"%12d\n", &NArcs);  // elements non nul
    fscanf(fsz,"%12d\n",&size); // nombre d'etats
    printf("NArcs = %d and size = %d\n", NArcs,size); 
    fclose(fsz); 
    
/* Extraction de proba du fichier filename.Rii*/
	frii=fopen(s5,"r");
    fscanf(frii,"%d %d", &i,&d);
    if( d != 2 || i != 0) erreur(i,s5);
	fscanf(frii,"%Lf %d %Lf %d",&A,&e,&B,&e);
	fscanf(frii,"%d %d", &i,&d);
	if(i != 1) erreur(i,s5);
	fscanf(frii,"%Lf %d", &alpha01,&e);
	long double Tprob1[d-1];
	for (k = 1; k < d; k++) 
		{
			fscanf(frii,"%Lf %d",&Tprob1[k-1],&e);
		}
	fscanf(frii,"%d %d", &i,&d);
	if(i != 2) erreur(i,s5);
	fscanf(frii,"%Lf %d", &alpha10,&e);
	Tbatch = d-1;
	long double Tprob2[Tbatch];
	for (k = 1; k < d; k++) 
		{ 
			fscanf(frii,"%Lf %d",&Tprob2[k-1],&e);
		}
	fclose(frii);
#define	conste  1/(1-alpha01*alpha10)

	
#if (DEBUG==1)
	printf("Proba : A = %Lf et B = %Lf \nAlpha01 = %Lf et Alpha10 = %Lf \n",A,B,alpha01,alpha10);
	printf("Proba du 1er batch : [");
    for (k = 0; k < Tbatch; k++) 
		{ 
			printf("%Lf ,",Tprob1[k]);
		}
	printf("] \n");
	printf("Proba du 2eme batch : [");
    for (k = 0; k < Tbatch; k++) 
		{ 
			printf("%Lf ,",Tprob2[k]);
		}
	printf("] \n");
#endif		
	

    
/* Extraction d'information du fichier filename.cd*/
	fcd=fopen(s2,"r");
	fseek ( fcd , -8*5 , SEEK_END ); //Lecture du fichier à partir de la fin
	fscanf(fcd,"%12d %12d %12d %12d", &it, &x, &Deadline, &m); //Derniere ligne du fichier
	
#if (DEBUG==1)
    printf("Derniere Ligne de '%s' :  %5d %5d %5d %5d \n",s2,it,x,Deadline,m);
#endif

    int Tab[Deadline+1];
    fseek ( fcd , 0 , SEEK_SET );
    for (i = 0; i < Deadline + 1; i++) Tab[i] = 0;
    for (i = 0; i < size; i++) 
		{
				fscanf(fcd," %12d %12d %12d %12d \n", &it, &x, &h, &m);
				if(h!=-1)
					Tab[h]++;
		}
	for (i = 0; i < Deadline + 1; i++) Tab[i] /=2;
	
#if (DEBUG==1)
    for (i = 0; i < Deadline + 1; i++)
		printf("nombre d'etats (X,%d,M) = %d \n",i,Tab[i]*2);
#endif
	fclose(fcd);
	
    
    if (!(pi=(long double*)calloc(size,sizeof(long double)))) ProblemeMemoire();   
    
/* Lecture et Traitement de la matrice de probabilité dans le fichier filename.Cii */
   fcii=fopen(s3,"r"); 
   fcd=fopen(s2,"r");
    pi[0]=1.0; som=0;
    pi[1] = (A+alpha10*B)*conste;
	pi[2] = (B+alpha01*A)*conste;
    for (k = 0; k < size; k++) {
		fscanf(fcd," %12d %12d %12d %12d \n", &it, &x, &h, &m);
        fscanf(fcii,"%d %d", &i,&d);
        if( it != i ) erreur(it,s2);
        if(i==0 || i==1 || i==2)
        {
			for (j = 0; j < d; j++) 
			{
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
			}
        } 
        if((i>2) && (x<=seuil) && ( h != Deadline) )
		{
		  if(m == 0)
		  {
			for (j = 0; j < d; j++) 
			  {
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
				if(e<i)
					{
						  pi[i] += ((prb*pi[e])*conste);
						  //printf("Ligne %d : Transition vers %d avec proba %Lf \n",i,e+recherche1(Tab,Deadline+1,i),recherche2(Tprob1,Tprob2,Tbatch,prb));
						  pi[i] += ((alpha10*recherche2(Tprob1,Tprob2,Tbatch,prb)*pi[e+recherche1(Tab,Deadline+1,i)])*conste);
					}
			  }
		   }
		
		 if( m == 1)
			{	
			  
			  for (j = 0; j < d; j++) 
			  {
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
				pi[i] += (prb*pi[e]);
			  }
			}
		}
		if( (x>seuil) || (h == Deadline) )
		{
			for (j = 0; j < d; j++) 
			  {
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
				pi[i] += (prb*pi[e]);
			  }
		 }
					
	 }//fin k	 
	fclose(fcii); 
    fclose(fcd);
  
/* Normalisation et test de somme de proba */
    for (k = 1; k < size; k++) { som += pi[k];}
    pi[0] = 1/(1+som);
#if (DEBUG==1)
    printf("pi[0] =%.18Le \n",pi[0]);
#endif
    test = pi[0];
    for (k = 1; k < size; k++) {
		pi[k] *= pi[0];
		test += pi[k];
#if (DEBUG==1)
		printf("pi[%d] =%.18Le \n",k,pi[k]);
#endif
	}
#if (DEBUG==1)
    printf("somme de proba = %.18Le \n",test);
#endif 

/*Ecriture du resultat dans un fichier*/
    fpi=fopen(s4,"w");
    for (k = 0; k < size; k++)  fprintf(fpi," %.18Le\n", pi[k]); //%.18Le
    printf("Distribtion Stationnaire dans '%s' \n",s4);
    fclose(fpi);  
  
    exit(0); 
}

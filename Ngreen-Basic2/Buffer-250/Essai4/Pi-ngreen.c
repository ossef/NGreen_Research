
/* 
 calcul de la distribution stationnaire à partir de la matrice,
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


long double *pi; 
FILE *fcd,*fcii,*fsz,*fpi; 



void usage() { 
    printf("usage : ./Pi-ngreen -f filename \n");
    printf("filename.sz and filename.Cii and filename.cd must exist before \n");
    exit(1); 
}

void ProblemeMemoire() { printf("Sorry, not enougth memory \n"); exit(1); }


int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
	int NArcs,size,k,i,j,d,e;
	long double prb,som,test;
    char s1[200]; 
    char s2[200]; 
    char s3[200]; 
    char s4[200];
    double seuil;
    int Deadline;
    
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
            strcat(s1,".sz"); 
            strcat(s2,".cd");
            strcat(s3,".Cii"); 
            strcat(s4,".pi"); 
			
            if ((fsz=fopen(s1,"r"))==NULL) usage(); 
            if ((fcd=fopen(s2,"r"))==NULL) usage(); 
            if ((fcii=fopen(s3,"r"))==NULL) usage(); 
            
            
            break; 
        } 
        default : usage(); 
    } 
    
/* On recupere les tailles dans le fichier filename.sz */
    fsz=fopen(s1,"r"); 
    fscanf(fsz,"%12d\n", &NArcs);  // elements non nul
    fscanf(fsz,"%12d\n",&size); // nombre d'etats
    printf("Dist stat chaine : NArcs = %d and size = %d\n", NArcs,size); 
    fclose(fsz); 

  
    
    if (!(pi=(long double*)calloc(size,sizeof(long double)))) ProblemeMemoire();
    
    
/* Lecture de la matrice de probabilité dans le fichier filename.Cii */
    fcii=fopen(s3,"r"); 
    pi[0]=1.0; som=0;
    for (k = 0; k < size; k++) {
        fscanf(fcii,"%d %d", &i,&d);
        if(i==0)
        {
			for (j = 0; j < d; j++) 
			{
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
			}
        } 
		else
		{
        for (j = 0; j < d; j++) 
			{
				fscanf(fcii,"%Lf",&prb);
				fscanf(fcii,"%d",&e);
				if(e>i){printf("Erreur le graphe de votre chaine ne respecte pas les conditions ! \nLes conditions :"); 
						printf("une transition dans votre graphe d'un etat i vers un etat j doit respecter le fait que i<=j, sauf pour les transitions vers l'etat 0 \n"); 
						exit(0);}
				pi[i] += prb*pi[e];
			}
		} 
    }
	fclose(fcii); 
    
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
    for (k = 0; k < size; k++)  fprintf(fpi," %.18Le\n", pi[k]);
    fclose(fpi);
    
   
    exit(0); 
}

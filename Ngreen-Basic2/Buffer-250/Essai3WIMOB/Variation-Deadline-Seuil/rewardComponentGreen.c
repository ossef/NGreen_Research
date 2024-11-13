// fichier rewardComponent.c pour modele ngreen

/* 
 calcul des recompenses a partir de la matrice,
 des probabilites stationnaires, du codage des etats des composantes
 
 V2.0 le 04/05/16
 
 Hypotheses  de fonctionnement : 
 l'argument est le nom du modele : filename 
 la taille est dans le fichiez filename.sz
 le codage dans filename.cd, 
 et la distribution dans filename.pi
 */

#include <stdio.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


/* 
 inclusions des constantes, types et variables particulieres a chaque modele
 */

#include "const.h"



/* Variables donnant l'etendue de chaque variable isolee */ 
int Min[NEt],Max[NEt]; 
typedef int Etat[NEt];

/* Le nombre d'etats atteignables et de transitions */ 

int ReachableStates, NArcs;

/* la distribution stationnaire et la marginale en cours */ 

double *pi; 
long double *marginale;
int *et;


FILE *pf1; 


//#include "fun.c" 
#include "funRewardGreen.c"


void usage() { 
    printf("usage : RewardComponent -f filename seuil deadline\n");
    printf("filename.pi, filename.sz and filename.cd must exist before \n");
    exit(1); 
}

void ProblemeMemoire() { printf("Sorry, not enougth memory \n"); exit(1); }

int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
    int i,j, k, plusieur, nb ; 
    int comp; 
    int maxcompsize; 
    long double Mean, Deviate; 
    char s1[50]; 
    char s2[50]; 
    char s3[50]; 
    char s4[50];
    char s5[50];
    char s6[50];
    char s7[50];
    char s8[100];
    double seuil;
    int Deadline;
    
    /* On recupere le nom du modele et on verifie que les fichiers existent */
    if (argc!=5) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            /* on ajoute .sz, .pi et .cd */ 
            strcpy(s2,s1);
            strcpy(s3,s1); 
            strcpy(s4,s1); 
            strcpy(s5,s1); 
            strcpy(s6,s1);
            strcpy(s7,s1);
            strcpy(s8,s1);
       
            strcat(s1,".sz"); 
            strcat(s2,".pi");
            strcat(s3,".cd"); 
            strcat(s4,".resultat"); 
            strcat(s5,".MargCd.X.pi");
            strcat(s6,".MargCd.H.pi");
            strcat(s8,".Conv.H.G.pi");
            strcat(s7,".pi.Trunc");
             
			
            if ((pf1=fopen(s1,"r"))==NULL) usage(); 
            if ((pf1=fopen(s2,"r"))==NULL) usage(); 
            if ((pf1=fopen(s3,"r"))==NULL) usage(); 
            
            seuil = atof(*(++argv))/Buffer;
			Deadline =atoi (*(++argv));
            
            break; 
        } 
        default : usage(); 
    } 
    
    /* On recupere les tailles dans le fichier filename.sz */
    pf1=fopen(s1,"r"); 
    fscanf(pf1,"%12d\n", &NArcs);  // elements non nul
    fscanf(pf1,"%12d\n",&ReachableStates); // nombre d'etats
    /*printf("%12d\n", NArcs); 
    printf("%12d\n",ReachableStates); */
    fclose(pf1); 

  
    
    if (!(pi=(double*)malloc(ReachableStates*sizeof(double)))) ProblemeMemoire(); 
    if (!(et=(int*)malloc(ReachableStates*NEt*sizeof(int)))) ProblemeMemoire();
    
    
    /* Lecture de la matrice de codage dans le fichier filename.cd */
    pf1=fopen(s3,"r"); 
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%d", &j);
        for (i = 0; i < NEt; i++) {
            fscanf(pf1,"%d",&nb);
            et[i+NEt*j] = nb; 
        } /*et[j][i] */ 
        getc(pf1);
    }
    fclose(pf1);
    
    /*   Lecture du vecteur pi dans le fichier filename.pi */
    pf1=fopen(s2,"r");
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%lf \n", &pi[k]); 
    }
    fclose(pf1);
    
 
    
    /* Calcul du nombre moyen de client en attente dans la file  */
    
    long double NombreMoyn = NombreMoyen(et,pi,ReachableStates,seuil,Deadline); 
    
    /* Calcul des marginales simple par rapport à X, puis par rapport à H */   
    
    /*Marg1_Marg2(et,pi,ReachableStates,seuil,Deadline);*/
    
    /* Calcul des marginales conditionnée à la sortie par rapport à H puis X */
     
    
    
    pf1=fopen(s4,"a");
    fprintf(pf1,"Buffer = %d       ", Buffer);
    fprintf(pf1,"Seuil = %f           ", seuil*Buffer);
    fprintf(pf1,"Horloge = %d             ", Deadline);
    fprintf(pf1,"NbreMoy = %.18Le\n"  , NombreMoyn); 
    
    char str1[20] = "";
    char str2[20] = "";
    sprintf(str1, ".%d.", Deadline);
    strcat(s8,str1);
    sprintf(str2, "%d", (int)(seuil*Buffer));
    strcat(s8,str2);
    Convolution_H_G(et,pi,ReachableStates,seuil,Deadline,s5,s6,s8); 
	Pi_troncer(pi,ReachableStates,s7);
   
    
    fprintf(pf1,"\n");
    
    fclose(pf1);
    //printf("Done RewardComponent\n");
    exit(0); 
}


/* 

 * Youssef V1.0 le 01/03/2018
 
 * Generation du vecteur de probabilité initiale pour l'algorithme KMS
   Ce vecteur est une approximation de la vrai valeur de la distribution stationnaire
   plus cette approx s'approche de la dist stationnaire, moins d'iteration l'algorithme KMS effectuera
   Dans un premier temps on génére une approx : [1/N, 1/N, ... 1/N] 
 
 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>



void usage() { 
    printf("usage : ./GenApprox -f filename \n");
    printf("filename.sz must exist before \n");
    exit(1); 
}


int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
	int NArcs,size;
	FILE *fsz,*fpi0;
	char s1[50], s2[50]; 
    
/* On recupere le nom du modele et on verifie que le fichier existe */
    if (argc!=3) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            strcpy(s2,s1); 
            
            /* on ajoute .sz et .pi0 */
            
            strcat(s1,".sz"); 
            strcat(s2,".pi0"); 
            
            if ((fsz=fopen(s1,"r"))==NULL) usage();
            break; 
        } 
        default : usage(); 
    } 
    
/* On recupere les tailles dans le fichier filename.sz */
    fsz=fopen(s1,"r"); 
    fscanf(fsz,"%12d\n", &NArcs);  // elements non nul
    fscanf(fsz,"%12d\n",&size); // nombre d'etats
    fclose(fsz);
    
/* On ecrit l'approximation 1/N dans le fichier "filenale.pi0" */
	
	fpi0=fopen(s2,"w");
	for (int i = 0; i < size; i++) {
		fprintf(fpi0," %.15Le\n", ((long double)(1))/size);
	}
	fclose(fpi0);
	printf("\n L'approximation est dans le fichier '%s' \n\n",s2);

  

    exit(0); 
}

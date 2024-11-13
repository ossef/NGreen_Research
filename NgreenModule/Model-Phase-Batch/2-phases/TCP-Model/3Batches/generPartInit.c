
/* 

 * Youssef V1.0 le 01/03/2018
 
 * Generation d'une partition initiale, qui sera ensuite utilisé pour l'algorithme de Tarjan
 * L'algorithme de Tarjan prend en entré une partition initiale et génère une partition aggrégé (Si la matrice est Lumpable/Quasi-Lumpable) 
 
 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>



void usage() { 
    printf("usage : ./GenPart -f filename \n");
    printf("filename.sz must exist before \n");
    exit(1); 
}


int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
	int NArcs,size;
	FILE *fsz,*fpart;
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
            strcat(s2,".tarjan.exp1.part"); 
            
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
	int i;
	if(size %2 == 1)
	{
		printf("Probleme de taille, la tailles de votre matrice doit être paire \n");
		exit(0);
	}
	fpart=fopen(s2,"w");
	fprintf(fpart," 2 \n");
	fprintf(fpart," 0 %d  ", size/2);
	for (i = 0; i < size/2; i++) {
		fprintf(fpart," %d ", i);
	}
	fprintf(fpart,"\n");
	fprintf(fpart," 1 %d  ",size/2);
	for (i = size/2; i < size; i++) {
		fprintf(fpart," %d ", i);
	}
	fclose(fpart);
	printf("\n Partition initiale dans le fichier '%s' \n\n",s2);

  

    exit(0); 
}

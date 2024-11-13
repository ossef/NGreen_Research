/*-----------------------------------------------------------*/
/* Modele Insertion dans l'anneau - mode Deterministe, neccesite un fichier temps - proba   */
/*-----------------------------------------------------------*/

/* composants */
/* 0 : population dans la file */
/* 1 : etat du controle de puissance */
/* codage 0 : OFF */
/*        1 : allume mais pas encore operationel */
/*        2 : allume, operationnel */
/* codage des evenements */
/* 1  : arrivee dans la file  */
/* 2  : service   */
/* 3  : allumage des serveurs  */
/* 4  : uniformisation loop   */

#define min(a,b) (a<=b?a:b)
#define max(a,b) (a<=b?b:a)

#define BufferSize 4 // !!! pour une modification du buffersize : assurer vous que le define BufferSize et la variable BufferSize dans le script shell ayent a même valeure
#define D 22 //15 //Deterministe
#define MaxAttente 60

int *Tab1 ;
double *Tab2 ;

void InitEtendue()
{
    Min[0] = 0;  Max[0] = D-1;
    Min[1] = 0;  Max[1] = MaxAttente;
	Min[2] = 0;  Max[2] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0; E[2] = 0;
}

void Lecture()
{
	printf("Lecrtue1 \n");
	int i,n;
	double som = 0;
	Tab1 = calloc(NbEvtsPossibles, sizeof(int)); // Nbre d'attente
    Tab2 =  calloc(NbEvtsPossibles, sizeof(long double)); //proba d'attente
	FILE *pf1;
    if ((pf1 = fopen("mod2-250-D40-Thr190.pi","r")) == NULL){fclose(pf1); printf("Fichier non trouvé ! \n"); exit(0);} //  if ((pf1 = fopen("TestProba.pi","r")) == NULL){fclose(pf1); printf("Fichier non trouvé ! \n"); exit(0);}
	fscanf(pf1,"%d",&n);
	if(n != NbEvtsPossibles ) {printf("Assurez vous que le nombre d'event possible est bien celui dans l'entête de votre fichier entrée"); exit(0);}
    for ( i=0; i<2*NbEvtsPossibles ; i++) {
		fscanf(pf1,"%d %lf",&Tab1[i],&Tab2[i]);
	}
	for ( i=0; i<NbEvtsPossibles ; i++) {
		printf("%d   %.10lf\n",Tab1[i],Tab2[i]);
	}	
	
	for ( i=0; i<NbEvtsPossibles ; i++) {
		som += Tab2[i];
	}
	Tab2[NbEvtsPossibles-1] += 1-som; 
	fclose(pf1);
}

double Probabilite(int indexevt, int *E)
{
	return Tab2[indexevt-1];
}

void Equation(int *E, int indexevt, int *F, int *R)
{
    F[0] = E[0]; 
    F[1] = E[1]; 
    F[2] = E[2];
    
    /*-----Deuxieme horloge H2 : horloge des arrivées ---------*/
	if(F[1]>0)
    {
		F[1]--;
	}
	else
	{
		F[1] = Tab1[indexevt-1]-1;
		F[2] = min(F[2]+1,BufferSize);
	}
	
    /*------Premiere horloge H1 : horloge des departs (services) ---------*/
    if(F[0]>0) 
    {
		F[0]--;
	}
	else
	{
		F[0] = D-1;
		F[2] = max(0,F[2]-1);
	}
	
	
	
}


void InitParticuliere()
{
}

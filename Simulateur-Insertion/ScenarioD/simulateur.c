#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include  <string.h>

#define DEBUG 0

#define TIMEMAX 10000   //temps max de simulation ?
#define TAILLEMAX 150 //taille de l'anneau
#define STATIONS 18 //nombre de stations
#define DEADLINE 108 //Deadline tronquée liée à la distribution de H conv G  (voir modèle Buffer25)
#define BUFFER 700 // taille du conteneur de PDUs (taille echeancier)
#define PERIODE 10 //Periode d'attente avnt re-emission de paquets



int Anneau[TAILLEMAX]; // l'anneau est remplit par des slots contenant (-1 pour vide  ou l'indice de l'emetteur)
int TrainD[TAILLEMAX]; //tableau contenant le nombre d'occurence des tailles de train à partir de 1
int TrainF[TAILLEMAX];
long double FctRepart[DEADLINE+1];
int DateArrivee[STATIONS][BUFFER]; // Echeancier pour chaque Station
int ProchArrivee[STATIONS];
int Delai[STATIONS][BUFFER];  //Delai d'attente pour chaque evennement
int IndiceEvent[STATIONS];   //Indice de l'element à oter
int DeltaStation[STATIONS];  //Periode d'attente avant re-emission d'une station
int PlaceStation[STATIONS];  //Emplacement d'une station dans un anneau
int NbrePDUs[STATIONS];
int Compteurs[STATIONS];
long double Moyenne = 0; //Moyenne de la duree de remplissage (de la loi convolue)
int MaxTrain; //tailleMax d'un train dans l'anneau


void affiche_Anneau()
{
	for (int i=0; i<TAILLEMAX; i++) {
		printf("Anneau[%d] = %d \n",i,Anneau[i]);
	}
	
}

void decalage_Anneau()
{
	int tmp = Anneau[TAILLEMAX- 1];
	memmove(&Anneau[1], Anneau, (TAILLEMAX - 1) * sizeof(int));
	Anneau[0] = tmp;
}

void Generer_Fonct_Repart()
{
	int i,j,m;

    FILE *f1 = fopen("test-ngreen-mod2-250.Conv.H.G.pi","r");
    FILE *f4 = fopen("FctRepart2.data","w");
	if (f1 == NULL) 	
		{
			printf("Erreur de lecture du fichier \n");
			exit(0);
		}
		
	for ( i=0; i<DEADLINE+1 ; i++) {
		fscanf(f1,"%d %Lf",&m,&FctRepart[i]);
		Moyenne += i*FctRepart[i]; //Moyenne
	}

	
	for ( i=1; i<DEADLINE+1 ; i++) {
			FctRepart[i] += FctRepart[i-1];
	}
	
	for ( i=0; i<DEADLINE+1 ; i++) {
		fprintf(f4,"%5d %Lf \n",i,FctRepart[i]);
	}

	
#if (DEBUG==1)	
	for ( i=0; i<DEADLINE+1 ; i++) {
		printf("FctRepart[%d] = %Lf \n",i,FctRepart[i]);
	}
#endif
	
	fclose(f4);
	fclose(f1);
}

int transform_inverse(FILE*f3) // retourne la durée d'un evenement selon H
{

	long double r = (long double)rand() / (long double)RAND_MAX;
		   for (int i=0; i<DEADLINE+1 ; i++) 
		   {
			  if(r<=FctRepart[i])
			  {	
				fprintf(f3,"%5d %Lf %Lf \n",i,FctRepart[i],r);
				return i;
			 }
		   }
  
}

int Nbre_Slot_Remplie()
{
	int n = 0;
	for (int i=0; i<TAILLEMAX; i++) {
		if(Anneau[i] != -1)
			n++;	
	}
	return n;
}


void init_Anneau(FILE*f3)
{
	int i,r,j;
	for ( i=0; i<TAILLEMAX; i++) {
		Anneau[i] = -1;//rand()%TAILLEMAX; // =-1
	}
	for ( i=0; i<STATIONS; i++) {
		DeltaStation[i] = 0;
		PlaceStation[i] = ((int)(TAILLEMAX/STATIONS))*i;
		IndiceEvent[i] = 0;
		
		if( i >= STATIONS/2) //(i+1)%2 == 1 && (i+1)%3 !=0 )
		{ r = 15; }
		else{ r = transform_inverse(f3); }
		
		ProchArrivee[i] = r;
		NbrePDUs[i] = 0;
		Compteurs[i] = 0;
		
		for ( j=0; j<BUFFER; j++) 
		{
			Delai[i][j] = -1;
			DateArrivee[i][j] = -1;
		}
	}
}

void Recherche_Train()
{
int i,j,c;
int var1 = 0;
int max = -1;
i = 0;
MaxTrain = 0;
while(i<TAILLEMAX)
 {
	 if(Anneau[i] != -1)
	 {
		 c =1;
		 TrainD[var1] = i;
		 	for ( j=i+1; j<TAILLEMAX; j++)
		 	{
			  if(Anneau[j] != -1)
			  {
				 c++; 
			  }
			  else
			  {
				 break;
			  }
			}
		TrainF[var1] = i+c-1;
		var1++;
		i += c;
	 }
	 else
	 {
		 i++;
	 }
 }	
 if(TrainD[0] == 0 && TrainF[var1-1] == TAILLEMAX-1 && var1>1)
 {
	 TrainF[0] += TrainF[var1-1] - TrainD[var1-1] + 1;
	 var1--;
 }
 
 /*for ( i=0; i<var1; i++) 
 {
	fprintf(f7,"%5d \n",TrainF[i] - TrainD[i] + 1);	
 }*/
 
 
 for ( i=0; i<var1; i++) 
 {
	 if(TrainF[i] - TrainD[i] + 1 > MaxTrain)
	 {
		MaxTrain =  TrainF[i] - TrainD[i] + 1; //MAJ de la variable global max
	 } 
 }
 
}


int main(int argc,char *argv[])
{
int t,i,j,duree,e,som1,som2,train;
FILE *f1 = fopen("NbreMoyen.res","w");
FILE *f2 = fopen("Delai.res","w");
FILE *f3 = fopen("FctRepart.data","w");
FILE *f5 = fopen("Remplissage.data","w");
FILE *f6 = fopen("MeanFilling.data","a");
FILE *f7 = fopen("Train.data","w");
FILE *f8 = fopen("MaxTrain.data","a");

srand(time(NULL));
Generer_Fonct_Repart();

init_Anneau(f3);
printf("ANNEAU INITIALE ! \n");
affiche_Anneau();
printf("\n");

som1= 0;
som2= 0;
t = 0;
 do 
 {
	fprintf(f1,"%5d",t); 
	fprintf(f5,"%10d%5d \n",t,Nbre_Slot_Remplie());
		if(t>=2000)
		{
			som1 += Nbre_Slot_Remplie();
			som2 += MaxTrain;
			fprintf(f7,"%6d %5d \n",t,MaxTrain);
		}
			
	Recherche_Train(f7);
	
	
	for ( i=0; i<STATIONS; i++) 
	{
	fprintf(f1,"%10d",Compteurs[i]); // affichage #waiting PDUs 
	
	if( i >= STATIONS/2) //(i+1)%2 == 1 && (i+1)%3 !=0 )
	{
	#if (DEBUG==1)		
			printf("t = %d, File %d : ProchaineArrivee = %d , Delta = %d \n",t,i,ProchArrivee[i],DeltaStation[i]);
	#endif
			if( t == ProchArrivee[i] )// ajout d'une arrive dans la file
			{
				DateArrivee[i][NbrePDUs[i]++] = t;	
				ProchArrivee[i] += 15;
				Compteurs[i]++;
			}
			
			if(Anneau[PlaceStation[i]] == PlaceStation[i])  //Je reçoit mon PDU, alors Nettoyage
			{
				Anneau[PlaceStation[i]] = -1;
			}
			
			if(Anneau[PlaceStation[i]] == -1 && DeltaStation[i] == 0 && NbrePDUs[i]>0 && DateArrivee[i][IndiceEvent[i]] != -1) //Je reçois un Slot vide et delai d'emission atteint, et file non vide 
			{ 																			//je peut emettre un PDU dans l'anneau, et j'obtient mon delai
				Anneau[PlaceStation[i]] = PlaceStation[i];	//MAJ de l'anneau
				DeltaStation[i] = PERIODE;				   //MAJ de la periode avant re-envoie
				Delai[i][IndiceEvent[i]] = t - DateArrivee[i][IndiceEvent[i]]; //MAJ du delai d'attente
				printf("Omettre la date %d de l'echeancier \n",DateArrivee[i][IndiceEvent[i]]);
				IndiceEvent[i]++; //Passage a l'arrivee suivante
				Compteurs[i]--;
			}
	}
	else
	{
	#if (DEBUG==1)		
			printf("t = %d, File %d : ProchaineArrivee = %d , Delta = %d \n",t,i,ProchArrivee[i],DeltaStation[i]);
	#endif
			if( t == ProchArrivee[i] )// ajout d'une arrive dans la file
			{
				DateArrivee[i][NbrePDUs[i]++] = t;	
				ProchArrivee[i] += transform_inverse(f3);
				Compteurs[i]++;
			}
			
			if(Anneau[PlaceStation[i]] == PlaceStation[i])  //Je reçoit mon PDU, alors Nettoyage
			{
				Anneau[PlaceStation[i]] = -1;
			}
			else
			{
				if(Anneau[PlaceStation[i]] == -1 && DeltaStation[i] == 0 && NbrePDUs[i]>0 && DateArrivee[i][IndiceEvent[i]] != -1) //Je reçoit un Slot vide et delai d'emission atteint, et file non vide 
				{ 																			//je peut emettre un PDU dans l'anneau, et j'obtient mon delai
					Anneau[PlaceStation[i]] = PlaceStation[i];	//MAJ de l'anneau
					DeltaStation[i] = PERIODE;				   //MAJ de la periode avant re-envoie
					Delai[i][IndiceEvent[i]] = t - DateArrivee[i][IndiceEvent[i]]; //MAJ du delai d'attente
					printf("Omettre la date %d de l'echeancier \n",DateArrivee[i][IndiceEvent[i]]);
					IndiceEvent[i]++; //Passage a l'arrivee suivante
					Compteurs[i]--;
				}
			}
		}

	    
#if (DEBUG==1)	    
		printf("Dates Arrivée : \n");
		for ( j=0; j<BUFFER ; j++) {
		 printf(" %d  ", DateArrivee[i][j] );
		}
		printf("\n");
		
#endif
		
		
	}//fin for
	fprintf(f1,"\n");
	
	for ( i=0; i<STATIONS; i++) 
	{
	  if(DeltaStation[i]>0)
			DeltaStation[i]--;	
	}
	
	printf("\nAprès %d clock \n",t);
	//affiche_Anneau();

	printf("Aprés decalage \n");	
	decalage_Anneau();		
	//affiche_Anneau();	
	
	t++;	
  } while (t < TIMEMAX+1);	


#if (DEBUG==1)	    
	
	printf("\n Affichage Final \n");
	for ( i=0; i<STATIONS ; i++) 
	{
		printf(" Station %d : \n",i);
		for ( t=0; t<BUFFER ; t++) {
		 printf(" %d  %d \n", DateArrivee[i][t],Delai[i][t] );
		}
		printf("\n");
	}
	
#endif

printf("Les files speciales : ");
for ( i=0; i<STATIONS ; i++) 
	{
		if( i >= STATIONS/2) //(i+1)%2 == 1 && (i+1)%3 !=0 )
		{
			printf("%d - ",i);
		}
	}
	printf("\n");

fprintf(f8,"%5d	    %Lf \n",STATIONS,(long double)(som2)/(long double)(TIMEMAX-2000+1) );	// Moyenne de TrainMax trouvé
fprintf(f6,"%5d		%Lf\n",STATIONS,(long double)(som1)/(long double)(TIMEMAX-2000+1)  ); // remplissage de l'anneau
for ( t=0; t<BUFFER ; t++) 
	{
		for ( i=0; i<STATIONS ; i++) {
		 fprintf(f2,"%10d%10d", DateArrivee[i][t],Delai[i][t] );
		}
		fprintf(f2,"\n");
	}
	printf("Proprieté d'une file special : Priorité + Duree \n");
	printf("Duree moyenne de remplissage d'un PDU en file speciale : 15 \n");
	printf("Duree moyenne de remplissage d'un PDU en file normal   : %Lf \n",Moyenne);

fclose(f1);
fclose(f2);
fclose(f3);
fclose(f5);
fclose(f6);
fclose(f7);
fclose(f8);
exit(0);
}





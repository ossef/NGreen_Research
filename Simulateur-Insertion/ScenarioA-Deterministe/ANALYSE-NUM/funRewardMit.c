// funreward for Deterministic model for the insertion of PDUs

#include "fun.c" 
#define ARRIVEE 31

double proba_perte(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

double perte = 0;

for(int i=0; i<taille*3 ; i=i+3){
        if(tab[i+1] == 0 && tab[i+2] == BufferSize )
			perte += pi[(int)i/3] ;
    }   
return perte; 		
}

void TempsInsertion(int tab[],double pi[],int taille,char s4[50]) 
{
int i;
double somme = 0;
double tmp = 0;
double moyenne = 0;
double test = 0;

strcat(s4,".InsertionTime");
FILE *f1 = fopen(s4,"w");

for(i=0; i<taille*3 ; i=i+3){
	if(tab[i+1] == 0 && tab[i+2]<BufferSize)
	{
		somme += pi[(int)i/3] ;	
 	}
}	

for(i=0; i<taille*3 ; i=i+3){
	if(tab[i+1] == 0)
	{
		if( (tab[i]+(tab[i+2]*D)) != D)
		{
			fprintf(f1,"%5d   %.15E \n",(tab[i]+(tab[i+2]*D)),pi[(int)i/3]/somme);	
			moyenne += (tab[i]+(tab[i+2]*D))*(pi[(int)i/3]/somme);
			test += pi[(int)i/3]/somme;
		}
		else
		{
			printf("Etat : (%d, %d, %d) \n",tab[i],tab[i+1],tab[i+2]);
			tmp += pi[(int)i/3]/somme;
			test += pi[(int)i/3]/somme;
		}
 	}
}
fprintf(f1,"%5d   %.15E \n",D,tmp);
moyenne += D*tmp;	

	
printf("La moyenne d'insertion = %f et somme = %f\n",moyenne,test);
	
}

double NombreMoyen(int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
double NbreMoy = 0;	

for(int i=0; i<taille*3 ; i=i+3){     
        NbreMoy += tab[i+2]*pi[(int)i/3];
    }   	
	
return NbreMoy;	
}



double TempAttente(double NbreMoyAtt){   // Temps moyen des clients en attente (loi de little : Ta = Na/Lambda et Ts = Ns/Lambda)
	return NbreMoyAtt/ARRIVEE;
}



















// funreward for ngreen model


#include "fun.c" 
#define DEBUG 0
#define EPSILON 1e-30





long double NombreMoyen(int tab[],double pi[],int taille,double seuil,int Deadline) // nombre moyen de paquets qui sortent
{
long double NbreMoy = 0;	
int i;

for(i=0; i<taille*2 ; i=i+2){ 
			if(tab[i+1] == Deadline || tab[i]>seuil*Buffer) 
			{
					NbreMoy += tab[i]*pi[(int)i/2];
			}
    }   	
	
return NbreMoy;	
}

void Marg1_Marg2(int tab[],double pi[],int taille,double seuil,int Deadline) // Marginale Normale
{
long double proba1,proba2;
proba1 = proba2 = 0;	
int i,j;
long double tab1[taille];
long double tab2[Deadline+1];


for(i=0; i<taille ; i=i+1){ tab1[i] = 0;}
for(i=0; i<=Deadline ; i=i+1){ tab2[i] = 0;}  

for(i=0; i<taille*2 ; i=i+2){ 
				if(tab1[tab[i]] == 0)
				{
					proba1=0;
					for(j=0; j<taille*2 ; j=j+2){
						if(tab[j] == tab[i])
							proba1 +=  pi[(int)j/2];
						}
						tab1[tab[i]] = proba1;
						printf("X = %d : %.18Le\n",tab[i],proba1);
				}
			}	
printf("\n ---------- \n");		
for(i=0; i<taille*2 ; i=i+2){ 
				if(tab2[tab[i+1]] == 0)
				{
					proba2=0;
					for(j=0; j<taille*2 ; j=j+2){
						if(tab[j+1] == tab[i+1])
							proba2 +=  pi[(int)j/2];
						}
						tab2[tab[i+1]] = proba2;
						printf("H = %d : %.18Le\n",tab[i+1],proba2);
				}
			}	
}

void Marg_Cond_X_H(int tab[],double pi[],int taille,double seuil,int Deadline,char s5[50],char s6[50]) // Marginal conditionnée sur X et H(en sortie)
{
long double som,s1,s2,test;
long double tab1[(int)(seuil*Buffer)+a[NbEvtsPossibles-1] + 1];
long double tab2[Deadline+1];
FILE *f1,*f2;
int i,j;
som = 0;	

for(i=0; i<taille*2 ; i=i+2){ 
			if(tab[i+1] == Deadline || tab[i]>seuil*Buffer) 
			{
					som += pi[(int)i/2];
			}
    }  
    
#if (DEBUG==1)		
		printf("somme = %.18Le\n",som); 
#endif

for(i=0; i<(int)(seuil*Buffer)+a[NbEvtsPossibles-1] + 1 ; i=i+1){ tab1[i] = 0;}
for(i=0; i<Deadline+1; i=i+1){ tab2[i] = 0;}

for(i=0; i<taille*2 ; i=i+2)
			{ 
				if(tab[i+1] == Deadline || tab[i]>seuil*Buffer)
				{
						tab1[tab[i]] += pi[(int)i/2];
						tab2[tab[i+1]] += pi[(int)i/2];
				}
			}
			
f1=fopen(s5,"w");
	for(i=0; i<(int)(seuil*Buffer)+a[NbEvtsPossibles-1] + 1 ; i=i+1){ 
	 tab1[i] /= som;
#if (DEBUG==1)	
	printf("tab1[%d] =      %.18Le\n",i,tab1[i]);
#endif
	test += tab1[i];
	if(tab1[i]>0)
	fprintf(f1,"%d      %.18Le\n",i,tab1[i]);
	}
#if (DEBUG==1)	
	printf("Somme de proba : %.18Le\n",test);
#endif
fclose(f1);

#if (DEBUG==1)	
	printf("\n -------------------- \n");
#endif

f2=fopen(s6,"w");
	for(i=0; i<Deadline+1; i=i+1){
#if (DEBUG==1)	
	printf("tab2[%d] =      %.18Le\n",i,tab2[i]);
#endif
	tab2[i] /= som;
	fprintf(f2,"%d      %.18Le\n",i,tab2[i]);
	}
fclose(f2);

}

void Pi_troncer(double pi[],int taille,char s7[50])
{
FILE *file = fopen(s7,"w");
	for(int i=0; i<taille; i++){
		if(pi[i]<EPSILON)
			pi[i] = EPSILON;
			fprintf(file,"%.18le\n",pi[i]);
	}	
fclose(file);	
}



















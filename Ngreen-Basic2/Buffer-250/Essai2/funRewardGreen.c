// funreward for ngreen model


#include "fun.c" 
#define DEBUG 0
#define EPSILON 1e-30
#define EPSTRONQUE 1e-15




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

long double* Marg_Cond_X_H(int tab[],double pi[],int taille,double seuil,int Deadline,char s5[50],char s6[50]) // Marginal conditionnée sur X et H(en sortie)
{
long double som,s1,s2,test;
long double *tab1 = calloc((int)(seuil*Buffer)+a[NbEvtsPossibles-1] + 1,sizeof(long double));
long double *tab2 = calloc(Deadline+1,sizeof(long double));

FILE *f1,*f2, *f3;
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


for(i=0; i<taille*2 ; i=i+2)
			{ 
				if(tab[i+1] == Deadline || tab[i]>seuil*Buffer)
				{
						tab1[tab[i]] += pi[(int)i/2];
						tab2[tab[i+1]] += pi[(int)i/2];
				}
			}
test = 0;			
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
	tab2[i] /= som;
#if (DEBUG==1)	
	printf("tab2[%d] =      %.18Le\n",i,tab2[i]);
#endif
	fprintf(f2,"%d      %.18Le\n",i,tab2[i]);
	}
fclose(f2);

/*
f3 = fopen("Resultats.data","a");
	som =0;
	for(i=0; i<Deadline+1; i=i+1){
	 som += i*tab2[i];
	}
fprintf(f3,"%5d  %Lf ",Deadline,som);
	if(seuil*Buffer > 540)
		fprintf(f3,"\n");
fclose(f3);*/

	som =0;
	for(i=0; i<(int)(seuil*Buffer)+a[NbEvtsPossibles-1] + 1 ; i=i+1){ 
	som += i*tab1[i];
	}
	printf("La moyenne de la taille des PDUs 'X' : %Lf \n",som);
	
    som = 0;
	for(i=0; i<Deadline+1; i=i+1){
		som += i*tab2[i];	
	}
	printf("La moyenne du temps de ramplissage 'H' est : %Lf \n",som);

return tab2; // Je retourne la distribution du timer
}


double Geometrique(double param, int k) /*-------- Calucle de (1-param)^k*param ---------- */
{ 
 //if(param<0 || param>1) {printf("Erreur loi Geometrique: assurez vous p soit dans [0,1] \n"); exit(0);}
 return k<=0 ? 0 : pow(1-param,k-1)*(param) ;

}

void Convolution_H_G(int tab[],double pi[],int taille,double seuil,int Deadline,char s5[50],char s6[50],char s7[50]) /*------- Convolution du timer H et de G qui suit une loi geomtrique de (1-p(a[0])) -------*/
{ 
 long double s = 0;
 long double *tab2 = calloc(Deadline+1,sizeof(long double));
 tab2 = Marg_Cond_X_H(et,pi,ReachableStates,seuil,Deadline,s5,s6); 
 long double *tabConv;
 
 int i,x,h;
 for(i=0; i<NbEvtsPossibles; i++){ if(a[i] == 0) break; }
 if(i<NbEvtsPossibles) // on a bien une arrivée avec 0 SDU ==> Calcule de la convolution
	{
	   if(i!=0) {printf("Erreur Convolution_H_G : Veuillez mettre l'arrivée de '0' SDU au dèbut de votre Batch d'arrivée"); exit(0);}
	   double param = p0;
	   int tronque = 1 + (int)(log10(EPSTRONQUE)/log10(1-param));
	   printf("TRONQUE = %d \n",tronque);
	   int taille = Deadline+1+tronque;
       tabConv = calloc(taille,sizeof(long double));
	   for(x=0; x<taille; x++)
			{
				for( h=0; h<Deadline+1; h++)
				{
					tabConv[x] += tab2[h]*(Geometrique(1-param,x-h));	
					//printf("TabH[%d] = %Lf x Geomtrique (%d) = %f, produit = %Lf \n",h,tab2[h],x-h,Geometrique(param,x-h),tab2[h]*Geometrique(param,x-h));
				} 
			} 
		
		FILE *f1=fopen(s7,"w");
		long double som =0;
		for(x=0; x<taille; x++){ som += tabConv[x];} 
		printf("Somme de proba : %Lf \n",som);
		for(x=0; x<taille; x++)
				{
					tabConv[x] /= som;
#if (DEBUG==1)	
					printf("TabConv[%d] =   %.18Le\n",x,tabConv[x]);
#endif
					fprintf(f1,"%d      %.18Le\n",x,tabConv[x]);
				} 
		fclose(f1);
		
	    som = 0;
		for(i=0; i<taille; i=i+1){
			som += i*tabConv[i];	
		}
	printf("La moyenne le la loi Convolue est : %Lf \n",som);	
	}	
 	
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





















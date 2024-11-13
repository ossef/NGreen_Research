// funreward for ngreen model


#include "fun.c" 
#define DEBUG 0
#define EPSILON 1e-30
#define EPSTRONQUE 1e-15


long double NombreMoyen(int tab[],double pi[],int taille,double seuil,int Deadline) // nombre moyen de paquets qui sortent
{
long double NbreMoy = 0;	
int i;

for(i=0; i<taille*3 ; i=i+3){ 
			if(tab[i+1] == Deadline || tab[i]>seuil*Buffer) 
			{
					NbreMoy += tab[i]*pi[(int)i/3];
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

for(i=0; i<taille*3 ; i=i+3){ 
				if(tab1[tab[i]] == 0)
				{
					proba1=0;
					for(j=0; j<taille*3 ; j=j+3){
						if(tab[j] == tab[i])
							proba1 +=  pi[(int)j/3];
						}
						tab1[tab[i]] = proba1;
						printf("X = %d : %.18Le\n",tab[i],proba1);
				}
			}	
printf("\n ---------- \n");		
for(i=0; i<taille*3 ; i=i+3){ 
				if(tab2[tab[i+1]] == 0)
				{
					proba2=0;
					for(j=0; j<taille*3 ; j=j+3){
						if(tab[j+1] == tab[i+1])
							proba2 +=  pi[(int)j/3];
						}
						tab2[tab[i+1]] = proba2;
						printf("H = %d : %.18Le\n",tab[i+1],proba2);
				}
			}	
}

long double*  Marg_Cond_X_H(int tab[],double pi[],int taille,double seuil,int Deadline,char s5[50],char s6[50]) // Marginal conditionnée sur X et H(en sortie)
{
long double som,s1,s2,test;
long double *tab1 = calloc((int)(seuil*Buffer)+a0[(NbEvtsPossibles/2)-1] + 1,sizeof(long double));
long double *tab2 = calloc(Deadline+1,sizeof(long double));

FILE *f1,*f2;
int i,j;
som = 0;	

for(i=0; i<taille*3 ; i=i+3){ 
			if(tab[i+1] == Deadline || tab[i]>seuil*Buffer) 
			{
					som += pi[(int)i/3];
			}
    }  
    
#if (DEBUG==1)		
		printf("somme = %.18Le\n",som); 
#endif


for(i=0; i<taille*3 ; i=i+3)
			{ 
				if(tab[i+1] == Deadline || tab[i]>seuil*Buffer)
				{
						tab1[tab[i]] += pi[(int)i/3];
						tab2[tab[i+1]] += pi[(int)i/3];
				}
			}
test = 0;			
f1=fopen(s5,"w");
	for(i=0; i<(int)(seuil*Buffer)+a0[(NbEvtsPossibles/2)-1] + 1 ; i=i+1){ 
	 tab1[i] /= som;
#if (DEBUG==1)	
	printf("tab1[%d] =      %.18Le\n",i,tab1[i]);
#endif
	test += tab1[i];
	//if(tab1[i]>0)
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
	
	som = 0;
	for(i=0; i<(int)(seuil*Buffer)+a0[(NbEvtsPossibles/2)-1] + 1 ; i=i+1){ 
	som += i*tab1[i];
	}
	printf("La moyenne le la loi X est : %Lf \n",som);
	
	som = 0;
	for(i=0; i<Deadline+1; i=i+1){
		som += i*tab2[i];	
	}
	printf("La moyenne le la loi H est : %Lf \n",som);
return tab2; // Je retourne la distribution du timer
}

double Geometrique(double param, int k) /*-------- Calucle de (1-param)^k*param ---------- */
{ 
 //if(param<0 || param>1) {printf("Erreur loi Geometrique: assurez vous p soit dans [0,1] \n"); exit(0);}
 return k<=0 ? 0 : pow(1-param,k-1)*(param) ;

}

int min(int a, int b)
{
	return a<=b ? a:b;
}

void Convolution_H_G(int tab[],double pi[],int taille,double seuil,int Deadline,char s5[50],char s6[50],char s7[50]) //------- Convolution du timer H et de G qui suit une loi geomtrique de (1-p(a[0])) -------
{ 
 long double s = 0;
 long double *tab2 = calloc(Deadline+1,sizeof(long double));
 tab2 = Marg_Cond_X_H(et,pi,ReachableStates,seuil,Deadline,s5,s6); 
 long double *tabConv1;
 int tronque1,tronque2,taille1;
 double proba1 = 0.0099; // proba etre dans l'etat 0
 double proba2 = 0.9900; // proba etre dans l'etat 1
 
 int i,j,x,h;
 for(i=0; i<NbEvtsPossibles/2; i++){ if(a0[i] == 0) break; }
 for(j=0; j<NbEvtsPossibles/2; j++){ if(a1[j] == 0) break; }
 
 if(i<NbEvtsPossibles/2 && j<NbEvtsPossibles/2) // on a bien une arrivée avec 0 SDU dans chaque batch ==> Calcule de la convolution
	{
	   if(i!=0 || j!=0) {printf("Erreur Convolution_H_G : Veuillez mettre l'arrivée de '0' SDU au dèbut de vos deux Batchs d'arrivée"); exit(0);}
	   double param1 = p00;
	   double param2 = p10;
	   tronque1 = 1 + (int)(log10(EPSTRONQUE)/log10(1-param1));
	   tronque2 = 1 + (int)(log10(EPSTRONQUE)/log10(1-param2));
	   printf("TRONQUE1 = %d et  TRONQUE2 = %d  \n",tronque1,tronque2);
	   taille1 = Deadline+1+min(tronque1,tronque2);
       tabConv1 = calloc(taille1,sizeof(long double));
	   for(x=0; x<taille1; x++)
			{
				for( h=0; h<Deadline+1; h++)
				{
					tabConv1[x] += tab2[h]*(proba1*Geometrique(1-param1,x-h) + proba2*Geometrique(1-param2,x-h));	
					//printf("TabH[%d] = %Lf x Geomtrique (%d) = %f, produit = %Lf \n",h,tab2[h],x-h,Geometrique(param,x-h),tab2[h]*Geometrique(param,x-h));
				} 
			} 
		
		FILE *file = fopen(s7,"w");	
		long double som1 =0;
		for(x=0; x<taille1; x++){ som1 += tabConv1[x];} 
		printf("Somme de proba : %Lf \n",som1);
		for(x=0; x<taille1; x++)
				{
					//tabConv1[x] /= som1;
#if (DEBUG==1)	
					printf("TabConv1[%d] =   %.18Le\n",x,tabConv1[x]);
#endif				
					fprintf(file,"%d         %.18Le\n",x,tabConv1[x]);
				} 
		fclose(file);
			
		s = 0;
		for(i=0; i<taille1; i=i+1){
			s += i*tabConv1[i];	
		}
	printf("La moyenne de la loi Convolue est : %Lf \n",s);	//doit être : (Moyenne de H) + 0.0099*(1/0.55) + 0.99*(1/0.95) 	
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



















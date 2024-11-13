#Execution : R CMD BATCH "--args $STATIONS $TIMEMAX" Draw.R

variables = commandArgs(trailingOnly=TRUE)
STATIONS = as.numeric(variables[1])
TIMEMAX = as.numeric(variables[2])


#-------------CourbeLines of Waiting PDUs -----------------
modelname1 = "NbreMoyen.res"
data1 = read.table(modelname1)
attach(data1);
t =V1

temp = (data1[TIMEMAX+1,]); #TIMEMAX+1
temp [1] = -1;
Max = max(temp);

#----------------------------------------------------CAMEMBERT POUR LA STATION 1---------------------------------------

valeurs = table(data1[,2]) #station 1 :  Calculer pourcentages correspondant à chaque valeurs
total = sum(valeurs)
pourcentages = valeurs/total*100 ;

sink('pourcentage.txt') #J'affiche le pourcentage dans un autre fichier
	cat(pourcentages,"\n")
sink()

data4 = read.table("pourcentage.txt")
attach(data4)

# Fonction à coller dans R - cette fonction text_pie permet d'ajouter des étiquettes au centre des quartiers
text_pie = function(vector,labels=c(),cex=1) {
     vector = vector/sum(vector)*2*pi
     temp = c()
     j = 0
     l = 0
     for (i in 1:length(vector)) {
          k = vector[i]/2         
          j =  j+l+k
          l = k
          text(cos(j)/2,sin(j)/2,labels[i],cex=cex)
     }
     vector = temp
}

        if(length(data4[1,]) == 8){
		pie(table(data1[,2]),col=c("pink","green","yellow","blue","red","brown","cyan","white"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDU","5 PDU","6 PDUs","7 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%"),paste0(round(data4[1,][7], 2),"%"),paste0(round(data4[1,][8], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 7){
		pie(table(data1[,2]),col=c("pink","green","yellow","blue","red","brown","cyan"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDU","5 PDU","6 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%"),paste0(round(data4[1,][7], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 6){
		pie(table(data1[,2]),col=c("pink","green","yellow","blue","red","brown"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDUs","5 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 5){
		pie(table(data1[,2]),col=c("pink","green","yellow","blue","red"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 4){
		pie(table(data1[,2]),col=c("pink","green","yellow","blue"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 3){
		pie(table(data1[,2]),col=c("pink","green","yellow"),labels=c("0 PDU","1 PDU","2 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 2){
		pie(table(data1[,2]),col=c("pink","green"),labels=c("0 PDU","1 PDU"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 1){
		pie(table(data1[,2]),col=c("pink"),labels=c("0 PDU"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%")),cex=1.5) 
		}


#----------------------------------------------------FIN CAMEMBERT STATION 1----------------------------------------------------

ma_seq=seq(2,STATIONS+1,by=1) # de 2 à STATIONS+1


for (i in ma_seq)
{ #pour chaque Station : plot #Waiting PDUs
	plot(t,data1[,i],type="s",col="black",xlab="Time", ylab="Waiting PDUs")
	if( (i-1)>= STATIONS/2 + 1){ #if( (i-1)%%2 !=0  && (i-1)%%3 !=0){
	legend("topright", legend=c(paste("Station **",i-1)),col=c("black"))
	}
	else
	{
	legend("topright", legend=c(paste("Station ",i-1)),col=c("black"))	
	}
	
	tab = table(data1[,i])
	
	if( (i-1) == 1){
		sink(paste0("file",(i-1)))
			cat("Pour la file ",i-1,"\n",tab)
				tab
		sink()
	}
	
	if( (i-1) == 8){
		sink(paste0("file",(i-1)))
			cat("Pour la file ",i-1,"\n",tab)
				tab
		sink()
	}
	
	
	tab = table(data1[,i])
	barplot(tab ,xlab = "Waiting PDUs",ylab = "Occurency",col = "blue", border = "black")
	if( (i-1)>= STATIONS/2 + 1){ #if( (i-1)%%2 !=0  && (i-1)%%3 !=0){
	legend("topright", legend=c(paste("Station **",i-1)),col=c("blue"))
	}
	else
	{
	legend("topright", legend=c(paste("Station ",i-1)),col=c("blue"))	
	}

	
	valeurs = table(data1[,i]) #station 1 :  Calculer pourcentages correspondant à chaque valeurs
	total = sum(valeurs)
	pourcentages = valeurs/total*100 ;

	sink('pourcentage.txt') #J'affiche le pourcentage dans un autre fichier
		cat(pourcentages,"\n")
	sink()

	data4 = read.table("pourcentage.txt")
	attach(data4)
	
	text_pie = function(vector,labels=c(),cex=1) {
     vector = vector/sum(vector)*2*pi
     temp = c()
     j = 0
     l = 0
     for (i in 1:length(vector)) {
          k = vector[i]/2         
          j =  j+l+k
          l = k
          text(cos(j)/2,sin(j)/2,labels[i],cex=cex)
     }
     vector = temp
}

        if(length(data4[1,]) == 8){
		pie(table(data1[,i]),col=c("pink","green","yellow","blue","red","brown","cyan","white"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDU","5 PDU","6 PDUs","7 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%"),paste0(round(data4[1,][7], 2),"%"),paste0(round(data4[1,][8], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 7){
		pie(table(data1[,i]),col=c("pink","green","yellow","blue","red","brown","cyan"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDU","5 PDU","6 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%"),paste0(round(data4[1,][7], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 6){
		pie(table(data1[,i]),col=c("pink","green","yellow","blue","red","brown"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDUs","5 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%"),paste0(round(data4[1,][6], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 5){
		pie(table(data1[,i]),col=c("pink","green","yellow","blue","red"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs","4 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%"),paste0(round(data4[1,][5], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 4){
		pie(table(data1[,i]),col=c("pink","green","yellow","blue"),labels=c("0 PDU","1 PDU","2 PDUs","3 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%"),paste0(round(data4[1,][4], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 3){
		pie(table(data1[,i]),col=c("pink","green","yellow"),labels=c("0 PDU","1 PDU","2 PDUs"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%"),paste0(round(data4[1,][3], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 2){
		pie(table(data1[,i]),col=c("pink","green"),labels=c("0 PDU","1 PDU"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%"),paste0(round(data4[1,][2], 2),"%")),cex=1.5) 
		}
		if(length(data4[1,]) == 1){
		pie(table(data1[,i]),col=c("pink"),labels=c("0 PDU"),cex=1.5) 
		text_pie(data4[1,],c(paste0(round(data4[1,][1], 2),"%")),cex=1.5) 
		}
}


#-------------CourbeLines of Time delai -----------------
modelname2 = "Delai.res"
data2 = read.table(modelname2)
attach(data2);

ma_seq=seq(1,(2*STATIONS)-1,by=2) # de 1 à (2*STATIONS)-1


tab = table(data2[,2])
tab = data.frame(tab) 
sink('DelaiFirstStat.txt') #J'affiche le pourcentage dans un autre fichier
	tab
	tab[,1]
	som = sum(as.vector(tab[,2]))
	tab[,2]/som
	
	#som = sum(as.vector(tab[1:length(tab[,2]),2]))
	#cat("\n Somme =",som,"\n");
	#as.vector(tab[,2])/sum(as.vector(tab[,2]))
	
	
sink()




for (i in ma_seq){ #pour chaque Station son propre plot
plot(data2[,i],data2[,i+1],type="s",col="black",xlab="Arrival date of PDUs", ylab="Delay", xlim=c(0,10000), ylim=c(0,100))#,xlim=c(0,m1), ylim=c(0,m2))
if( (i+1)/2 >= STATIONS/2 + 1 ){ #if( ((i+1)/2)%%2 !=0  && ((i+1)/2)%%3 !=0){
legend("topleft", legend=c(paste("Station **",(i+1)/2)),col=c("black"))
}
else{
legend("topleft", legend=c(paste("Station",(i+1)/2)),col=c("black"))	
}

tab = table(data2[,i+1])
tab = data.frame(tab) 
som = sum(as.vector(tab[,2]))
barplot(as.vector(tab[,2])/som, names.arg=as.vector(tab[,1]),xlab = "Delay",ylim = c(0,0.15),ylab = "Probability",col = "blue", border = "black")
if( (i+1)/2 >= STATIONS/2 + 1 ){ #if( ((i+1)/2)%%2 !=0  && ((i+1)/2)%%3 !=0){
legend("topright", legend=c(paste0("Station **",(i+1)/2)),col=c("blue"))
}
else{
legend("topright", legend=c(paste("Station",(i+1)/2)),col=c("blue"))	
}
}


#-------------CourbeLines de l'anneau -----------------
modelname3 = "Remplissage.data"
data3 = read.table(modelname3)
attach(data3);

plot(V1,V2,type="l",col="black",xlab="time", ylab="Filled slots")


#-------------CourbeLines de l'anneau -----------------

pdf(file=STATIONS)

modelname5 = "Train.data"
data5 = read.table(modelname5)
attach(data5);

tab = table(data5[,2])
tab = data.frame(tab) 
som = sum(as.vector(tab[,2]))
barplot(as.vector(tab[,2])/som, names.arg=as.vector(tab[,1]),xlab = "Maxtrain",ylim = c(0,0.40),ylab = "Probability",col = "blue", border = "black")
legend("topleft",legend=c(paste(STATIONS,"stations"))

dev.off()

#plot(t,N1,type="S",col="red",xlab="Time", ylab="# Waiting PDUs")
#lines(t,N2,type="S",col="black")
#legend("top", legend=c("ESLB","ELB"),
#       col=c("blue","red"), lty=1:1, cex=1.3)









#Execution : R CMD BATCH  Draw.R




#-------------Courbe1 -----------------
modelname1 = "Remplissage-Vs-Stats.data"
data1 = read.table(modelname1)
attach(data1);

par(mar=c(5,4,2,5))

plot(V1,V2,type="o", pch=15,las=1,lab=c(10, 6, 1),ylim=c(50,150),col="black",xlab="Number of stations",ylab="")
mtext("Number of filled slots",side=2,line=2.5)










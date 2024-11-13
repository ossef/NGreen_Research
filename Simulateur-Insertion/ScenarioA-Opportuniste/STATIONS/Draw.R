#Execution : R CMD BATCH  Draw.R




#-------------Courbe1 -----------------
modelname1 = "MeanFilling.data"
data1 = read.table(modelname1)
attach(data1);

par(mar=c(5,4,2,5))

plot(V1,V2,type="o",las=1,lab=c(10, 6, 1),ylim=c(0,150), pch=16,col="black",xlab="Number of stations",ylab="")
mtext("Number of filled slots",side=2,line=2.5)

#barplot(as.vector(tab[2:length(tab[,1]),2]), names.arg=as.vector(tab[2:length(tab[,1]),1]),xlab = "Delay",ylab = "Occurency",col = "blue", main = paste("Occurency of time Delay, station",(i+1)/2), border = "black")



#-------------Courbe1 -----------------
modelname2 = "MaxTrain.data"
data2 = read.table(modelname2)
attach(data2);

par(new=T)

plot(V1,V2,type="o",las=1,lab=c(10, 6, 1),ylim=c(0,150), pch=15,col="red",xlab="",ylab="")

#axis(1,pretty(range(V1),10))
#mtext("Number of stations",side=1,col="black",line=2.5)
legend(x="topleft",legend=c("Mean Number","Mean of max trains"),text.col=c("black","red"),pch=c(16,15),col=c("black","red"))









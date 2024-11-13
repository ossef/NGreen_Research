

modelname = "Moyenne.data"
data = read.table(modelname)
attach(data);


plot(V1,V2,type="o",las=1,lab=c(10, 6, 1),ylim=c(0,150), pch=15,col="red",xlab="stations",ylab="")

legend(x="topleft",legend=c("Mean of max trains"),text.col=c("red"),pch=c(15),col=c("red"))


variables = commandArgs(trailingOnly=TRUE)

#modelname2 = "ResultatsX.data"

#---------------------Courbes1 : Mean time de remplissage -------------------

colors = c("red","blue","green") 
ma_seq=seq(3,5 ,by=1) # de 1 à (2*STATIONS)-1

modelname1 = "End-To-End.res"
data1 = read.table(modelname1)
attach(data1);

Deadline = data1[,1]
plot(Deadline,data1[,2],type="o",las=1,lwd=2.5, pch=3,ylim=c(160,200), col="black",xlab="Deadline", ylab="Mean Sejourn Time (in time slots)")
legend(x="topleft",legend=c("Thr = 90%","Thr = 80%","Thr = 70%","Thr = 60%"),text.col=c("green","blue","red","black"),col=c("green","blue","red","black"),lty=1:1, cex=1.2) 


const1 = 1
for (i in ma_seq){ 
lines(Deadline,data1[,i],type="o",las=1, pch=3, col=colors[const1])
const1 = const1 +1
}




#-----------------Courbe2 : Mean taux de remplissage ------------------------

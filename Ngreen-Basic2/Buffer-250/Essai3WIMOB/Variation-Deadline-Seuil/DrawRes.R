#Execution : R CMD BATCH "Draw.R"

variables = commandArgs(trailingOnly=TRUE)

#modelname2 = "ResultatsX.data"

#---------------------Courbes1 : Mean time de remplissage -------------------

colors = c("red","blue","green") 
ma_seq=seq(4,8 ,by=2) # de 1 à (2*STATIONS)-1

modelname1 = "ResultatsH.data"
data1 = read.table(modelname1)
attach(data1);

Deadline = data1[,1]
plot(Deadline,data1[,2],type="o",las=1, pch=3,ylim=c(5,40), lwd=2.5, col="black",xlab="C", ylab="Mean time of PDU's filling")
legend(x="topleft",legend=c("Thr = 90%","Thr = 80%","Thr = 70%","Thr = 60%"),text.col=c("green","blue","red","black"),col=c("green","blue","red","black"),lty=1:1, cex=1.2) 


const1 = 1
for (i in ma_seq){ 
lines(Deadline,data1[,i],type="o",lwd=2.5,las=1, pch=3, col=colors[const1])
const1 = const1 +1
}

x = c(30,40,40,40)
y = c(22.360072 ,28.068516,30.919263,32.023956)
points(x,y,pch=5, cex=1.75, col="blue")



#-----------------Courbe2 : Mean taux de remplissage ------------------------



modelname2 = "ResultatsX.data"
data2 = read.table(modelname2)
attach(data2);

Deadline = data2[,1]
plot(Deadline,data2[,2],type="o",las=1,lwd=2.5, pch=3, col="black",xlab="C",ylim=c(50,250), ylab="Number of chunks in PDU")
legend(x="topleft",legend=c("Thr = 90%","Thr = 80%","Thr = 70%","Thr = 60%"),text.col=c("green","blue","red","black"),col=c("green","blue","red","black"),lty=1:1, cex=1.2) 

const1 = 1
for (i in ma_seq){ 
lines(Deadline,data2[,i],type="o",lwd=2.5,  pch=3, las=1,col=colors[const1])
const1 = const1 +1

}

#-----------------Courbe3 : Efficacité énergetique ------------------------

colors2 = c("blue","red","black") 

modelname3 = "ResultatsE.data"
data3 = read.table(modelname3)
attach(data3);

Deadline = data3[,1]
plot(Deadline,data3[,2],type="o",las=1,lwd=2.5, pch=3, col="black",xlab="Deadline",ylim=c(0.5,3), ylab="Energy efficiency (nJoule/bit)")
legend(x="topright",legend=c("Thr = 90%","Thr = 80%","Thr = 70%","Thr = 60%"),text.col=c("green","blue","red","black"),col=c("green","blue","red","black"),lty=1:1, cex=1.2) 


const1 = 1
for (i in ma_seq){ 
lines(Deadline,data3[,i],type="o",lwd=2.5,  pch=3, las=1,col=colors[const1])
const1 = const1 +1
}









#Execution : R CMD BATCH "Draw.R"

variables = commandArgs(trailingOnly=TRUE)

#modelname2 = "ResultatsX.data"

#---------------------Courbe1-------------------

colors = c("red","blue","brown") 
ma_seq=seq(4,8 ,by=2) # de 1 à (2*STATIONS)-1

modelname1 = "ResultatsH.data"
data1 = read.table(modelname1)
attach(data1);

Deadline = data1[,1]
plot(Deadline,data1[,2],type="o",las=1, pch=3,ylim=c(0,35), col="black",xlab="C", ylab="Mean time of PDU's filling")
text(50, 8.8, "Thr = 0.28" , cex=0.9, pos=3,col="black") 


const1 = 1
const2 = 12
const3 = 0.44
for (i in ma_seq){ 
lines(Deadline,data1[,i],type="o",las=1, pch=3, col=colors[const1])
text(50, const2,paste("Thr =",const3), cex=0.9, pos=3,col=colors[const1]) 
const1 = const1 +1
const2 = const2 +5
const3 = const3 +0.16
}


#-----------------Courbe2------------------------

modelname2 = "ResultatsX.data"
data2 = read.table(modelname2)
attach(data2);

Deadline = data2[,1]
plot(Deadline,data2[,2],type="o",las=1, pch=3, ylim=c(0,0.90), col="black",xlab="C", ylab="#SDUs/J : (filling rate of PDU)")
text(50, 0.37, "Thr = 0.28" , cex=0.9, pos=3,col="black") 

const1 = 1
const2 = 0.50
const3 = 0.44
for (i in ma_seq){ 
lines(Deadline,data2[,i],type="o",  pch=3, las=1,col=colors[const1])
text(50, const2,paste("Thr =",const3), cex=0.9, pos=3,col=colors[const1]) 
const1 = const1 +1
const2 = const2 +0.17
const3 = const3 +0.16
}












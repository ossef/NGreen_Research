#Execution : R CMD BATCH "Draw.R"

variables = commandArgs(trailingOnly=TRUE)
modelname1 = "test-ngreen-250-DAG.cd"
modelname2 = "test-ngreen-250-DAG.pi"
modelname3 = "test-ngreen-250-DAG.MargCd.X.pi"
modelname4 = "test-ngreen-250-DAG.MargCd.H.pi"
modelname5 = "test-ngreen-250-DAG.Conv.H.G.pi"

data1 = read.table(modelname1)
attach(data1);
i =V1
X =V2
H =V3


data2 = read.table(modelname2)
attach(data2);
Pi =V1


library(lattice)

#-------------3Dimension---------------

levelplot(
  Pi ~ X*H, 
  xlab = "X", ylab = "H",
  sub="Parametres: J=250, J*0.76 = 190 and C = 40",
  colorkey = TRUE,
  col.regions = topo.colors(100)[length(topo.colors(100)):1] #heat.colors(100)[length(heat.colors(100)):2]  #cm terrain topo heat
)



#-------------Courbe1-----------------
data3 = read.table(modelname3)
attach(data3);
x =V1
pi1 =V2



barplot(pi1,names.arg = x,xlab = "x : Number of SDUs in PDU",ylab = "PrX(x)",col = "blue",border = "black")
abline(v=228.5, col="Red",lwd="2",lty=1)
legend("topleft", legend=c("probability","Threshold"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(x,pi1,type="h",xlab="X",ylab="Marginale sortie de X")
#title("Courbe de la marginale conditionnel sur les paquets qui sortent") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)

#--------------Courbe2-----------------

data4 = read.table(modelname4)
attach(data4);
h =V1
pi2 =V2

barplot(pi2,names.arg = h,xlab = "t",ylab = "PrH(t)",col = "blue", border = "black")
abline(v=48, col="Red",lwd="3",lty=1)
legend("topleft", legend=c("probability","Timer deadline"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(h,pi2,type="h",xlab="H",ylab="Marginale sortie de H")
#title("Courbe de la marginale conditionnel sur l'horloge") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)

data5 = read.table(modelname5)
attach(data5);
h =V1
piConv =V2

barplot(piConv,names.arg = h, xlab = "t",ylab = "PrH_G(t)",col = "blue", border = "black")
legend("topleft", legend=c("probability"),
       col=c("blue"), lty=1:1, cex=1.3)

#plot(h,pi2,type="h",xlab="H",ylab="Marginale sortie de H")
#title("Courbe de la marginale conditionnel sur l'horloge") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)




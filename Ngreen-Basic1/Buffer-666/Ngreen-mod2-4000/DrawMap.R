#Execution : R CMD BATCH "Draw.R"

variables = commandArgs(trailingOnly=TRUE)
modelname1 = "test-ngreen-mod2-666-DAG.cd"
modelname2 = "test-ngreen-mod2-666-DAG.pi.Trunc"
modelname3 = "test-ngreen-mod2-666-DAG.MargCd.X.pi"
modelname4 = "test-ngreen-mod2-666-DAG.MargCd.H.pi"

data1 = read.table(modelname1)
attach(data1);
i =V1
X =V2
H =V3


data2 = read.table(modelname2)
attach(data2);
Pi =V1


library(lattice)

levelplot(
  log10(Pi) ~ X*H, 
  xlab = "X", ylab = "H",
  main = "Stationnary distribution",
  col.regions = topo.colors(20)  #cm terrain topo heat
)

data3 = read.table(modelname3)
attach(data3);
x =V1
pi1 =V2

plot(x,pi1,type="l",xlab="X",ylab="Marginale sortie de X")
title("Courbe de la marginale conditionnel sur les paquets qui sortent") 
legend(40, 0.145, legend=c("Pi0"),
       col=c("black"), lty=1:1, cex=1.2)

data4 = read.table(modelname4)
attach(data4);
h =V1
pi2 =V2

plot(h,pi2,type="l",xlab="H",ylab="Marginale sortie de H")
title("Courbe de la marginale conditionnel sur l'horloge") 
legend(40, 0.145, legend=c("Pi0"),
       col=c("black"), lty=1:1, cex=1.2)




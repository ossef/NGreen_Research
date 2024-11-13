#Execution : R CMD BATCH "Draw.R"

variables = commandArgs(trailingOnly=TRUE)
modelname1 = "test-ngreen-10-DAG.cd"
modelname2 = "test-ngreen-10-DAG.pi"
modelname3 = "test-ngreen-10-DAG.MargCd.X.pi"
modelname4 = "test-ngreen-10-DAG.MargCd.H.pi"

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
  main = "Stationnary distribution",
  col=color.palette(30)  #col.regions = topo.colors(20)  #cm terrain topo heat
)

levelplot(
  Pi ~ X*H, 
  xlab = "X", ylab = "H",
  main = "Stationnary distribution",
  col.regions = heat.colors(20)  #cm terrain topo heat
)

levelplot(
  Pi ~ X*H, 
  xlab = "X", ylab = "H",
  main = "Stationnary distribution",
  col.regions = terrain.colors(20)  #cm terrain topo heat
)

levelplot(
  Pi ~ X*H, 
  xlab = "X", ylab = "H",
  main = "Stationnary distribution",
  col.regions = cm.colors(20)  #cm terrain topo heat
)



#-------------Courbe1-----------------
data3 = read.table(modelname3)
attach(data3);
x =V1
pi1 =V2



barplot(pi1,names.arg = x,xlab = "x : Number of SDUs in PDU",ylab = "PrX(x)",col = "blue", main = "Distribution of the PDU size at release time",border = "black")
abline(v=7.4, col="Red",lwd="4",lty=1)
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

barplot(pi2,names.arg = h,xlab = "t",ylab = "PrH(t)",col = "blue", main = "Distribution of the Timer at release time", border = "black")
abline(v=6.2, col="Red",lwd="4",lty=1)
legend("topleft", legend=c("probability","Timer deadline"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(h,pi2,type="h",xlab="H",ylab="Marginale sortie de H")
#title("Courbe de la marginale conditionnel sur l'horloge") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)




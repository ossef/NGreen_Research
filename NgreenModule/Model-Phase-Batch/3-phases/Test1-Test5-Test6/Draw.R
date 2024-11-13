
variables = commandArgs(trailingOnly=TRUE)
MODEL = variables[1] #as.numeric(variables[1])

MODEL = paste0(MODEL,"-reordre");

modelname1 = paste0(MODEL, ".MargCd.X.pi")
modelname2 = paste0(MODEL, ".MargCd.H.pi")
modelname3 = paste0(MODEL, ".Conv.H.G.pi")

#-------------Courbe1-----------------
data1 = read.table(modelname1)
attach(data1);
x =V1
pi1 =V2

x = expression( 0 ,  ,   ,   ,  ,   ,  ,  ,   ,   ,    ,  ,  ,   ,   ,   ,  , ,
    ,    ,   20   ,  ,  ,   ,   ,      ,  ,  ,   ,   ,     ,  ,  ,   ,   ,    , 
    ,    ,    ,    , 40  ,  ,  ,   ,   ,      ,   ,  ,  ,   ,    ,    ,   ,   , 
    ,    ,  ,  ,   ,   ,   60    ,  ,  ,   ,   ,         , ,  ,   ,   ,      ,   , 
    ,    ,    ,      ,  ,  ,   ,   ,    80    ,  ,  ,   ,   ,     ,   ,   ,    ,  , 
    ,  ,  ,   ,   ,       ,  ,  ,   ,   ,   100 ,   ,  ,  ,   ,       ,  ,  ,
   ,  ,     ,  ,  ,   ,   ,     ,   ,  ,  ,   ,    120   ,  ,  ,   ,   ,   
    ,  ,  ,   ,   ,       ,  ,  ,   ,   ,       ,  ,  ,   ,   ,    140 ,   ,   ,   ,  
   ,    ,  ,  ,   ,   ,      ,  ,  ,   ,   ,       ,  ,  ,   ,   ,   160 ,  ,
   ,   ,   ,      ,  ,  ,   ,   ,     ,  ,  ,   ,   ,      ,  ,  ,   ,   ,  
  180  ,  ,  ,   ,   ,     ,  ,  ,   ,   ,      ,  ,  ,   ,   ,    ,   ,  ,
   ,   ,  200   ,  ,  ,   ,   ,     ,  ,  ,   ,   ,      ,  ,  ,   ,   ,     ,  ,  ,   ,   ,   220) 

barplot(pi1,names.arg =x ,  cex.axis =1,xlab = "x : Number of chunks in PDU",ylab = "PrX(x)",col = "blue",border = "black")
abline(v=228.7, col="Red",lwd="2",lty=1)
legend("topleft", legend=c("probability","Threshold"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(x,pi1,type="h",xlab="X",ylab="Marginale sortie de X")
#title("Courbe de la marginale conditionnel sur les paquets qui sortent") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)

#--------------Courbe2-----------------

data2 = read.table(modelname2)
attach(data2);
h =V1
pi2 =V2

h = expression( 0 , , , , , 5 , , , , , 10 , , , , ,  15, , , , ,  20 , , , , ,  25 , , , , ,  30 , , , , ,  35  , , , , , 40  , , , , ,  45 , , , , ,  50 , , , , ,  55 )

barplot(pi2,names.arg = h, ylim=c(0,0.075) ,xlab = "t",ylab = "PrH(t)",col = "blue", border = "black")
abline(v=48, col="Red",lwd="3",lty=1)
legend("topleft", legend=c("probability","timer deadline"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(h,pi2,type="h",xlab="H",ylab="Marginale sortie de H")
#title("Courbe de la marginale conditionnel sur l'horloge") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)

data3 = read.table(modelname3)
attach(data3);
h =V1
piConv =V2

h = expression( 0 , , , , , 5 , , , , , 10 , , , , ,  15, , , , ,  20 , , , , ,  25 , , , , ,  30 , , , , ,  35  , , , , , 40  , , , , ,  45 , , , , ,  50 , , , , ,  55 )

barplot(piConv,names.arg = h, ylim=c(0,0.075), xlab = "t",ylab = "PrH_G(t)",col = "blue", border = "black")
legend("topleft", legend=c("probability"),
       col=c("blue"), lty=1:1, cex=1.3)

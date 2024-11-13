modelname3 = "test-ngreen-mod2-250.MargCd.X.pi"

data3 = read.table(modelname3)
attach(data3);

data3
datan = data3[order(-V1),]
attach(datan)


En =(0.00008/(V1*50*8))*10^9
En = round(En,2)
Proba = V2

barplot(Proba,names.arg = En,xlim=c(0,200),ylim=c(0,0.20),xlab = "Energy Consumption (nJoule/bit) ",ylab = "Probability",col = "blue",border = "black")
legend("topright", legend=c("probability","Threshold"),
       col=c("blue","red"), lty=1:1, cex=1.3)


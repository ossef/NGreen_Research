

modelname7 = "ResFinale.res"
data7 = read.table(modelname7)
attach(data7);

data7

barplot(as.vector(V2),names.arg=as.vector(V1),ylim=c(0,0.05),xlab = "End to End Delay",ylab = "Probability",col = "blue", border = "black")



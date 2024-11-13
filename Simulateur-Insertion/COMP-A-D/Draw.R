
#------------------------------
modelname1 = "dataA.txt"
data1 = read.table(modelname1)
attach(data1);

var1  = V1
freq1 = V2

#barplot(V2, names.arg=V1,xlab = "Delay",ylab = "Probability",col = "red" ,xlim=c(0,25),ylim=c(0,0.40), border = "black")
plot(V1,V2,type ="l",xlab = "Insertion Delay",ylab = "Probability",col = "black" ,xlim=c(0,35),ylim=c(0,0.45) )
legend(x="topright",legend=c("Scenario A","Scenario B"),text.col=c("black","red"),col=c("black","red"),lty=1:1, cex=1.2)

modelname2 = "dataD.txt"
data2 = read.table(modelname2)
attach(data2);

var2 = V1
freq2 = V2

lines(V1,V2,type ="l",col = "red" ,xlim=c(0,25),ylim=c(0,0.40) )
#plot(V1,V2,type ="h",xlab = "Delay",ylab = "Probability",col = "red" ,xlim=c(0,25),ylim=c(0,0.40) )
#barplot(V2, names.arg=V1, axes=FALSE, add = T,col=rgb(0, 1, 0, 0.5), border = "black") #col=rgb(0, 1, 0, 0.5)


#library("entropy")
KLD(var1,var2)

#tab = data.frame(data1) 
#tab

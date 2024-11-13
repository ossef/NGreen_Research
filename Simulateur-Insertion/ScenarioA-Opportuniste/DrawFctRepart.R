#Execution : R CMD BATCH "DrawFctRepart.R"

modelname1 = "FctRepart.data"


#-------------CourbeLines-----------------
data1 = read.table(modelname1)
attach(data1);

barplot(table(data1[,1]),xlab="Inter Arrivals (PDUs filling time)", ylab="Occurency", main="Inter Arrivals Occurency",col = "blue", border = "black")

#-------------CourbeLines-----------------



#plot(t,N1,type="S",col="red",xlab="Time", ylab="# Waiting PDUs")
#lines(t,N2,type="S",col="black")
#legend("top", legend=c("ESLB","ELB"),
#       col=c("blue","red"), lty=1:1, cex=1.3)









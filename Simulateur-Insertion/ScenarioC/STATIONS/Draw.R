#Execution : R CMD BATCH  Draw.R




#-------------CourbeLines of Waiting PDUs -----------------
modelname1 = "MeanFilling.data"
data1 = read.table(modelname1)
attach(data1);



plot(V1,V2,type="o",las=1,lab=c(10, 6, 1), pch=3,col="black",xlab="Number of stations", ylab="Number of used slots", main="Occupency of the ring with 150 slots")
#barplot(as.vector(tab[2:length(tab[,1]),2]), names.arg=as.vector(tab[2:length(tab[,1]),1]),xlab = "Delay",ylab = "Occurency",col = "blue", main = paste("Occurency of time Delay, station",(i+1)/2), border = "black")












#Execution : R CMD BATCH  Draw.R


modelname1 = "Deter-60-28-4.InsertionTime"
data1 = read.table(modelname1)
attach(data1);

datan = data1[order(V1),]
datan
attach(datan)


barplot(V2, names.arg=V1,xlab = "Insertion Delay",xlim=c(0,120),ylim = c(0,0.08),ylab = "Probability",col = "blue", border = "black")

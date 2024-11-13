#Execution : R CMD BATCH "Draw.R"

library(gplots)

modelname1 = "DETER.times"
modelname2 = "OPPORT.times"

data1 = read.table(modelname1)
attach(data1);

X = V1
Y = V2



data2 = read.table(modelname2)
attach(data2);


moyenne1 = mean(V1)
moyenne2 = mean(V2)
moyenne3 = mean(V3)
moyenne4 = mean(V4)
moyenne5 = mean(V5)
moyenne6 = mean(V6)
moyenne7 = mean(V7)
#moyenne8 = mean(V8)

moyennes = c(moyenne1, moyenne2, moyenne3,moyenne4,moyenne5,moyenne6,moyenne7)#,moyenne8)

plot(X,moyennes,ylim=c(1,50),
xlab="Number of Stations", ylab="Insertion Delay",
type="l", 
font.lab=2,
pch=8,
lty=1, 
lwd=2,
col="red" )
legend(x="topleft",legend=c("Deterministic","Opportunistic"),text.col=c("black","red"),pch=c(15,8),col=c("black","red"))


borneSup = c(1.706674 , 2.299755 , 3.223659 , 4.757640 , 8.414499 , 28.704061 ,  40.640740) #,105.577676) 
borneInf = c(1.675993 , 2.261578 , 3.163674 , 4.677693 , 8.248168 , 26.982606 ,  36.440594 ) #, 85.746324) 
moyennes


plotCI(X, moyennes, li=borneInf, ui=borneSup,  barcol="blue", gap=0, add=TRUE, type="p", pch=8, lwd=1.3, cex = 0.9,col ="red")

lines(X, Y, 
type="o", 
font.lab=2,
pch=15,
lty=1, 
lwd=2,
col="black" )

panel.first = grid()







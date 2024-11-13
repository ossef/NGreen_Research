#Execution : R CMD BATCH "Draw.R"



modelname1 = "Matrice1.time"
modelname2 = "Matrice2.time"
modelname3 = "Matrice3.time"


data1 = read.table(modelname1)
attach(data1);


t.test(V1)$conf.int
t.test(V2)$conf.int
t.test(V3)$conf.int
t.test(V4)$conf.int


data2 = read.table(modelname2)
attach(data2);


t.test(V1)$conf.int
t.test(V2)$conf.int
t.test(V3)$conf.int
t.test(V4)$conf.int



data3 = read.table(modelname3)
attach(data3);


t.test(V1)$conf.int
t.test(V2)$conf.int
t.test(V3)$conf.int
t.test(V4)$conf.int


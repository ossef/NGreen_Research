#Execution : R CMD BATCH "Draw.R"



modelname1 = "KMS_OPT_POW.time"
modelname2 = "KMS_MAJ.time"



data1 = read.table(modelname1)
attach(data1);


t.test(V1)$conf.int



data2 = read.table(modelname2)
attach(data2);


t.test(V1)$conf.int



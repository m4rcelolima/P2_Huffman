setwd(dir = "C:/Users/Thiago/Desktop/UFAL/comparacao")
data <- read.table("resultado.txt")

col2 <- data[,2]
col3 <- data[,3]

x <- 1:length(col2)

plot(x,col2,, main="Lista x ABB", xlab="Testes", ylab="Numero de Comparacoes", type='l', ylim=c(min(col2,col3),max(col2,col3)))
points(col3, type='l', col='red', lty=2)
par(mfrow=c(1,2))

SEIRt=read.csv("C:/Users/popcorn/Desktop/0/UniTo/Tesi/Pugliese/Modelli Probabilistici/Sellke/OutputFile/sellke.csv",header = FALSE)
S=SEIRt$V1
E=SEIRt$V2
I=SEIRt$V3
R=SEIRt$V4
time=SEIRt$V5
plot(time,S,col="red", type="l", ylim = c(0,S[1]+1))
lines(time,E,col="black", type="l")
lines(time,I,col="green", type="l")
lines(time,R,col="purple", type="l")
legend("topright" ,legend = c("Susceptible", "Exposed","Infected","Recovered"), col=c("red","black","green","purple"),lty = 1)








SEIRt=read.csv("C:/Users/popcorn/Desktop/0/UniTo/Tesi/Pugliese/Modelli Probabilistici/Gillespie_algorithm/OutputFIle/gillespie.csv",header = FALSE)
S=SEIRt$V1
E=SEIRt$V2
I=SEIRt$V3
R=SEIRt$V4
time=SEIRt$V5
plot(time,S,col="red", type="l", ylim = c(0,S[1]+1))
lines(time,E,col="black", type="l")
lines(time,I,col="green", type="l")
lines(time,R,col="purple", type="l")
legend("topright" ,legend = c("Susceptible", "Exposed","Infected","Recovered"), col=c("red","black","green","purple"),lty = 1)





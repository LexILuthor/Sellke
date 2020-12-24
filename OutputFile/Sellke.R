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

























#testing

N= 1000
beta= 0.3

gamma= 0.2
#R0=beta/gamma

Q=sort(rexp(N))


I=rexp(N,gamma)


I=I*(beta/N)


sumI=0
u=0
for (i in 1:(N-1)){
  sumI=sumI+I[i]
  if(Q[i+1]>sumI){
    z=i
    break
  }
  u=5
  z=i
}
z

u

























main : CSendMail.o
	g++ main.cpp CSendMail.o -o main -lcurl -I./include


CSendMail.o:
	g++ -c CSendMail.cpp 

clean:
	rm main CSendMail.o

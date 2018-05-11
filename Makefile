all:	server client
	@echo done
server:	server.cpp gfx.o data.o PaqueteDatagrama.o SocketDatagrama.o
	g++ -o server server.cpp gfx.o data.o PaqueteDatagrama.o SocketDatagrama.o -Wall -lX11 -lpthread
client:	client.cpp data.o PaqueteDatagrama.o SocketDatagrama.o
	g++ -o client client.cpp data.o PaqueteDatagrama.o SocketDatagrama.o -Wall
gfx.o:	gfx.h gfx.c
	gcc -c gfx.c -lX11
PaqueteDatagrama.o:	PaqueteDatagrama.h PaqueteDatagrama.cpp
	g++ -c PaqueteDatagrama.cpp 
SocketDatagrama.o:	SocketDatagrama.h SocketDatagrama.cpp
	g++ -c SocketDatagrama.cpp
data.o:	data.h data.cpp
	g++ -c data.cpp
clean:	
	rm *~ *.o server client

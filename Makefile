all:	server
	@echo done
server:	server.cpp gfx.o
	g++ -o server server.cpp gfx.o -Wall -lX11 -lpthread
gfx.o:	gfx.h gfx.c
	gcc -c gfx.c -lX11
clean:	
	rm *~ *.o server client

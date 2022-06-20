all: socket container

socket: socket.o server.o client.o
	g++ -g -o sockets.exe socket.o server.o client.o

container: container.o
	g++ -g -o container.exe container.o

container.o: Container.cpp Container.h
	g++ -g -c Container.cpp

socket.o: socket.cpp server.cpp client.cpp server.h client.h
	g++ -g -c socket.cpp server.cpp client.cpp

server.o: server.cpp server.h
	g++ -g -c server.cpp

client.o: client.cpp client.h
	g++ -g -c client.cpp

tar:
	tar -cvf ex5.tar Container.cpp Container.h socket.cpp server.cpp client.cpp server.h client.h Makefile README
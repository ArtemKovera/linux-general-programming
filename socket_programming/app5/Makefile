
CC = gcc

server: server_app5.o server_routines.o robust_io.o 
	$(CC) server_app5.o server_routines.o robust_io.o -o $@

client: client_app5.o open_client_fd.o robust_io.o 
	$(CC) client_app5.o open_client_fd.o robust_io.o -o $@

server_app5.o: ./source/server_app5.c 
	$(CC) ./source/server_app5.c -c

client_app5.o: ./source/client_app5.c 
	$(CC) ./source/client_app5.c -c

server_routines.o: ./source/server_routines.c ./source/server_routines.h
	$(CC) ./source/server_routines.c -c

open_client_fd.o: ./source/open_client_fd.c ./source/open_client_fd.h
	$(CC) ./source/open_client_fd.c -c

robust_io.o: ./source/robust_io.c ./source/robust_io.h
	$(CC) ./source/robust_io.c -c

clean:
	rm *.o server client
client: client.c
	gcc -Wall client.c -o client -pthread

server: server.c
	gcc -Wall	 server.c -o server

chess: chess.c
	gcc chess.c -o chess

clean:
	rm server client

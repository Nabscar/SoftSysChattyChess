client: client.c chessFunc.o chess.h server.h
	gcc client.c chessFunc.o -o client -pthread

server: server.c chessFunc.o chess.h server.h
	gcc server.c chessFunc.o -o server

chess: chess.c chessFunc.o chess.h
	gcc chess.c chessFunc.o -o chess

chessFunc.o: chessFunc.c chess.h
	gcc -c chessFunc.c

clean:
	rm server client chess

all: FinalExec

FinalExec: gameDriver.o GameBoard.o CEO.o Developer.o Manager.o Piece.o President.o Supervisor.o TeamLeader.o
	g++ gameDriver.o GameBoard.o CEO.o Developer.o Manager.o Piece.o President.o Supervisor.o TeamLeader.o -o FinalExec

gameDriver.o: gameDriver.cpp
	g++ -c gameDriver.cpp

GameBoard.o: GameBoard.cpp GameBoard.h
	g++ -c GameBoard.cpp

CEO.o: CEO.cpp CEO.h
	g++ -c CEO.cpp

Developer.o: Developer.cpp Developer.h
	g++ -c Developer.cpp

Manager.o: Manager.cpp Manager.h
	g++ -c Manager.cpp

Piece.o: Piece.cpp Piece.h
	g++ -c Piece.cpp

President.o: President.cpp President.h
	g++ -c President.cpp

Supervisor.o: Supervisor.cpp Supervisor.h
	g++ -c Supervisor.cpp

TeamLeader.o: TeamLeader.cpp TeamLeader.h
	g++ -c TeamLeader.cpp

clean:
	rm -rf *.o FinalExec
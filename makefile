all : game
	g++ checkers.cc game.cc space.cc main.cc

game : checkers.o game.o space.o main.o
	g++ checkers.cc game.cc space.cc main.cc -o game

main.o : main.cc colors.h checkers.h
	g++ -c main.cc

checkers.o : checkers.cc checkers.h game.h
	g++ -c checkers.cc

game.o : game.cc game.h
	g++ -c game.cc

space.o : space.cc colors.h space.h
	g++ -c space.cc

clean :
	rm -rf game *.o a.out

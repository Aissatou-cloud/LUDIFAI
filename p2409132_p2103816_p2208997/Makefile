all: bin/mainTest1

bin/mainTest1: obj/mainTest1.o obj/Joueur.o obj/Pion.o
	g++  obj/mainTest1.o obj/Joueur.o obj/Pion.o -o bin/mainTest1.o
	
obj/mainTest1.o: src/mainTest1.cpp src/Joueur.h
	g++ -ggdb -Wall -c src/mainTest1.cpp -o obj/mainTest1.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h
	g++ -ggdb -Wall -c src/Joueur.cpp -o obj/Joueur.o

obj/De.o: src/De.h src/De.cpp
	g++ -ggdb -Wall -c src/De.cpp -o obj/De.o

obj/Pion.o: src/Pion.h src/Pion.cpp
	g++ -ggdb -Wall -c src/Pion.cpp -o obj/Pion.o

obj/Color.o: src/Color.h src/Color.cpp
	g++ -ggdbgdb -Wall -c src/Color.cpp -o obj/Color.o

clean:
	rm -f obj/*.o bin/mainTest1


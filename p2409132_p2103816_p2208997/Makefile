all: bin/mainTest1

bin/mainTest1: obj/mainTest1.o obj/Joueur.o obj/Pion.o obj/De.o obj/Color.o 
	g++ -ggdb -Wall obj/mainTest1.o obj/Joueur.o obj/Pion.o obj/De.o obj/Color.o -o bin/mainTest1
	
obj/mainTest1.o: src/mainTest1.cpp src/Joueur.h src/Pion.h src/De.h src/Color.h
	g++ -ggdb -Wall -c src/mainTest1.cpp -o obj/mainTest1.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h src/Pion.h src/Color.h
	g++ -ggdb -Wall -c src/Joueur.cpp -o obj/Joueur.o

obj/De.o: src/De.cpp src/De.h
	g++ -ggdb -Wall -c src/De.cpp -o obj/De.o

obj/Pion.o: src/Pion.cpp src/Pion.h
	g++ -ggdb -Wall -c src/Pion.cpp -o obj/Pion.o

obj/Color.o: src/Color.cpp src/Color.h
	g++ -ggdb -Wall -c src/Color.cpp -o obj/Color.o

clean:
	rm -f obj/*.o bin/mainTest1


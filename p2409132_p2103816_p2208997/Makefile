all: joueur.out

joueur.out: obj/main.o obj/Joueur.o
	g++ -g obj/main.o obj/Joueur.o -o joueur.out
	
obj/main.o: src/main.cpp src/Joueur.h
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h
	g++ -g -Wall -c src/Joueur.cpp -o obj/Joueur.o

clean:
	rm -f obj/*.o joueur.out


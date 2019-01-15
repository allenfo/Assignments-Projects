run.o: main.o vampire.o barbarian.o blueMen.o medusa.o harry_potter.o character.o gameplay.o queue.o fight.o
	g++ main.o vampire.o barbarian.o blueMen.o medusa.o harry_potter.o character.o gameplay.o queue.o fight.o -o run
main.o: main.cpp
	g++ -c main.cpp
vampire.o: vampire.hpp vampire.cpp
	g++ -c vampire.cpp
barbarian.o: barbarian.hpp barbarian.cpp
	g++ -c barbarian.cpp
blueMen.o: blueMen.hpp blueMen.cpp
	g++ -c blueMen.cpp
medusa.o: medusa.hpp medusa.cpp
	g++ -c medusa.cpp
harry_potter.o: harry_potter.hpp harry_potter.cpp
	g++ -c harry_potter.cpp
character.o: character.hpp character.cpp
	g++ -c character.cpp
gameplay.o: gameplay.hpp gameplay.cpp
	g++ -c gameplay.cpp
queue.o: queue.hpp queue.cpp
	g++ -c queue.cpp
fight.o: fight.hpp fight.cpp
	g++ -c fight.cpp
clean:
	rm *.o run

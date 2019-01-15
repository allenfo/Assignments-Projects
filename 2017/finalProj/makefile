run.o: main.o attackup.o boss.o character.o elevator.o healthpo.o item.o l1monster.o l2monster.o map.o monster.o play.o space.o
	g++ main.o attackup.o boss.o character.o elevator.o healthpo.o item.o l1monster.o l2monster.o map.o monster.o play.o space.o -o run 
main.o: main.cpp
	g++ -c main.cpp
attackup.o: attackup.hpp attackup.cpp
	g++ -c attackup.cpp
boss.o: boss.hpp boss.cpp
	g++ -c boss.cpp
character.o: character.hpp character.cpp
	g++ -c character.cpp
elevator.o: elevator.hpp elevator.cpp
	g++ -c elevator.cpp
healthpo.o: healthpo.hpp healthpo.cpp
	g++ -c healthpo.cpp
item.o: item.hpp item.cpp
	g++ -c item.cpp
l1monster.o: l1monster.hpp l1monster.cpp
	g++ -c l1monster.cpp 
l2monster.o: l2monster.hpp l2monster.cpp
	g++ -c l2monster.cpp
map.o: map.hpp map.cpp
	g++ -c map.cpp
monster.o: monster.hpp monster.cpp
	g++ -c monster.cpp
play.o: play.hpp play.hpp
	g++ -c play.cpp
space.o: space.hpp space.cpp
	g++ -c space.cpp
clean:
	rm *.o run

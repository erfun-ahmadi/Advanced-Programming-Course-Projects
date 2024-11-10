CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

starwars.out: main.o rsdl.o file_info.o ship.o shot.o power_up.o game.o
	$(CC) main.o rsdl.o file_info.o ship.o shot.o power_up.o game.o $(CCFLAGS) -o starwars.out

main.o: main.cpp file_info.h rsdl.hpp
	$(CC) -c main.cpp 

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp

file_info.o: file_info.cpp file_info.h
	$(CC) -c file_info.cpp

ship.o: ship.cpp ship.h rsdl.hpp const_values.h 
	$(CC) -c ship.cpp

shot.o: shot.cpp shot.h	rsdl.hpp const_values.h
	$(CC) -c shot.cpp

power_up.o: power_up.cpp power_up.h rsdl.hpp const_values.h
	$(CC) -c power_up.cpp

game.o: game.cpp game.h rsdl.hpp const_values.h ship.h shot.h power_up.h
	$(CC) -c game.cpp

clean:
	rm *.o *.out 
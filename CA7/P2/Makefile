CC := g++ -std=c++11

utaxi.out: main.o get_commands.o utaxi.o users.o passengers.o drivers.o errors.o trips.o locations.o
	$(CC) main.o get_commands.o utaxi.o users.o passengers.o drivers.o errors.o trips.o locations.o -o utaxi.out

main.o: main.cpp get_commands.h utaxi.h locations.h drivers.h passengers.h users.h trips.h const_values.h errors.h
	$(CC) -c main.cpp

get_commands.o: get_commands.cpp get_commands.h utaxi.h locations.h drivers.h passengers.h users.h trips.h const_values.h errors.h
	$(CC) -c get_commands.cpp

utaxi.o: utaxi.cpp utaxi.h locations.h drivers.h passengers.h users.h trips.h const_values.h errors.h
	$(CC) -c utaxi.cpp

users.o: users.cpp users.h locations.h trips.h errors.h const_values.h
	$(CC) -c users.cpp

passengers.o: passengers.cpp passengers.h users.h locations.h trips.h errors.h const_values.h
	$(CC) -c passengers.cpp

drivers.o: drivers.cpp drivers.h users.h locations.h trips.h errors.h const_values.h
	$(CC) -c drivers.cpp

errors.o: errors.cpp errors.h
	$(CC) -c errors.cpp

trips.o: trips.cpp trips.h const_values.h
	$(CC) -c trips.cpp

locations.o: locations.cpp locations.h
	$(CC) -c locations.cpp

clean:
	rm *.o *.out 	
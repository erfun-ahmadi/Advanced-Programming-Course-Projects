CC := g++ -std=c++11

utaxi.out: main.o handlers.o template_parser.o response.o request.o utilities.o server.o route.o utaxi.o users.o passengers.o drivers.o errors.o trips.o locations.o
	$(CC) *.o -o utaxi.out

main.o: main.cpp handlers.hpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp 7.2/utaxi.h 7.2/locations.h 7.2/drivers.h 7.2/passengers.h 7.2/users.h 7.2/trips.h 7.2/const_values.h 7.2/errors.h
	$(CC) -c main.cpp

utaxi.o: 7.2/utaxi.cpp 7.2/utaxi.h 7.2/locations.h 7.2/drivers.h 7.2/passengers.h 7.2/users.h 7.2/trips.h 7.2/const_values.h 7.2/errors.h
	$(CC) -c 7.2/utaxi.cpp

users.o: 7.2/users.cpp 7.2/users.h 7.2/locations.h 7.2/trips.h 7.2/errors.h 7.2/const_values.h
	$(CC) -c 7.2/users.cpp

passengers.o: 7.2/passengers.cpp 7.2/passengers.h 7.2/users.h 7.2/locations.h 7.2/trips.h 7.2/errors.h 7.2/const_values.h
	$(CC) -c 7.2/passengers.cpp

drivers.o: 7.2/drivers.cpp 7.2/drivers.h 7.2/users.h 7.2/locations.h 7.2/trips.h 7.2/errors.h 7.2/const_values.h
	$(CC) -c 7.2/drivers.cpp

errors.o: 7.2/errors.cpp 7.2/errors.h
	$(CC) -c 7.2/errors.cpp

trips.o: 7.2/trips.cpp 7.2/trips.h 7.2/const_values.h
	$(CC) -c 7.2/trips.cpp

locations.o: 7.2/locations.cpp 7.2/locations.h
	$(CC) -c 7.2/locations.cpp

handlers.o: handlers.cpp handlers.hpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp 7.2/utaxi.h 7.2/locations.h 7.2/drivers.h 7.2/passengers.h 7.2/users.h 7.2/trips.h 7.2/const_values.h 7.2/errors.h
	$(CC) -c handlers.cpp

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.hpp utils/request.hpp utils/utilities.hpp 
	$(CC) -c utils/template_parser.cpp 

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp 

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp
	$(CC) -c server/server.cpp 

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp

clean:
	rm *.o *.out
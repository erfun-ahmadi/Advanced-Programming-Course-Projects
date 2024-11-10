CC := g++ -std=c++11

library.out: main.o Library.o person.o professor.o student.o document.o book.o magazine.o reference.o
	$(CC) main.o Library.o person.o professor.o student.o document.o book.o magazine.o reference.o -o library.out

main.o: main.cpp Library.hpp person.hpp professor.hpp student.hpp document.hpp book.hpp magazine.hpp reference.hpp const_values.hpp
	$(CC) -c main.cpp	

Library.o: Library.cpp Library.hpp person.hpp professor.hpp student.hpp document.hpp book.hpp magazine.hpp reference.hpp const_values.hpp
	$(CC) -c Library.cpp

person.o: person.cpp person.hpp document.hpp const_values.hpp
	$(CC) -c person.cpp

professor.o: professor.cpp professor.hpp person.hpp document.hpp const_values.hpp
	$(CC) -c professor.cpp

student.o: student.cpp student.hpp person.hpp document.hpp const_values.hpp
	$(CC) -c student.cpp

document.o: document.cpp document.hpp const_values.hpp
	$(CC) -c document.cpp

book.o: book.cpp book.hpp document.hpp const_values.hpp
	$(CC) -c book.cpp

magazine.o: magazine.cpp magazine.hpp document.hpp const_values.hpp
	$(CC) -c magazine.cpp

reference.o: reference.cpp reference.hpp document.hpp const_values.hpp
	$(CC) -c reference.cpp
	
clean:
	rm *.o *.out 	


# executable target
project: database.o user_interface.o user_interface_utility.o
	gcc -o project database.o user_interface.o user_interface_utility.o

# object targets
database.o: database.c record.h
	gcc -ansi -pedantic-errors -Wall -c database.c

user_interface.o: user_interface.c record.h
	gcc -ansi -pedantic-errors -Wall -c user_interface.c

user_interface_utility.o: user_interface_utility.c user_interface.h
	gcc -ansi -pedantic-errors -Wall -c user_interface_utility.c

# utility target
clean:
	rm project database.o user_interface.o user_interface_utility.o


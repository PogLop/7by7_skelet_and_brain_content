all: test_fud.o nehetest.o

test_fud.o: fudis.c test_fud.c
	gcc -Wall -Werror -o test_fud.o test_fud.c

nehetest.o: nehet.c n_test.c
	gcc -Wall -Werror -o nehetest.o n_test.c

clean:
	rm -f *.o
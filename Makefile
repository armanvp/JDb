all:
	g++ jdb.cpp -c
	ar -cvq libjdb.a jdb.o

clean:
	rm *.o *.a

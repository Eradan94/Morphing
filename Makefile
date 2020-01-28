CFLAGS=-Wall -O2 -ansi -g
LDFLAGS=-lm -lMLV
OBJ=bin/Main.o bin/Point.o bin/Triangle.o bin/Graph.o bin/Matrice.o bin/Frame.o bin/Triangulation.o

Morphing: $(OBJ)
	gcc -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)

bin/Main.o: src/Main.c include/Point.h include/Triangle.h include/Graph.h include/Matrice.h include/Frame.h include/Triangulation.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)

bin/Point.o: src/Point.c include/Point.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)

bin/Triangle.o: src/Triangle.c include/Triangle.h include/Point.h include/Matrice.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)

bin/Graph.o: src/Graph.c include/Graph.h include/Triangle.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)

bin/Matrice.o: src/Matrice.c include/Matrice.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)
	
bin/Triangulation.o: src/Triangulation.c  include/Triangulation.h include/Triangle.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)
	
bin/Frame.o: src/Frame.c include/Frame.h include/Triangle.h include/Point.h
	gcc -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f bin/*.o
	rm -f Morphing

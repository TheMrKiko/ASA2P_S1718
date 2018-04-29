testpath=./Testes
all: comp run

comp: main.cpp
	g++ -std=c++11 -O3 -Wall -o proj main.cpp -lm

run: proj
	./proj

clean:
	rm proj
	
test: comp
	read t; \
	./proj < ${testpath}/$$t.in

graph: comp
	valgrind --tool=massif ./proj < ${testpath}/st01.in

leak: comp
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./proj < ${testpath}/st01.in
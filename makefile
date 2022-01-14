XXFLAGS += -std=c++17

OBJS = main.o dpll_solver.o clause.o

test: $(OBJS)
	g++ -std=gnu++17 -g -O2 -o main $(OBJS)  
	rm -rf $(OBJS)

clause.o: clause.cpp ./include/clause.h
	g++ -g -c clause.cpp -o clause.o

dpll_solver.o: dpll_solver.cpp ./include/dpll_solver.h
	g++ -g -c dpll_solver.cpp -o dpll_solver.o

main.o: main.cpp
	g++ -g -c main.cpp -o main.o

clean:
	rm -rf $(OBJS) main
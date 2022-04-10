.PHONY: test clean

XXFLAGS += -std=c++17

OBJS = main.o dpll_solver.o clause.o

test: $(OBJS)
	g++ $(XXFLAGS) -g -o main $(OBJS)  

clause.o: clause.cpp ./include/clause.h
	g++ $(XXFLAGS) -g -c clause.cpp -o clause.o

dpll_solver.o: dpll_solver.cpp ./include/dpll_solver.h
	g++ $(XXFLAGS) -g -c dpll_solver.cpp -o dpll_solver.o

main.o: main.cpp
	g++ $(XXFLAGS) -g -c main.cpp -o main.o

clean:
	rm -rf $(OBJS) main
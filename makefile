XXFLAGS += -std=c++17

OBJS = main.o dpll_solver.o clause.o

test: $(OBJS)
			g++ -std=gnu++17 -g -O2 -o main $(OBJS)  
			rm -rf $(OBJS)

clause.o: clause.cpp ./include/clause.h

dpll_solver.o: dpll_solver.cpp ./include/dpll_solver.h

main.o: main.cpp

clean:
	rm -rf $(OBJS) main
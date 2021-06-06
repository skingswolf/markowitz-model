CXX=g++
CXXFLAGS = -Wall -g -Wc++11-extensions


csv.o: csv.h

read_data.o: read_data.h

utils.o: utils.h

matrix.o: matrix.h

markowitz_model.o: matrix.h markowitz_model.h portfolio_optimisation_model.h utils.h matrix.h

main.o: markowitz_model.h read_data.h
	g++ -c main.cpp

main: main.o markowitz_model.o matrix.o utils.o read_data.o csv.o
	$(CXX) -o main main.o markowitz_model.o matrix.o utils.o read_data.o csv.o $(CXXFLAGS)

.PHONY: clean
clean:
	rm -r *.o read_data utils matrix main markowitz_model
CXX=g++
CXXFLAGS = -Wall -g -w


csv.o: csv.h

read_data.o: read_data.h

utils.o: utils.h

matrix.o: matrix.h

markowitz_model.o: markowitz_model.h portfolio_optimisation_model.h utils.h matrix.h

markowitz_model_backtester.o: backtester.h

main.o: markowitz_model.h read_data.h
	g++ -c main.cpp

main: main.o markowitz_model_backtester.o markowitz_model.o matrix.o utils.o read_data.o csv.o
	$(CXX) -o main main.o markowitz_model_backtester.o markowitz_model.o matrix.o utils.o read_data.o csv.o $(CXXFLAGS)


.PHONY: clean
clean:
	rm -r *.o main
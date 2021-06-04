CXX=g++
CXXFLAGS = -Wall -g


csv.o: csv.h

read_data.o: read_data.h csv.h

read_data: csv.o read_data.o
	$(CXX) -o read_data csv.o read_data.o $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf *.o 
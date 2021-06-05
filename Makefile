CXX=g++
CXXFLAGS = -Wall -g


csv.o: csv.h

read_data.o: read_data.h csv.h

utils.o: read_data.h utils.h

read_data: csv.o read_data.o
	$(CXX) -o read_data read_data.o csv.o $(CXXFLAGS)

utils: utils.o read_data.o csv.o
	$(CXX) -o utils utils.o read_data.o csv.o $(CXXFLAGS)


.PHONY: clean
clean:
	rm -r *.o read_data utils
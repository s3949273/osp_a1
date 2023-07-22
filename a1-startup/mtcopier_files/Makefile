.SILENT:
CXX = g++
CFLAGS = -std=c++20 -Wall -lpthread

mtcopier: main.o reader.o writer.o
	$(CXX) $(CFLAGS) -o mtcopier main.o reader.o writer.o 

%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -c $^

clean: 
	rm -rf mtcopier *.o  
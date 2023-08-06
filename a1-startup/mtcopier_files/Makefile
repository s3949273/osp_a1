
CXX = g++
CFLAGS = -std=c++20 -Wall -Werror -pthread

mtcopier: reader.o writer.o main.o
	$(CXX) $(CFLAGS) -o mtcopier main.o reader.o writer.o 

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^

clean: 
	rm -rf mtcopier *.o  
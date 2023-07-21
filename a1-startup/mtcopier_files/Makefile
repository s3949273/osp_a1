CXX = g++
CFLAGS = -std=c++20 -Wall 

mtcopier: main.o reader.o writer.o
	$(CC) $(CFLAGS) -o mtcopier main.o reader.o writer.o 

%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -c $^

clean: 
	rm -rf copier *.o  
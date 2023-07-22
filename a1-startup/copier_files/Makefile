.SILENT:
CXX = g++
#don't forget the -lpthread linker
CFLAGS = -std=c++20 -Wall -Werror

copier: main.o reader.o writer.o
	$(CXX) $(CFLAGS) -o copier main.o reader.o writer.o 

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^


clean: 
	rm -rf copier *.o  

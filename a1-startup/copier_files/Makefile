CXX = g++
CFLAGS = -std=c++20 -Wall  -lpthread

copier: main.o reader.o writer.o
	$(CC) $(CFLAGS) -o copier main.o reader.o writer.o 

clean: 
	rm -rf copier *.o  

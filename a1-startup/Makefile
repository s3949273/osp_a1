
##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs 
all: 
	$(MAKE) clean
	$(MAKE) copier
	$(MAKE) mtcopier


#go into the copier_files filepath and run the make command there
copier: 
	@echo making copier...
	g++ -Wall -Werror -std=c++20 -g ./copier_files/*.cpp -o copier
	@echo "done"
#go into the mtcopier_files filepath and run the make command there

mtcopier:
	@echo making multi-threaded copier...
	g++ -Wall -Werror -std=c++20 -lpthread -g ./mtcopier_files/*.cpp -o mtcopier
	@echo "done"
#clean by going into each directory and running make clean
clean: 
	@echo "cleaning up..."
	@rm -rf copier mtcopier *.dSYM
	
	@echo "done"


##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs 

#go into the copier_files filepath and run the make command there
copier: 
	@echo "making copier"
	@$(MAKE) -C copier_files
	@cd copier_files && mv copier ..
	@echo "finished making copier"
#go into the mtcopier_files filepath and run the make command there

mtcopier:
	@echo "making mtcopier"
	@$(MAKE) -C mtcopier_files
	@cd mtcopier_files && mv mtcopier ..
	@echo "finished making mtcopier"

#clean by going into each directory and running make clean
clean: 
	@echo "cleaning up..."
	@cd copier_files && $(MAKE) clean;
	@cd mtcopier_files && $(MAKE) clean;
	@echo "done"




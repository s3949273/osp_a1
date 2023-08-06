/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;

void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    delete readers;
    delete writers;
}

int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/
    if(argc!= 4){
        std::cout<<"Not enough command line arguments"<<std::endl;
    }else{
        /**
         * process command line arguments
         **/
        try{
            const unsigned int num_threads = std::stoi(argv[1]);
              /**
             * initiliaze the reader and writer classes
             **/
            
            std::vector<reader*> reads(num_threads, readers);
            std::vector<writer*> writes(num_threads, writers);
            readers->init(argv[2]);
            writers->init(argv[3]);
            /**
             * initialize the running of each thread. Note you just call run() on each
             * object here, you'll call pthread_create itself in the run function.
             **/
            for(size_t x = 0; x<num_threads; x++){
                reads[x]->run();
                // writes[x]->run();
            }
            writers->print();

            

        }catch(...){
            std::cout<<"The command line argument which was supposed to contain the number of threads did not contain any numbers"<<std::endl;
        }
    }

    
    


    /**
     *
     * have loop here waiting for the threads to bomplete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    return EXIT_SUCCESS;
}
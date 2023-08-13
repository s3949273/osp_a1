/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <unistd.h>
#include "writer.h"
#include <cstdlib>
/**
 * these need to be global variables as you'll need handle cleaning them up in
 *cleanup which will automatically be called on program exit
 **/
reader* readers;
writer* writers;
pthread_mutex_t shared_mutex;


void cleanup() {
    /**
     * perform any cleanup you need to do here for global pointers
     **/
    if(readers!=nullptr){
        delete[] readers;    
    }
    if (writers != nullptr){
        delete[] writers;
    }
    pthread_mutex_destroy(&shared_mutex);
}


int main(int argc, char** argv) {
    atexit(cleanup);
    /**
     * check command line arguments
     **/
    if(argc!= 4){
        std::cout<<"incorrect amount of command line arguments, expected 3, got: "<<argc-1<<std::endl;
    }
    else{
        try{
            /**
             * process command line arguments
             **/
            const unsigned int num_threads = std::stoi(argv[1]);
              /**
             * initiliaze the reader and writer classes
             **/
            readers = new reader[num_threads];
            writers = new writer[num_threads];
            readers->init(argv[2]);
            writers->init(argv[3]);
            
            pthread_mutex_init(&shared_mutex,NULL);
            readers->r_mutex = &shared_mutex;
            writers->w_mutex = &shared_mutex;
            
            /**
             * initialize the running of each thread. Note you just call run() on each
             * object here, you'll call pthread_create itself in the run function.
             **/
            std::clock_t start = std::clock();
            for(size_t x = 0; x<num_threads; x++){
                readers[x].run();
                writers[x].run();
            }
            
            /**
             *
             * have loop here waiting for the threads to bomplete. Please see
             * section on avoiding busy waiting on the assignment specification to see
             * what need to be done here
            **/
            readers->join();
            writers->join();
            
            std::cout<<"duration was: "<<( std::clock() - start ) / (double) CLOCKS_PER_SEC<<std::endl;
        }catch(...){
            std::cout<<"The command line argument which was supposed to contain the number of threads did not contain any numbers"<<std::endl;
        }
    }
    std::cout<<"end of program, have a nice day"<<std::endl;
    return EXIT_SUCCESS;
}
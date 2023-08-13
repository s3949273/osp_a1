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


    /**
     * initiliaze the reader and writer classes
     **/
    /**
     * initialize the running of each thread. Note you just call run() on each
     * object here, you'll call pthread_create itself in the run function.
     **/




    /**
     *
     * have loop here waiting for the threads to bomplete. Please see
     * section on avoiding busy waiting on the assignment specification to see
     * what need to be done here
      **/
    return EXIT_SUCCESS;
}
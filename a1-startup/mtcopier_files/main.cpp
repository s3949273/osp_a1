/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include <cstdlib>
#include <ctime>
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
     **/ if(argc != 4){
        //incorrect amount of command line arguments
        std::cout<<"Sorry did not get the expected command line arguments"<<std::endl; 
        std::cout<<"expected arguments are: number of threads to spawn, input filepath and output filepath separated by spaces"<<std::endl;
        std::cout<<"expected example: ./copier 10 input_file output_file"<<std::endl;
    }else{
        //correct amount of command line arguments
        //make sure to do some input validation

        std::cout<<"read/writing with "<<argv[1]<<" number of threads"<<std::endl;

        readers->init((std::string)argv[2]);
        std::cout<<"using: "<<argv[1]<<" threads"<<std::endl;
        readers->set_threads_to_spawn(std::atoi(argv[1]));
        std::clock_t start = std::clock();
        readers->run();
        double duration =( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"duration was: "<<duration<<std::endl;
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

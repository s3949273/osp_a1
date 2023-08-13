/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include "writer.h"
#include "pthread.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
using std::cout;
using std::endl;




/* global variables if needed go here */
int main(int argc, char** argv) {
    

    /* check command line arguments */
    if(argc != 3){
        //incorrect amount of command line arguments
        cout<<"Sorry did not get the expected command line arguments"<<endl; 
        cout<<"expected example: ./copier input_file output_file"<<endl;
    }else{
        //correct amount of command line arguments
        //initialise writer

        writer writer((std::string)argv[2]);
        //initialise reader
        reader reader((std::string)argv[1], writer);
        std::clock_t prog_start = std::clock();
        reader.run();
        double duration =( std::clock() - prog_start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"duration was: "<<duration<<endl;
    }
    /* load the file and copy it to the destination */
    
    return EXIT_SUCCESS;
}

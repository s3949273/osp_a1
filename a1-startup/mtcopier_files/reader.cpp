/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"

#include "writer.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;
pthread_t reader::thread;

void reader::init(const std::string& name) {
    in.open(name);
}

void reader::run(){
    if(pthread_create(&thread, NULL, runner, (void *)&in)!= 0){
        std::cout<<"Something went wrong initialising the thread"<<std::endl;
    }else{
        std::cout<<"created a thread"<<std::endl;
    }
}

void* reader::runner(void* arg) { 
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&lock);
    std::ifstream* i_file = (std::ifstream*)arg;
    std::string line = "";
    if(!i_file->eof()){
        getline(*i_file, line);
        writer::append(line);
        
    }else{
        writer::setfinished();
    }
    if(pthread_join(thread, NULL)!=0){
        std::cout<<"somethign went wrong joining the thread"<<std::endl;
    }
    pthread_mutex_unlock(&lock);
        return nullptr; 
    }
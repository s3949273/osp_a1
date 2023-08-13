/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"
#include <unistd.h>
#include "reader.h"

/**
 * implement these functions requred for the writer class
 **/
std::ofstream writer::out;
bool writer::finished =false;
std::deque<std::string> writer::queue;
pthread_t writer::w_thread;
pthread_mutex_t* writer::w_mutex;
pthread_cond_t writer::line_ready = PTHREAD_COND_INITIALIZER;
void writer::init(const std::string& name) {
    out.open(name);
} 


void writer::join(){
    int ret = pthread_join(w_thread, NULL);
    if(ret !=0 ){
        std::cout<<"Err: "<<strerror(ret)<<std::endl; 
    }else{
        std::cout<<"finished joining writer threads"<<std::endl;
    }
    if(out.is_open()){
        out.close();
        std::cout<<"closed the output file"<<std::endl;
    }
    pthread_cond_destroy(&line_ready);
}

void writer::run() {
    if(out.is_open()){  
        if(pthread_create(&w_thread, NULL, runner, NULL)!=0){
            std::cout<<"something went wrong creating the thread"<<std::endl;
        }
    }else{
        std::cout<<"output file was not open"<<std::endl;
    }
}


void* writer::runner(void* arg) {
    while(true){    
        if(queue.empty() && writer::finished){
            break;   
        }
        std::string line = "";
        if(pthread_mutex_lock(w_mutex)!=0){
            std::cout<<"could not obtain lock"<<std::endl;
        }
        
        while(queue.empty() && !writer::finished){
            pthread_cond_wait(&line_ready, w_mutex);    
        }
        if(queue.size() >0){
            out<<queue.front()<<std::endl;
            queue.pop_front();
        }
        int ret = pthread_mutex_unlock(w_mutex);
        if(ret!=0){
            std::cout<<"something went wrong unlocking writer lock"<<strerror(ret)<<std::endl;
        }
    }
    pthread_exit(NULL);
    return nullptr;
}


void writer::append(const std::string& line) {
    writer::queue.push_back(line);
}

void writer::setfinished() {
    finished = true;
}
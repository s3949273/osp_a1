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
unsigned reader::threads_to_spawn;
pthread_cond_t reader::cond;
pthread_mutex_t reader::lock;

void reader::init(const std::string& name) {
    in.open(name);
}
void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   std::cout << "Hello World! Thread ID, " << tid << std::endl;
   pthread_exit(NULL);
}


void reader::run() {
    pthread_t threads[threads_to_spawn-1];
    lock =  PTHREAD_MUTEX_INITIALIZER;
    while(!in.eof()){
        for(size_t i = 0; i< threads_to_spawn; i++){
            if(pthread_create(&threads[i], NULL, runner, (void * )&in)!=0){
                std::cout<<"something went wrong creating the thread:"<<i<<std::endl;
            }else{
                std::cout<<"created reader thread: "<<i<<std::endl;
            }
        }
        for(size_t i = 0; i<threads_to_spawn; i++){
            //join the threads, right now we do not expect anything to be returned
            if(pthread_join(threads[i], NULL) != 0){
                std::cout<<"Something went wrong joining thread:" <<threads[i]<<std::endl;
            }else{
                std::cout<<"joined reader thread: "<<i<<std::endl;
                writer::signal();
            }
        }
    }
    //destroy condition, and mutex
    // pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    std::cout<<"finished reading successfully"<<std::endl;
    in.close();
    writer::setfinished();
}

void* reader::runner(void* arg) {
    //cast void pointer to ifstream pointer
    std::string line = "";
    if(pthread_mutex_lock(&lock)!= 0){
        std::cout<<"something went wrong obtaining the reader lock"<<std::endl;
    }
    std::ifstream* input = (std::ifstream*) arg;
    
    if(!input->fail() && !input->eof()){
       //if there is a line to get, then get it
        getline(*input, line);
        std::cout<<line<<std::endl; 
        writer::append(line);
    }
    if(pthread_mutex_unlock(&lock) != 0){
        std::cout<<"something went wrong when unlocking the mutex lock!"<<std::endl;
    }
    return nullptr;
}

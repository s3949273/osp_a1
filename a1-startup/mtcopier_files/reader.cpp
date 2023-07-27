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
unsigned reader::threads_to_spawn = 0;
pthread_cond_t reader::cond;
pthread_mutex_t reader::lock;

void reader::init(const std::string& name) {
    in.open(name);
}
void reader::set_threads_to_spawn(int num_threads){
    reader::threads_to_spawn = num_threads;
}

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   std::cout << "Hello World! Thread ID, " << tid << std::endl;
   pthread_exit(NULL);
}


void reader::run() {
    pthread_t threads[threads_to_spawn-1];
    std::string line = "";
    lock =  PTHREAD_MUTEX_INITIALIZER;
    size_t counter = 0;
    while(!in.eof()){
        for(size_t x = 0; x<threads_to_spawn;x++){
            counter = x;
            if(!in.eof()){
                //just check agian whether we've reached eof
            pthread_create(&threads[x],NULL,runner, (void* ) &in);
            }else{
                break;
            }
        }
        for(size_t x = 0; x<counter;x++){
            //we use counter here and not threads_to_spawn in case we break out of
            //the for loop above prematurely due to end of file, this way we won't
            //be calling join() on threads that aren't being used
            pthread_join(threads[x], NULL);
        }
    }
    
    //destroy condition, and mutex
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    std::cout<<"finished reading successfully"<<std::endl;
}

void* reader::runner(void* arg) {
        pthread_mutex_lock(&lock);
        std::string line = "";
        std::ifstream* s = (std::ifstream*)arg;
        pthread_cond_wait(&cond, &lock);
        getline(*s, line);
        // std::cout<<line<<std::endl;
        writer::append(line);
        if(pthread_mutex_unlock(&lock)!= 0){
            std::cout<<"something went wrong when unlocking the mutex"<<std::endl;
        };     
        if(pthread_cond_signal(&cond) != 0){
            std::cout<<"something went wrong when sending the condition signal"<<std::endl;
        };
        return nullptr; 
    }

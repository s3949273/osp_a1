/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

std::deque<std::string> writer::queue =  std::deque<std::string>();
std::ofstream writer::out;
unsigned writer::threads_to_spawn;
pthread_cond_t writer::line_ready;
pthread_mutex_t writer::lock;


bool writer::is_finished;

void writer::init(const std::string& name) {
    //open the file
    writer::out.open(name);
    is_finished = false;
}

void writer::run() {
    //we want to keep creating threads until the is_finished variable is true
    pthread_t threads[threads_to_spawn];
    lock = PTHREAD_MUTEX_INITIALIZER;
    if(out.is_open()){
        std::cout<<"file ready to be written to"<<std::endl;
        while(!queue.empty()){
            //do stuff here
            for(size_t i = 0; i<threads_to_spawn; i++){
                if(pthread_create(&threads[i], NULL, runner, (void* )&out)==0){
                    std::cout<<"created writer thread: "<<i<<std::endl;
                }else{
                    std::cout<<"something went wrong joining writer thread: "<<i<<std::endl;
                }
            }   
            for(size_t j = 0; j<threads_to_spawn; j++){
                pthread_join(threads[j], NULL);
                std::cout<<"joined writer    thread: "<<j<<std::endl;
            }
        }
    pthread_mutex_destroy(&lock);
    out.close();
    std::cout<<"finished writing to file"<<std::endl;   
    }else{
        std::cout<<"ERR: file was not open to be written to"<<std::endl;
    }


}

void writer::signal(){
    pthread_cond_signal(&line_ready);
}

void* writer::runner(void* arg) {
    //lock the mutex
    if(pthread_mutex_lock(&lock)!= 0){
        std::cout<<"something went wrong obtaining the writer lock"<<std::endl;
    }
    std::ofstream* o = (std::ofstream*)arg;
    if(!queue.empty()){
        *o << queue.front() <<std::endl;
        queue.pop_front();
    }
    if(pthread_mutex_unlock(&lock) !=0){
        std::cout<<"something went unlocking the lock"<<std::endl;
    };
    return nullptr;
}

void writer::append(const std::string& line) {
    //done
    writer::queue.push_back(line);

}

void writer::setfinished(){
    is_finished = true;
}

void writer::print(){
    for (auto it = writer::queue.begin(); it != writer::queue.end(); ++it){
        std::cout << *it<<std::endl;
        std::cout<<"hello"<<std::endl;
    }
}
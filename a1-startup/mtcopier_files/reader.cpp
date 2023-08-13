
    /**
     * startup code provided by Paul Miller for COSC1114 - Operating Systems
     * Principles
     **/
    #include "reader.h"
    #include <unistd.h>
    #include "writer.h"

/**
 * implement the functions needed for this class
 **/
std::ifstream reader::in;

pthread_mutex_t* reader::r_mutex;

void reader::init(const std::string& name) {
    in.open(name);
}
void reader::run() {
        if(in.is_open()){
            if(pthread_create(&r_thread, NULL, runner, NULL)!=0){
                std::cout<<"something went wrong creating the thread"<<std::endl;
            }
        }else{
            std::cout<<"input file was not open"<<std::endl;
        }

    }

    void* reader::runner(void* arg) {   
        while(true){    
            std::string line = "";
            if(pthread_mutex_lock(r_mutex)!=0){
                std::cout<<"something went wrong locking"<<std::endl;
            }
            if(getline(in, line)){
                writer::append(line);
                pthread_cond_signal(&writer::line_ready);
            }else{
                if(!writer::finished){
                    writer::setfinished();
                }
                if(pthread_mutex_unlock(r_mutex)!=0){
                    std::cout<<"something went wrong unlocking reader lock"<<std::endl;
                }
                break;
            }
            if(pthread_mutex_unlock(r_mutex)!=0){
                std::cout<<"something went wrong unlocking"<<std::endl;
            }
        }
        pthread_exit(NULL);
        return nullptr; 
    }
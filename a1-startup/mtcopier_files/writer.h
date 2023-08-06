/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include <pthread.h>

#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#ifndef WRITER
#define WRITER
class writer {
   public:
    /**
     * Please note that methods and data need to be static as there's a
     * variety of information that needs to be coordinated between writers
     * such as locks and other shared data. Also, as the pthread library
     * is a c library, it does not know about classes so ruuner in particular
     * needs to be static. You can pass in instances into the function as
     * pointers though.
     **/
        static void init(const std::string& name);
        static void* runner(void*);
        void run();
        static void append(const std::string& line);
        //had to be added
        static void setfinished();
        //doesn't matter if this is public
        static void print();
        static unsigned threads_to_spawn;
        static pthread_cond_t line_ready;
        static void signal();
    private:

        static std::ofstream out;
        static std::deque<std::string> queue;
        static bool is_finished;
        
        static pthread_mutex_t lock;
        static pthread_t threads;
        
};
#endif

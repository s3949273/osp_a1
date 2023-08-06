/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

/**
 * implement these functions requred for the writer class
 **/
std::ofstream writer::out;
std::deque<std::string> writer::queue;
void writer::init(const std::string& name){

}

void writer::run() {}

void* writer::runner(void* arg) { return nullptr; }

void writer::append(const std::string& line) {
    queue.push_back(line);
}

void writer::setfinished() {}

void writer::print(){
    for(auto i: queue){
        std::cout<<i<<std::endl;
    }
}
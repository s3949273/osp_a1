/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/

#include "writer.h"

/**
 * provide your implementation for the writer functions here
 **/
writer::writer(const std::string& name):
    queue(*new std::deque<std::string>())
{
    out.open(name);
}

void writer::run() {
    while(this->queue.size() > 1){
        out << this->queue.front()<<std::endl;
        this->queue.pop_front();
        std::cout<<this->queue.size()<<" ";
    }
    out << this->queue.front();
    this->queue.pop_front();
    //close the ofstream
    out.close();
}

void writer::append(const std::string& line) {
    //resize the queue to have additional space
    //push the new line into the queue
    this->queue.push_back(line);
}

/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "writer.h"

#include "reader.h"

std::deque<std::string> writer::queue =  std::deque<std::string>();
std::ofstream writer::out;
/**
 * implement these functions requred for the writer class
 **/
void writer::init(const std::string& name) {
    writer::out.open(name);
}

void writer::run() {
    
}

void* writer::runner(void* arg) { return nullptr; }

void writer::append(const std::string& line) {
    writer::queue.push_back(line);

}

void writer::setfinished() {}

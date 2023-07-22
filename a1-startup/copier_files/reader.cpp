/**
 * startup code provided by Paul Miller for COSC1114 - Operating Systems
 * Principles
 **/
#include "reader.h"
#include <functional>

reader::reader(const std::string& name, writer& mywriter):thewriter(mywriter){   
    //open the ifstream with given name 
    in.open(name);
}

void reader::run() {
    std::string line;
    while(std::getline(in, line)){
        //while there is a line, append the line to the writer's queue
        // std::cout<<line<<std::endl;
        this->thewriter.append(line);
    }
    in.close();
    // std::cout<<"this end of run fn"<<std::endl;
    this->thewriter.run();
    
}

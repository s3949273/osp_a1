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
    while(std::getline(in, line, '\n')){
        //while there is a line, append the line to the writer's queue 
        if(!in.eof() && !in.fail()){
            this->thewriter.append(line);
        }
        if(in.eof()){
            break;
        }
    }
    in.close();
    
    this->thewriter.run();
    
}

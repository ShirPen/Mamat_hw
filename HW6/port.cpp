#include <iostream>
#include "string.h"
#include "port.h"
#include "generic-field.h"
#include <cstring>

#define PORTAMNT 2

port::~port(){}

port::port(const String &Port) : GenericField(){

    port_name = Port;
    min_val = 0;
    max_val = MAXPORT;

}

bool port::set_value(String value) {

    String *port_range;
    size_t size = 0;

    value.split("-", &port_range, &size);

    //check that we received a valid range of 2 ports
    if(size != PORTAMNT){
        delete[] port_range;
        return false;
    }

    //trims ports and turns them to shorts
    min_val = (port_range[0].trim()).to_integer();
    max_val = (port_range[1].trim()).to_integer();

    delete[] port_range;
    return true;
}

bool port::match(String packet) {

    String *packet_split;
    String *ports;

    size_t ps_size = 0;
    size_t size = 0;

    packet.split(",", &packet_split, &ps_size);
    for(int i = 0; i<int(ps_size); i++){
        packet_split[i] = packet_split[i].trim();
        packet_split[i].split("=", &ports, &size);
        ports[0] = ports[0].trim();
        if(ports[0].equals(port_name)){
            break;
        }
    }

    int curr_port = (ports[1].trim()).to_integer();
    delete[] packet_split;
    delete[] ports;

    return ((curr_port >= this->min_val) && (curr_port <= this->max_val));

}
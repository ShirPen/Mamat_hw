//
// Created by Noam Cooper on 6/5/23.
//

#ifndef PORT_H
#define PORT_H

#define MAXPORT 65535


#include "string.h"
#include "generic-field.h"

class port : public GenericField{
        unsigned short min_val;
        unsigned short max_val;

        String port_name;

    public:
        port(): min_val(0), max_val(MAXPORT), port_name(nullptr){}
        bool match(String packet);
        bool set_value(String value);
        port(const String &Port );
        ~port();


};
#endif //PORT_H

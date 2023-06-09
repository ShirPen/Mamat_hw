#ifndef IP_H
#define IP_H

#include <stddef.h>
#include <iostream>
#include "generic-field.h"

class ip : public GenericField {
    String ip_name;
    unsigned int mask_ip;
    int mask_num;

public:
    //constructors
    ip():  ip_name(nullptr), mask_ip(0), mask_num(0){}
    ip(const String &ip);
    //overrides match function in GenericField
    bool match(String packet);
    //overrides set_value function in GenericField
    bool set_value(String value);
    //destructor
    ~ip();
};

#endif //HW6_IP_H
#include <iostream>
#include "input.h"
#include "string.h"
#include "port.h"
#include "ip.h"
#include "generic-field.h"


int main(int argc, char **argv){

    if(check_args(argc, argv)){
        return 1;
    }

    String input(argv[1]);
    String *rule;
    size_t p_size = 0;

    input.split("=", &rule, &p_size);
    String name = rule[0].trim();
    String val = rule[1].trim();

    if(name.equals("src-ip") || name.equals("dst-ip")){
        ip main_ip(name);
        main_ip.set_value(val);
        parse_input(main_ip);
    }

    if(name.equals("src-port") || name.equals("dst-port")){
        port main_port(name);
        main_port.set_value(val);
        parse_input(main_port);

    }

    delete[] rule;

    return 0;
}
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
    std::cout << "check args succeeded" << std::endl;
    String input(argv[1]);
    String *rule;
    size_t p_size = 0;

    input.split("=", &rule, &p_size);
    String name = (rule[0]).trim();
   // cout << name.data << endl;
    String val = rule[1];
    std::cout << "split succeeded" << std::endl;
    name.string_print();
    if(name.equals("src-ip") || name.equals("dst-ip")){
    	std::cout << "its an ip" << std::endl;
    	ip main_ip(name);
    	std::cout << "created main ip" << std::endl;
        main_ip.set_value(val);
        parse_input(main_ip);
    }

    if(name.equals("src-port") || name.equals("dst-port")){
    	std::cout << "its a port" << std::endl;
    	port main_port(name);
        main_port.set_value(val);
        parse_input(main_port);

    }

    delete[] rule;

    return 0;
}

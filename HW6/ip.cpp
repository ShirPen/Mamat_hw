#include <iostream>
#include "string.h"
#include "ip.h"
#include "generic-field.h"
#include <cstring>

#define TOTALBYTES 4
#define SHIFT 8
#define MASKMAX 32


unsigned int int_convr(const String &ip);

ip::~ip(){}

ip::ip(const String &ip) : GenericField() {

        ip_name = ip;
        mask_num = 0;
        mask_ip = 0;
}
// convert a string of number to int
unsigned int int_convr(const String &ip){

    String *ip_bytes;
    size_t size = 0;
    ip.split(".", &ip_bytes, &size);

    unsigned int ip_int = 0;
    int curr;
    for (int i = 0; i < TOTALBYTES ; i++ ) {
        curr = ip_bytes[i].to_integer();
        ip_int += (curr << ((3 - i) * SHIFT));
        ip_int |= (curr << ((3 - i) * SHIFT));
    }
    delete[] ip_bytes;
    return ip_int;
}

bool ip::set_value(String value) {
    String *ip_mask;
    size_t size = 0;
    value.split("/", &ip_mask, &size);
    unsigned int int_ip = int_convr(ip_mask[0]);
    unsigned int mask = ip_mask[1].to_integer();
    //checks that we got a valid mask number
    if(mask < 0 || mask > MASKMAX){
        delete[] ip_mask;
        return false;
    }

    this->mask_num = mask;
    this->mask_ip = int_ip >> (MASKMAX - mask_num);
    delete[] ip_mask;
    return true;

}
bool ip::match(String packet) {
    String *packet_split;
    String *ip_addrs;
    size_t ps_size = 0; //size of packet split array
    if(packet.equals("")){
    	return false;
    }
    packet.split(",",&packet_split,&ps_size);
    for(int i=0; i<(int)ps_size; i++){
        packet_split[i] = packet_split[i].trim();
        packet_split[i].split("=", &ip_addrs, &ps_size);
        ip_addrs[0] = ip_addrs[0].trim();
        if(ip_addrs[0].equals(this->ip_name)){
            break;
        }
        delete[] ip_addrs;
    }
    //ip to be checked against mask
    unsigned int curr_ip = int_convr(ip_addrs[1]);
    //remove the unwanted number of bits
    curr_ip = curr_ip >> (MASKMAX - mask_num);

    //deallocate temporary memory allocations
    delete[] packet_split;
    delete[] ip_addrs;

    //returns true if the ip number meets the rule
    return (curr_ip == this->mask_ip);
}



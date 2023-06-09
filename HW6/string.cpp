#include <iostream>
#include "string.h"
#include <cstring>

String::String(): length(0){
    data = new char [1];
    data[1] = '\0';

}

String::String(const String &str){
    data = new char[str.length + 1];
    strcpy(data, str.data);
    length = str.length;
}

String::String(const char *str){
    data = new char[strlen(str) +1];
    strcpy(data, str);
    length = strlen(str);
}

String::~String(){
    delete[] data;
}

String& String::operator=(const String &rhs){
    if(this != &rhs){
        delete[] data;
        length = rhs.length;
        data = new char[length + 1];
        strcpy(data, rhs.data);
    }

    return *this;

}

String& String::operator=(const char *str){

    delete[] data;
    data = new char [strlen(str) + 1];
    strcpy(data, str);
    length = strlen(str);
    return *this;

}

bool String::equals(const String &rhs) const{

    //length check to save runtime in case of diff length
    if(length != rhs.length){
        return false;
    }
    else{
        if( strcmp(data, rhs.data) ){
            return false;
        }
    }

    return true;
}	

bool String::equals(const char *rhs) const {

    if(length != strlen(rhs)){
        return false;
    }
    else{
        if( strcmp(data, rhs) ){
            return false;
        }
    }

    return true;
}

void String::split(const char *delimiters, String **output, size_t *size) const{

    if( *data == '\0'){
        *output = NULL;
        return;
    }

    char *temp = new char[length + 1];
    strcpy(temp, data);

    //calculates amount of sub strings
    int amount = 0;
    char *token = strtok(temp, delimiters);

    while(token != NULL){
        amount++;
        //start from end of last call (last time delimiter was replaced with '\0')
        token = strtok(NULL, delimiters);
    }
    *size = amount;

    if(output == NULL){
        return;
    }

    //Create array of Strings
    String *sub_strings = new String[amount];
    char *temp_2 = new char[length + 1];
    strcpy(temp_2, data);

    //Loop to insert tokens into Strings array
    int curr = 0;
    char *token_2 = strtok(temp, delimiters);
    while(token_2 != NULL || curr<amount){
        sub_strings[curr].data = token_2;
        sub_strings[curr].length = strlen(token_2);
        curr++;
        token_2 = strtok(NULL, delimiters);
    }

    *output = sub_strings;

    delete[]temp;
    delete[]temp_2;

}

int String::to_integer() const{
    return atoi(data);
}

String String::trim() const{

    //leading white spaces
    int leading = 0;
    while(data[leading] == ' '){
        leading++;
    }

    //trailing white spaces
    int trailing = 0;
    int end = length;
    while( data[end-1] == ' '){
        trailing++;
        end--;
    }

    int new_size = length - leading - trailing;
    char *new_data = new char[new_size + 1];
    int j = 0;
    for(int i = leading; i<=end; i++){
        new_data[j] = data[i];
        j++;
    }
    new_data[j] = '\0';

    String out;
    strcpy(out.data, new_data);
    out.length = new_size;

    delete[] new_data;

    return out;

}

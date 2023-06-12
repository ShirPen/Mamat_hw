#include <iostream>
#include "string.h"
#include <string.h>
#include <cstring>
using std::cout;
using std::endl;

String::String() {
    data = new char [1];
    data[0] = '\0';
    length = 0;

}

String::String(const String &str){
	if(str.data == NULL){
		return;
	}
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
	if(data != nullptr){
	    delete[] data;
	}
}

String& String::operator=(const String &rhs){
    if(equals(rhs)){
        return *this;
    }
    delete[] data;
    length = rhs.length;
    data = new char[length + 1];
    strcpy(data, rhs.data);
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

	if( *data == '\0' || length == 0){
		*output = NULL;
    	*size = 0;
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
    	delete[] temp;
        return;
    }

    //Create array of Strings
    String *sub_strings = new String[amount];
    char *temp_2 = new char[length + 1];
    strcpy(temp_2, data);

    //Loop to insert tokens into Strings array
    int curr = 0;
    char *token_2 = strtok(temp_2, delimiters);
    while (token_2 != NULL || curr < amount) {
    	sub_strings[curr].data = new char[strlen(token_2) + 1];
        strcpy(sub_strings[curr].data, token_2);
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

    int leading = 0;
    int trailing = length - 1;
    String out;
    //leading white spaces
    while(data[leading] == ' '){
        leading++;
    }
    
    if(leading ==(int)length){
    	return out;
    }
	
    //trailing white spaces
    while(data[trailing] == ' ') {
        trailing--;
    }

    int new_size = trailing - leading +2;
    char *new_data = new char[new_size];
    int j = 0;
    for(int i = leading; i<=trailing; i++){
        new_data[j] = data[i];
        j++;
    }
    new_data[j] = '\0';

    out = new_data;
//    strcpy(out.data, new_data);
//    out.length = new_size;

    delete[] new_data;

    return out;

}
	void String::string_print(){
		std::cout << data << std::endl;
	}


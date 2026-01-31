#include "ResponseParser.h"
#include<iostream>
#include<sstream>
#include<unistd.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/socket.h>

// Function to read a single character from the socket.
static bool readChar(int sockfd , char &c){
    ssize_t r = recv(sockfd , &c , 1, 0);
    return (r == 1);
}

// Function to read a line from the socket until it encounters a carriage return.
static std::string readLine(int sockfd){
    std::string line;
    char c;
    while(readChar(sockfd , c)){
        // if(c == '\r'){
        //     // expext '\n' next; read and break;
        //     readChar(sockfd , c);
        //     break;
        // }
        if (c == '\r') {
            char lf;
            readChar(sockfd, lf); // should be '\n'
            break;
        }

        line.push_back(c);
    }
    return line;
}

std::string ResponseParser::parseResponse(int sockfd){
    char prefix;
    if(!readChar(sockfd , prefix)) {
        return ("Error: No Response or connection closed.");
    }

    switch(prefix) {
        case '+' : return parseSimpleString(sockfd);
        // case '-' : return parseSimpleErrors(sockfd);
        // case ':' : return parseInteger(sockfd);
        // case '$' : return parseBulkString(sockfd);
        // case '*' : return parseArray(sockfd);
        default:
            return "Error: Unknown Reply type.";
    }
}

std::string ResponseParser::parseSimpleString(int sockfd){
    return readLine(sockfd);
}

// std::string ResponseParser::parseSimpleErrors(int sockfd){
    
// }

// std::string ResponseParser::parseInteger(int sockfd){

// }

// std::string ResponseParser::parseBulkString(int sockfd){
    
// }

// std::string ResponseParser::parseArray(int sockfd){
    
// }


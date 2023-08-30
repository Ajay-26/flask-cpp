#include <iostream>
#include "server/http_server.hpp"

int main(int argc, char** argv){
    HTTP_Server s("127.0.0.1", "6667");
    s.start_server();
    return 0;
}
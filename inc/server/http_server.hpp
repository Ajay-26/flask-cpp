#ifndef HTTP_SVR_HDR 
#define HTTP_SVR_HDR

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <thread>
#include <unordered_map>
//os related libraries
#include <unistd.h>

//not sure what the C++ equivalent headers are
#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h>

class HTTP_Server{
public:
    HTTP_Server(const char *ip_addr, const char* port);
    void start_server();

private:
    char* port;
    char* ip_addr;
    int buffer_size;
    int backlog;
    int passive_socket_fd;
    char* server_hostname;
};

#endif //HTTP_SVR_HDR
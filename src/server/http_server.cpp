#include "server/http_server.hpp"

HTTP_Server::HTTP_Server(const char* ip_addr, const char* port){
    this->ip_addr = new char[std::strlen(ip_addr)];
    std::strcpy(this->ip_addr, ip_addr);

    this->port = new char[std::strlen(port)];
    std::strcpy(this->port, port);

    this->backlog = 10;
    this->buffer_size = 1024;
}

void HTTP_Server::start_server(){
    //using the struct key word because the header files are native to C 
    //we do not want overlap with any other type with the same name in the global namespace
    struct addrinfo hints;  //this variable will hold the hints required to the call to getaddrinfo()
    struct addrinfo* p;     //iterator for nodes of list returned by getaddrinfo()
    struct addrinfo* res;   //head of list returned by getaddrinfo()

    struct sockaddr_storage client_addr;    //placeholder for client_addr
    socklen_t addr_size = sizeof (struct sockaddr_storage);                    //size of client addr placeholder

    int active_socket_fd;   //file descriptor for active socket

    int ret;    //placeholder for return value

    char *client_name;

    std::memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_UNSPEC;        //do not specify whether IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    //socket stream as opposed to socket_datagram
    hints.ai_flags = AI_PASSIVE;        //fill my IP address for me

    this->buffer_size = buffer_size;

    //first param is NULL because domain name is unspecified, plus hints.ai_flags is passive
    ret = getaddrinfo(NULL, this->port, &hints, &res);
    if(ret != 0){
        std::printf("Call to getaddinfo failed! Value of errno = %d, exiting function!\n", errno);
        return;
    }

    //get the server hostname
    this->server_hostname = new char[this->buffer_size];
    ret = gethostname(this->server_hostname, this->buffer_size);
    if(ret == -1){
        std::printf("Could not get server hostname, value of errno = %d, exiting function!\n", errno);
        return;
    }

    for(p = res; p != nullptr; p = p->ai_next){
        this->passive_socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(this->passive_socket_fd < 0){
            std::printf("Call to create socket failed, value of errno = %d\n", errno);
            continue;
        }

        ret = bind(this->passive_socket_fd, p->ai_addr, p->ai_addrlen);
        if(ret < 0){
            std::printf("Call to bind failed, value of errno = %d\n", errno);
            close(this->passive_socket_fd);
            continue;
        }

        ret = listen(this->passive_socket_fd, this->backlog);
        if(ret < 0){
            std::printf("Call to listen failed, value of errno = %d\n", errno);
            close(this->passive_socket_fd);
            continue;
        }
        break;
    }

    if(p == nullptr){
        std::printf("No available socket for the server to listen with, returning from function\n");
        return;
    }

    //we do not need the linkedlist now, the server is listening on this->passive_socket
    freeaddrinfo(res);

    //create an infinite loop and keep accepting clients
    while(1){
        active_socket_fd = accept(this->passive_socket_fd, (struct sockaddr*) &client_addr, &addr_size);
        if(active_socket_fd < 0){
            //no one requested to connect
        }else{
            //someone has requested to connect
            //prepare to handle the client here
            std::cout << "Got client\n";
        }
    }
}
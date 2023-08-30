#ifndef HTTP_PKT_HDR
#define HTTP_PKT_HDR

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

constexpr const int bufsize = 1024;

enum class http_req_types{
    GET, POST
};

struct http_packet_t{
    http_req_types request_type;
    int http_error_code;
    char* content;
    int content_length;
};

void send_http_packet(int sockfd, http_packet_t pkt);

#endif //HTTP_PKT_HDR
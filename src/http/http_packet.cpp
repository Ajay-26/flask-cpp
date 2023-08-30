#include "http/http_packet.hpp"

void send_http_packet(int sockfd, http_packet_t pkt){
    char* header = new char[bufsize];
    char* req;
    if(pkt.request_type == http_req_types::GET){
        req = "GET";
    }else if(pkt.request_type == http_req_types::POST){
        req = "POST";
    }
}
//
//  serverUDP.cpp
//  Server
//
//  Created by Sue Cho on 2020/03/22.
//  Copyright © 2020 Sue Cho. All rights reserved.
//

#include "serverUDP.hpp"

server_UDP::server_UDP(int port){
    portNo = port;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("Failed to Open Socket");
        return;
    }
    mySocketAddress.sin_family = AF_INET;
    mySocketAddress.sin_port = htons(portNo);
    mySocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    

    if(bind(sock, (struct sockaddr_in *) &mySocketAddress, sizeof(struct sockaddr_in)) != 0){
        perror("Failed to Bind");
        close(sock);
        return;
    }

}

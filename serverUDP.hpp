//
//  serverUDP.hpp
//  Server
//
//  Created by Sue Cho on 2020/03/22.
//  Copyright © 2020 Sue Cho. All rights reserved.
//

#ifndef serverUDP_hpp
#define serverUDP_hpp

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
//#include <arpa/inet.h>
#include <cstdio>


class serverUDP{
private:
    int sock; // socket
    int portNo; // port number to use
    struct sockaddr_in mySocketAddress; // server's add
    struct sockaddr_in yourSocketAddress; // client's add

public:
    serverUDP (int port);
   
};

#endif /* serverUDP_hpp */

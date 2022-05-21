#include <node.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <cstdlib>

#include <unistd.h> 


#include <fstream>

#include "json.hpp"
using json = nlohmann::json;



namespace calculate {
	using v8:: FunctionCallbackInfo;
	using v8 :: Local;
	using v8 :: Object;
	using v8 :: Value;
	void magic(const FunctionCallbackInfo<Value>&args)
	{
    std::string tempResponse="HTTP/1.1 200 OK\nConnection: keep-alive\nContent-Type: text/html\nContent-Length: 15\n\nsdfkjsdnbfkjbsf";
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Listen to port 9999 on any address
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to
                                   // network byte order
  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
while(true){
    if (listen(sockfd, 10) < 0) {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
  if (connection < 0) {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Read from the connection
  //////////////////////////////////////////////
    //todo here get the card..
    char buffer[100];
    auto bytesRead = read(connection, buffer, 100);
    std::cout << "The message was: " << buffer;

std::ifstream ifs("cards.json");
// json j = json::parse(ifs);
   
    // Print the values
             

    /////////////////////////////////////////
    
    send(connection, tempResponse.c_str(), tempResponse.size(), 0);
  close(connection);
  close(sockfd);
	}
}
	void Initialize(Local<Object> exports) {
		NODE_SET_METHOD(exports, "magic", magic);
	}

	NODE_MODULE(NODE_GYP_MODULE_NAME,Initialize);
}

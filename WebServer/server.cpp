#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include "threadpool/ThreadPool.h"


const int NUM_THREADS = 1000; // need to change

#define PORT 5000

void respond (int sock_num);
char *ROOT;

int main( int argc, char *argv[] ) {
  int sockfd, newsockfd, portno = PORT;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  clilen = sizeof(cli_addr);
  ROOT = getenv("PWD");

  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  // port reusable
  int tr = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* TODO : Now bind the host address using bind() call.*/
  if(bind(sockfd,  (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) != 0) {
    perror ("Can't bind to socket");
    exit(1);
  }
  /* TODO : listen on socket you created */
  if (listen(sockfd, 100) != 0) {
    perror("Can't listen to socket");
    exit(1);
  }  



  printf("Server is running on port %d\n", portno);
  
  ThreadPool pool(NUM_THREADS);
  
  while (1) {
    /* TODO : accept connection */

    socklen_t cli_size = sizeof(cli_addr);    
    newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr, &cli_size);
   if (newsockfd < 0) {
      printf("Can't accept current client\n");
      continue;
   } 
    // TODO : implement processing. there are three ways - single threaded, multi threaded, thread pooled
     // pthread_t t1;
     // pthread_create(&t1, NULL, &respond, (void *) &newsockfd);

   //  pool.enqueue([newsockfd] {
                //std::cout << "hello " << i << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(1));
                //std::cout << "world " << i << std::endl;
     //});
                respond(newsockfd);
     
  }

  return 0;
}


std::string getFilePath(std::vector< std::string > request) { 
  std::string absolute_path (ROOT);
  std::string default_path = "/index.html";
  if (request.size()< 2 || request[1].length() <= 1) absolute_path += default_path; 
  else absolute_path += request[1]; // requested file
  return absolute_path;  
}

bool constructHeaderMsg(std::string &head, std::string absolute_path, 
  			std::vector<std::string> request, int image_length) {
    head = "";
    if (absolute_path.find(".jpg") == std::string::npos) {
     head += "HTTP/1.1 200 OK \r\n";
      head += "Content-Type: text/html \r\n";
      head += "Content-Encoding: UTF-8 \r\n";
      head += "Connection: close \r\n";
    }
    else {
 //     std::cout << fileContent;
    head += "HTTP/1.1 200 OK \r\n";
 
 //   head += "Connection: close \r\n";
      head += "Content-Type: image/jpeg \r\n";
      head += "Content-Transfer-Encoding: binary \r\n";
      head += "Content-Length: " + std::to_string(image_length) + " \r\n";
 //   head += "Connection: keep-alive \r\n";
    }
    head += "\r\n";
    return true;
}


const int IMAGE_SIZE = 2000000;

bool getFileContent(std::string absolute_path, std::string &fileContent, int &file_length, int sock) {
    std::ifstream file_r;
    file_r.open(absolute_path.c_str(), std::ios::binary);
    if (!file_r.is_open()) {
	      printf("can't open requested file\n");
	      return false;       
    } 
    
    fileContent = "";
    if (absolute_path.find(".jpg") != std::string::npos) {    
	char *buffer = new char[IMAGE_SIZE];
	file_r.read(buffer, sizeof(char) * IMAGE_SIZE);
   	file_length = (int) file_r.gcount() ;
   	file_r.close();
	    return true;
   }
	    int c;
	    std::string line;
	    while (std::getline(file_r, line)) {
	       fileContent += line;
	    }
	    file_r.close();
            file_length = -1; // since we don't need it for http text    
   return true;
}



void respond(int sock_num) {
  //int *sock_p = (int*) sock_num;
  int sock = sock_num;
  printf("\n\n\nClient socket id %d\n", sock);
  
  int n, i;
  char buffer[9999];
  char abs_path[256];
  bzero(buffer,9999);
  n = recv(sock,buffer,9999, 0);

  std::vector<std::string> request;

  if (n < 0) {
    printf("recv() error\n");
    return;
  } else if (n == 0) {
    printf("Client disconnected unexpectedly\n");
    return;
  }
  char* request_msg = strtok(buffer, " \t");
  while (request_msg != NULL) {
       std::string parsed_string (request_msg);
       request.push_back(parsed_string); 
       request_msg = strtok(NULL, " \t"); 
  }
  for (auto r : request){
  //   std::cout << r << "\n";
  }
  
  std::string absolute_path = getFilePath(request);
   std::cout <<"File Path: " << absolute_path << "\n";
  int file_length = 0;
  std::string fileContent = "";									  
  bool read_from_file = getFileContent(absolute_path, fileContent, file_length, sock);
  if (!read_from_file) {
    printf("Read from file error.\n");
    return;
  }      
  
  std::string header_msg;
  bool construct_header = constructHeaderMsg(header_msg, absolute_path, request, file_length);
  //std::cout <<"Header Message:\n"<< header_msg <<"\n";
 

       
   
  int success = send(sock, header_msg.c_str(), strlen(header_msg.c_str()), 0);
  
  if (absolute_path.find(".jpg") == std::string::npos) {    
    success = send(sock, fileContent.c_str(), strlen(fileContent.c_str()), 0);
     shutdown(sock, SHUT_RDWR);
    close(sock);

     return;
  } else { 
     printf("Successfully sent image. Code: %d\n", success);
  }  
   
   FILE *image;
   image = fopen(absolute_path.c_str(), "rb");
   if (image == NULL) {
     std::cout << "Can't read image :(\n";
     return;
   }

   fseek(image, 0, SEEK_END);
   file_length = ftell(image);
   rewind (image);

   char * send_buffer =  new char[IMAGE_SIZE];
   size_t result = fread(send_buffer, 1, file_length, image);
   if (result == 0) {
     std::cout << "F, not working";
     return;          
   }
   //std::cout << result << " - " << file_length << "\n";
   //for (int i = 0 ; i <  file_length ; ++i) {
     //fileContent += send_buffer[i];
     //std::cout << send_buffer[i] << " " << fileContent[i] << "\n";
    //}
   success = send(sock, send_buffer, result, 0);
  
   delete send_buffer;
  

  shutdown(sock, SHUT_RDWR);
  close(sock);

}

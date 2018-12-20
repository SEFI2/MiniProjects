#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


const string DEFAULT_USER = "default_username";
const string DEFAULT_HOST = "127.0.0.1";
const int DEFAULT_PORT = 3000;
const int DEFAULT_ROOM = 10;
const string DEFAULT_HEARTBEAT_MSG = "IWANTTOCHECKYOURHEALTHCLIENT";
const string DEFAULT_HEALTH_ANSWER = "IAMALIVETHANKS";
const string DEFAULT_CONNECTION_MSG = "IWANTTOCONNECT";
const string DEFAULT_QUIT_MSG = "BYEBYE";
const string DEFAULT_QUIT_REQUEST = "IWANTTOQUITMAAN";
string CURRENT_USER;
string CURRENT_HOST;
int CURRENT_PORT;
int CURRENT_ROOM;
int CURRENT_SERVER;



vector<string>  Split (string str, string divider) {
  vector <string> result;
  size_t pos = 0;
  std::string token;
  while ((pos = str.find(divider))
          != string::npos) {
    token = str.substr(0, pos);
    result.push_back(token);
    str.erase(0, pos + divider.length());
  }
  if (str.length() > 0)
    result.push_back(str);
  vector<int> to_be_deleted;
  for (int i = 0 ; i < (int) result.size() ; ++i) {
    if (result[i] == divider) {
      to_be_deleted.push_back(i);
    }
  }

  for (int i = to_be_deleted.size() - 1 ; i >= 0 ; --i) {
    result.erase(result.begin() + i);
  }

  return result;
}

void *listenServerResponse(void *data) {
  int buflen = 1024;
  char* buf = new char[buflen+1];

  while (true) {
        // read the response
        memset(buf,0,buflen);
        recv(CURRENT_SERVER,buf,buflen,0);
        string received_msg = (string) buf;
        if (received_msg.find(DEFAULT_HEARTBEAT_MSG) !=
            string::npos) {
          send(CURRENT_SERVER, DEFAULT_HEALTH_ANSWER.c_str(),
                      DEFAULT_HEALTH_ANSWER.length(), 0);
        } if (received_msg.find(DEFAULT_QUIT_MSG) !=
            string::npos) {
          break;
        }
        else {
          cout << received_msg << "\n\n";
        }
  }
  delete[] buf;
  return NULL;
}

int
main(int argc, char **argv)
{
    if (argc > 1) {
      vector<string> split = Split(argv[1], ":");
      CURRENT_HOST = split[0];
    	CURRENT_PORT = stoi(split[1]);
      CURRENT_ROOM = atoi(argv[2]);
      CURRENT_USER = argv[3];
    } else {
      CURRENT_HOST = DEFAULT_HOST;
      CURRENT_PORT = DEFAULT_PORT;
      CURRENT_ROOM = DEFAULT_ROOM;
      CURRENT_USER = DEFAULT_USER;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(CURRENT_PORT);
		inet_aton(CURRENT_HOST.c_str(), &server_addr.sin_addr);

    CURRENT_SERVER = socket(PF_INET, SOCK_STREAM, 0);
    if (CURRENT_SERVER < 0) {
      cout << "Can't create socket instance\n";
      return 0;
    }

    if (connect(CURRENT_SERVER, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
      cout << "Can't connect\n";
      return 0;
    }

    pthread_t listenServerResponse_t;
    int create_res = pthread_create(&listenServerResponse_t, NULL,
                                     listenServerResponse, NULL);
    if (create_res)
    {
      cout << "Error occured while creating the thread for listenServerResponse\n";
      return 0;
    }


    string input = "/" + DEFAULT_CONNECTION_MSG  + " " + CURRENT_USER + " " + to_string(CURRENT_ROOM);
    do
    {
      if (input.length() > 0) {
        send(CURRENT_SERVER, input.c_str(), input.length(), 0);
        if (input.find("/quit") != string::npos) {
          break;
        }
      }
    } while (getline(cin, input));

    void *thread_status;
    int join_res = pthread_join(listenServerResponse_t, &thread_status);
    if (join_res) {
      cout << "Unable to join listenServerResponse" << join_res << "\n";
    }

    close(CURRENT_SERVER);
    pthread_exit(NULL);
}

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>

#include <iostream>

using namespace std;

const int BUFF_SIZE = 1024;



string trim(string input) {
	string output = "";
  for (int i = 0 ; i < (int) input.length() ; ++i){
		if (input[i] != ' ') {
			output += input[i];
		}
	}
	return output;
}

vector<string> trim(vector<string> input) {
  vector<string> output;
	for (int i = 0 ; i < (int) input.size() ; ++i) {
		output.push_back(trim(input[i]));
	}
	return output;
}



pthread_t my_threads[10000];

const int DEFAULT_PORT = 2500;
const string DEFAULT_HEARTBEAT_MSG = "IWANTTOCHECKYOURHEALTHCLIENT";
const string DEFAULT_HEALTH_ANSWER = "IAMALIVETHANKS";
const string DEFAULT_CONNECTION_MSG = "IWANTTOCONNECT";
const string DEFAULT_QUIT_MSG = "BYEBYE";
const string DEFAULT_QUIT_REQUEST = "IWANTTOQUITMAAN";

vector<int> user_room;
vector<int> user_client_id;
vector<string> user_name;

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


int addNewUser(int client_id, int room, string username) {
  int ret_id = user_room.size();
  user_room.push_back(room);
  user_client_id.push_back(client_id);
  user_name.push_back(username);
  return ret_id;
}

int findUserByID (int client_id) {
  for (int i = 0 ; i < (int) user_client_id.size() ; ++i){
    if (user_client_id[i] == client_id) {
      return i;
    }
  }
  return -1;
}

int findUserByUsername (string username) {
  for (int i = 0 ; i < (int) user_name.size() ; ++i) {
    if (user_name[i] == username) {
      return i;
    }
  }
  return -1;
}

void sendNotification (int cur_user_ind,
                       string userMessage,
                       string roomMessage) {
  for (int i = 0 ; i < (int) user_name.size() ; ++i) {
    if (user_client_id[i] != user_client_id[cur_user_ind]) continue;

    if (user_room[i] == user_room[cur_user_ind]) {
      send(user_client_id[i], roomMessage.c_str(), roomMessage.length(), 0);
    }
  }
  send(user_client_id[cur_user_ind], userMessage.c_str(), userMessage.length(), 0);
}

int changeUserRoom(int client, int newRoom) {
  for (int i = 0 ; i < (int) user_room.size() ; ++i) {
    if (user_client_id[i] == client) {
      user_room[i] = newRoom;
      return i;
    }
  }
  return -1;
}




void sendUserList(int cur_user_ind) {
  string ret = "";
  for (int i = 0 ; i < (int) user_room.size() ; ++i) {
    if (user_room[i] == user_room[cur_user_ind]) {
      ret +=
            "#" + to_string(i + 1) + " "
            + user_name[i] + "\n";
    }
  }

  send(user_client_id[cur_user_ind],
       ret.c_str(), ret.length(), 0);
}

void sendMessageTo(vector<string> messagedUsers,
                   string msg,
                   int cur_user_ind,
                   bool all) {
  vector< string > wrong_names;

  msg = user_name[cur_user_ind] + ": " + msg;
  vector<bool> checked(messagedUsers.size(), false);

  for (int i = 0 ; i < (int)user_room.size() ; ++i)
  {
    if (i == cur_user_ind || user_room[cur_user_ind] != user_room[i])
      continue;
    if(all)
      send(user_client_id[i], msg.c_str(), msg.length(), 0);

    for (int j = 0 ; j < (int) messagedUsers.size() ; ++j) {
      if (messagedUsers[j] == user_name[cur_user_ind]) {
        checked[j] = true;
        send(user_client_id[i], msg.c_str(), msg.length(), 0);
      }
    }
  }

  bool at_least_one = false;
  string wrong_user_msg = "There is no such a user: ";
  for (size_t i = 0; i < messagedUsers.size(); i ++) {
    if (checked[i] == false) {
      wrong_user_msg += messagedUsers[i] + " ";
      at_least_one = true;
    }
  }

  if (at_least_one)
    send(user_client_id[cur_user_ind],
        wrong_user_msg.c_str(),
        wrong_user_msg.length(), 0);
}

void *listenToClient (void* client_p) {
  int cur_client_id = (long) client_p;
  char *buffer = new char[BUFF_SIZE];

  do
  {
      cout << "client = " << cur_client_id << "\n";
      memset(buffer, 0, BUFF_SIZE);
      int nread = recv(cur_client_id, buffer, BUFF_SIZE, 0);
      if (nread <= 0) {
        int client_ind = findUserByID(cur_client_id);
        string userMessage = DEFAULT_QUIT_MSG + " " + user_name[client_ind] + "\n";
        string roomMessage = user_name[client_ind] + " is leaving\n";
        sendNotification(client_ind, userMessage, roomMessage);
        break;
      }

      string requestFromClient = (string) buffer;
      vector <string> list = trim(Split(requestFromClient, " "));

      if (list[0].find("/connect") != string::npos) {
        string username = list[1];
        int room = stoi(list[2]);

        int id = 1;
        do {
          if (findUserByUsername(username) == -1)
            break;
          username = list[1] + "-" + to_string(++ id);
        } while(true);

        int client_ind = addNewUser(cur_client_id, room, username);
        string userMessage =  "Welcome, " + user_name[client_ind] + " to room #" + to_string(room) + "\n";
        string roomMessage = user_name[client_ind] + " is connected to this room\n";
        sendNotification(client_ind, userMessage, roomMessage);
      } else if (list[0].find("/list") != string::npos) {
        sendUserList(findUserByID(cur_client_id));
      } else if (list[0].find("/quit") != string::npos) {
        int client_ind = findUserByID(cur_client_id);
        string userMessage = DEFAULT_QUIT_MSG + " " + user_name[client_ind] + "\n";
        string roomMessage = user_name[client_ind] + " is leaving\n";
        sendNotification(client_ind, userMessage, roomMessage);
        break;
      } else if (list[0].find("/join") != string::npos) {
        int newRoom = stoi(list[1]);
        int client_ind = changeUserRoom(cur_client_id, newRoom);
        string userMessage = "New user joined: " + user_name[client_ind] + "\n";
        string roomMessage = user_name[client_ind] + " is leaving\n";
        sendNotification(client_ind, userMessage, roomMessage);
      } else {
        int user_ind = findUserByID(cur_client_id);
        vector<string> parsedInput = Split(requestFromClient, ":");
        vector<string> messagedUsers = trim(Split(parsedInput[0], ","));
        string Msg = parsedInput[1];
        if (messagedUsers.size() > 1)
          sendMessageTo(messagedUsers, Msg, user_ind, false);
        else if (messagedUsers.size() == 1
                 && messagedUsers[0] == "All")
          sendMessageTo(messagedUsers, Msg, user_ind, true);
      }
  } while (true);

  close(cur_client_id);
  delete [] buffer;
  return NULL;
}

int
main(int argc, char **argv)
{
    struct sockaddr_in server_addr,client_addr;
    socklen_t clientlen = sizeof(client_addr);
    int port, reuse = 1;
    int server, client;

    port = 3000;

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (!(server = socket(PF_INET,SOCK_STREAM,0))) {
      cout << "Socket create\n";
      return 0;
    }

    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
      cout << "Socket opt\n";
      return 0;
    }

    if (bind(server,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
      cout << "Bind problem\n";
      return 0;
    }

    if (listen(server,SOMAXCONN) < 0) {
      cout << "listening problem";
      return 0;
    }

    int num = 0;

    while ((client = accept(server,(struct sockaddr *)&client_addr,&clientlen)) > 0)
    {
      int res = pthread_create
                      (&my_threads[num ++],
                       NULL,
                       listenToClient,
                       (void *) client);
      if (res) {
        cout << "Can't create thread for " << client << "\n";
      }
    }

    close(server);
}

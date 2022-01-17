#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>
#include "auxiliar.hpp"

class MessageException : public std::exception {
   std::string message;
public:
    MessageException(const std::string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Message {
    int id;
    std::string username;
    std::string msg;
    std::vector<std::string> likes;
public:
    Message(int id, const std::string& username, const std::string& msg) : id(id), username(username), msg(msg) {}
    int getId() const {
        return id;
    }
    void like(const std::string& username) {
        likes.push_back(username);
    }
    friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
        os << "[";
        for (size_t i = 0; i < msg.likes.size(); i++) {
            if (i != msg.likes.size() - 1) {
                os << msg.likes[i] << ",";
            } else {
                os << msg.likes[i];
            }
        }
        os << "]";
        return os;
    }
};

class Inbox {
    std::map<int, Message*> unread;
    std::map<int, Message*> allMsgs;
public:
    Inbox();
    std::vector<Message*> getUnread() {
        for (int i = 0; i < unread.size(); i++) {
            std::cout << unread[i];
        }
        unread.clear();
    }
    std::vector<Message*> getAll() const {

    }
    Message* getTweet(int id) {
        auto key = allMsgs.find(id);

        if (key != allMsgs.end()) {
            return allMsgs[id];
        }
    }
    friend std::ostream& operator<<(std::ostream& os, Inbox& inbox) {
        for (int i = 0; i < inbox.allMsgs.size(); i++) {
            os << "(" << inbox.allMsgs[i] << ")" << std::endl;
        }
        return os;
    }
    void storeUnread(Message* tweet);
    void storeReaded(Message* tweet);
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
public:
    void sendTweet(Message * msg);
    User(const std::string& username) : username(username) {}
    void follow(User * other);
    void unfollow(std::string username);
    void like(int twId);
    Inbox& getInbox();
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

class Controller {
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Message>> tweets;
    int nextTweetId { 0 };
    //create, stores and returns a new tweet object
    Message* createMsg(std::string username, std::string msg);
public:
    Controller();
    void addUser(std::string username);
    User* getUser(std::string username);
    void sendTweet(std::string username, std::string msg);
    friend std::ostream& operator<<(std::ostream& os, const Controller& ctrl);
};
std::ostream& operator<<(std::ostream& os, const Controller& ctrl) {
    os << aux::join(ctrl.users, "\n", aux::fn_map_values_ptr);
    return os;
}

std::vector<std::string> getcmd() {
    std::string line;
    std::getline(std::cin, line);
    std::cout << "$" << line << "\n";
    return aux::split(line, ' ');
}

int main(){
    Controller sistema;

    while(true) {
        auto param = getcmd();
        auto cmd = param[0];
        try {
            if (cmd == "end") {
                break;
            } else if (cmd == "add") {
                sistema.addUser(param[1]);
            } else if (cmd == "show") {
                std::cout << sistema << '\n';
            } else if (cmd == "follow") {
                sistema.getUser(param[1])->follow(sistema.getUser(param[2]));
            } else if (cmd == "unfollow") {
                sistema.getUser(param[1])->unfollow(param[2]);
            } else if (cmd == "twittar") {
                auto msg = aux::slice(param, 2);
                sistema.sendTweet(param[1], aux::join(msg, " "));
            } else if (cmd == "like") {
                sistema.getUser(param[1])->like(std::stoi(param[2]));
            } else if (cmd == "unread") {
                auto msgs = sistema.getUser(param[1])->getInbox().getUnread();
                std::cout << aux::join_ptr(msgs, "\n") << '\n';
            } else if (cmd == "timeline") {
                auto msgs = sistema.getUser(param[1])->getInbox().getAll();
                std::cout << aux::join_ptr(msgs, "\n") << '\n';
            } else {
                std::cout << "fail: comando invalido" << '\n';
            }
        } catch (MessageException &e) {
            std::cout << e.what() << '\n';
        }
    }
    return 0;
}
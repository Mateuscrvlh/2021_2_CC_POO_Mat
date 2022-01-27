#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <list>

class Tweet {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;
    Tweet *rt {nullptr};
public:
    Tweet(int id, const std::string& username, const std::string& msg) : id{id}, username{username}, msg{msg} {}

    int getId() const {
        return id;
    }
    std::string getSender() const {
        return username;
    }
    std::string getMsg() const {
        return msg;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tweet& msg) {
        int cont = 0;
        os << msg.id << ":" << msg.username << " (" << msg.msg << ") [";
        for(auto it : msg.likes) {
            cont++;
            os << it;
            if (cont != (int) msg.likes.size()) {
                os << ",";
            }
        }
        os << "]\n";
        if(msg.rt != nullptr) {
            os << "    " << *msg.rt;
        }
        return os;
    }

    void like(const std::string& username) {
        this->likes.insert(username);
    }
    std::set<std::string> getLikes() const {
        std::set<std::string> aux;
        for(auto it : likes) {
            aux.insert(it);
        }
        return aux;
    }

    void setRt(Tweet *rtt) {
        this->rt = rtt;
    }

    bool deleted {false};

    void setDeleted() {
        deleted = true;
        this->msg = "esse tweet foi deletado";
        this->username = "";
        this->likes.clear();
    }

    bool isDeleted() const {
        return deleted;
    }
};

class Inbox {
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;
public:
    Inbox() {}
    void storeInTimeline(Tweet* tweet) {
        this->timeline[tweet->getId()] = tweet;
    }
    std::vector<Tweet*> getTimeline() const {
        std::vector<Tweet*> aux;
        for (auto it : timeline) {
            aux.push_back(it.second);
        }
        return aux;
    }

    friend std::ostream& operator<<(std::ostream& os, const Inbox& inbox) {
        auto key = inbox.getTimeline();
        for(int i = (int) (key.size() - 1); i >= 0;i--) {
            if(key[i]->isDeleted() == false) {
                os << *key[i];
            }
        }
        return os;
    }

    Tweet* getTweet(int id) {
        for (auto it : timeline) {
            if(it.first == id) {
                return it.second;
            } else {
                throw std::runtime_error("Esse tweet nao existe");
            }
        }
    }

    void rmMsgsFrom(const std::string& username) {
        for(auto i = timeline.begin(); i != timeline.end();) {
            if (i->second->getSender() == username) {
                i = this->timeline.erase(i);
            } else {
                i++;
            }
        }
    }

    void storeInMyTweets(Tweet* tweet) {
        this->myTweets[tweet->getId()] = tweet;
    }

    std::vector<Tweet*> getMyTweets() const {
        std::vector<Tweet*> aux;
        for (auto it : myTweets) {
            aux.push_back(it.second);
        }
        return aux;
    }
};

class User {
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
public:
    User(const std::string& username) : username{username} {}
    friend std::ostream& operator<<(std::ostream& os, const User& user);

    void follow(User * other) {
        if (this->username != other->username) {
            //auto key = following.find(other->username);
            //if (key != following.end()) {
                this->following[other->username] = other;
                other->followers[this->username] = this;
            //} else {
            //    throw std::runtime_error("Esse usuario nao existe");
            //}
        }
    }
    Inbox& getInbox() {
        return inbox;
    }
    void sendTweet(Tweet * msg) {
        this->inbox.storeInTimeline(msg);
        this->inbox.storeInMyTweets(msg);

        for (auto it : followers) {
            it.second->inbox.storeInTimeline(msg);
        }
    }

    void unfollow(std::string username) {
        auto key = this->following.find(username);
        if (key != following.end()) {
            following.erase(key);
            this->inbox.rmMsgsFrom(username);
            key->second->followers.erase(this->username);
        } else {
            throw std::runtime_error("Voce nao segue esse usuario");
        }
    }

    void like(int twId) {
        this->getInbox().getTweet(twId)->like(this->username);
    }

    void unfollowAll() {
        int cont = 0;
        for(auto it = following.begin(); cont < following.size();) {
            std::cout << it->first << std::endl;
            this->unfollow(it->first);
            cont++;
        }
    }

    void rejectAll() {
        for (auto it : followers) {
            it.second->unfollow(this->username);
        }
    }
};
std::ostream& operator<<(std::ostream& os, const User& user) {
    int cont = 0;
    os << user.username << "\n" << "  seguidos   ";
    os << "[";
    for (auto it : user.following) {
        cont++;
        os << it.first;
        if (cont != (int) user.following.size()) {
            os << ",";
        }
    }
    os << "]\n  seguidores [";
    for (auto it : user.followers) {
        cont = 0;
        cont++;
        os << it.first;
        if (cont != (int) user.followers.size()) {
            os << ",";
        }
    }
    os << "]" << std::endl;
    return os;
}

class Controller {
    int nextTweetId { 0 };
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Tweet>> tweets;
public:
    Controller() {}
    void addUser(std::string username) {
        auto key = users.find(username);
        if (key != users.end()) {
            throw std::runtime_error("Ja existe conta com esse nome\n");
        } else {
            this->users[username] = std::make_shared<User>(username); 
        }
    }
private:
    Tweet* createTweet(std::string username, std::string msg) {
        auto tweet = std::make_shared<Tweet>(nextTweetId, username, msg);
        this->tweets[nextTweetId] = tweet;
        nextTweetId++;
        return tweet.get();
    }
public:
    User* getUser(std::string username) {
        auto key = users.find(username);
        if (key != users.end()) {
            return this->users[username].get();
        } else {
            throw std::runtime_error("Esse tweet nao existe");
        }
    }
    
    void sendTweet(std::string username, std::string msg) {
        auto key = this->getUser(username);
        auto key2 = this->createTweet(username, msg);
        key->sendTweet(key2);
    }

    void sendRt(std::string username, int twId, std::string msg) {
        auto user1 = this->getUser(username); 
        auto rtTweet = this->createTweet(username, msg);
        rtTweet->setRt(user1->getInbox().getTweet(twId));
        user1->sendTweet(rtTweet);
    }

    void rmUser(std::string username) {
        auto user1 = this->getUser(username);
        user1->unfollowAll();
        user1->rejectAll();
        auto key = user1->getInbox().getMyTweets();
        for(auto it : key) {
            it->setDeleted();
        }
        for(auto it : users) {
            if(it.first == username) {
                this->users.erase(it.first);
                break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Controller& ctrl);
};
std::ostream& operator<<(std::ostream& os, const Controller& ctrl) {
    for (auto it : ctrl.users) {
        os << *it.second;
    }
    return os;
}

int main() {
    Controller sistema;

    while(true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        try {
            if (cmd == "end") {
                break;
            } else if (cmd == "addUser") {
                std::string username;
                ss >> username;
                sistema.addUser(username);
            } else if (cmd == "follow") {
                std::string username;
                std::string other;
                ss >> username >> other;
                sistema.getUser(username)->follow(sistema.getUser(other));
            } else if (cmd == "show") {
                std::cout << sistema;
            } else if (cmd == "twittar") {
                std::string username;
                std::string msg;
                ss >> username;
                std::getline(std::cin,msg);
                sistema.sendTweet(username, msg);
            } else if (cmd == "timeline") {
                std::string username;
                ss >> username;
                auto key = sistema.getUser(username)->getInbox();
                std::cout << key << std::endl;
            } else if (cmd == "like") {
                std::string username;
                int twId;
                ss >> username >> twId;
                sistema.getUser(username)->like(twId);
            } else if (cmd == "unfollow") {
                std::string username;
                std::string other;
                ss >> username >> other;
                sistema.getUser(username)->unfollow(other);
            } else if (cmd == "rt") {
                std::string username;
                std::string msg;
                int twId;
                ss >> username >> twId;
                std::getline(std::cin,msg);
                sistema.sendRt(username,twId,msg);
            } else if (cmd == "rm") {
                std::string username;
                ss >> username;
                sistema.rmUser(username);
            } else {
                std::cout << "fail: comando invalido" << std::endl;
            }
        } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
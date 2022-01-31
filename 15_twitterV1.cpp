#include <iostream>
#include <map>

class User {
    std::string username;
    std::map<std::string, User*> following;
    std::map<std::string, User*> followers;
public:
    User(std::string username) : username(username) {};

    std::string getUserame() {
        return username;
    }

    void follow(User* other){
        this->following[other->username] = other;
        other->followers[this->username] = this;
    }

    void unfollow(User* other){
        this->following.erase(other->username);
        other->followers.erase(this->username);
    }

    friend std::ostream &operator<<(std::ostream& os, User& u) {
        int cont = 0;
        os << u.username << "\n" << "seguidos: [";
        for (auto it : u.following) {
            cont++;
            os << it.first;
            if (cont != u.following.size()) {
                os << ",";
            }
        }
        os << "]\n";
        os <<"seguidores: [";
        for (auto it : u.followers) {
            os << it.first;
            if (cont < u.followers.size()) {
                os << ",";
            }
        }
        os << "]";
        return os;
    }
};

int main () {
    User* user0 = new User("Mateus");
    User* user1 = new User("Rafael");
    User* user2 = new User("Vania");

    user0->follow(user1);
    user1->follow(user0);
    user0->follow(user2);

    std::cout << *user0;
}
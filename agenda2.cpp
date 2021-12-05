#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>

class Fone {
    std::string id;
    std::string number;
public:
    Fone(std::string id = "", std::string number = "") : id(id), number(number) {}

    bool validate(std::string number){
        for(int i = 0; i < (int)number.size(); i++){
            if(number[i] >= '0' || number[i] <= '9' || number[i] == '.' || number[i] == '(' || number[i] == ')'){
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fone& f) {
        os << "" << f.id << ":" << f.number << "]";
        return os;
    }

    std::string getId() {
        return this->id;
    }

    std::string getNumber() {
        return this->number;
    }
};

class Contact {
    std::vector<Fone> fones;
    std::string name;
public:
    Contact(std::string name) : name(name) {}

    void addFone(Fone fone) {
        fones.push_back(fone);
        std::cout << "O telefone foi adicionado" << std::endl;
    }

    void rmFone (int index) {
        for (int i = 0; i < (int) this->fones.size(); i++) {
            if(i == index) {
                this->fones.erase(this->fones.begin() + i);
                return;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Contact& c) {
        os << "-" << c.name << " ";
        for(int i = 0; i < (int) c.fones.size(); i++) {
            os << "[" << c.fones[i].getId() << ":" << c.fones[i].getNumber() << "] ";
        }
        return os;
    }

    std::vector<Fone> getFone(){
        return this->fones;
    }

    std::string getName(){
        return this->name;
    }
};

class Agenda {
    std::map<std::string, Contact> contacts;
public:
    Agenda() {}

    void rmContact(std::string name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            contacts.erase(it);
            std::cout << "Contato removido" << std::endl;
            return;
        }
        std::cout << "Contato nao existe" << std::endl;
    }

    void addContact(Contact c) {
        auto it = contacts.find(c.getName());
        if (it == contacts.end()) {
            contacts[c.getName()] = c;
        } else {
            for (Fone fone : c.getFone()) {
                it->second.addFone(fone);
            }
        }
    }

    std::vector<Contact> search(std::string pattern) {
        std::vector<Contact> aux;
        for (auto i : contacts) {
            std::stringstream ss;
            ss << i.second;
            auto texto = ss.str();
            if (texto.find(pattern) != std::string::npos) {
                aux.push_back(i.second);
            }
        }
        return aux;
    }

    friend std::ostream& operator<<(std::ostream& os, Agenda& a) {
        for (auto i : a.contacts) {
            os << i.first << i.second << std::endl;
        }
        return os;
    }
};

int main() {

    Agenda agenda;

    while (true) {
        std::string line{};
        std::getline(std::cin, line);
        std::stringstream ss(line);

        std::string cmd{};
        ss >> cmd;

        if (cmd == "add") {
            std::string name, id, number;
            std::vector<Fone> aux;
            ss >> name;
            Contact contato(name);
            ss << id << number;
            Fone f(id, number);
            contato.addFone(f);
            agenda.addContact(contato);
        }
        else if (cmd == "show") {
            std::cout << agenda << std::endl;
        }
        else if (cmd == "rmContact") {
            std::string name{};
            ss >> name;

            agenda.rmContact(name);
        }
        else if (cmd == "search") {
            std::string pattern{};
            ss >> pattern;

            std::vector<Contact> busca = agenda.search(pattern);
            if ((int)busca.size() == 0) {
                std::cout << "Nada foi encontrado :/\n";
            }
            else {
                for (auto &c : busca)
                {
                std::cout << c << std::endl;
                }
            std::cout << std::endl;
            }
        }
        else if (cmd == "end") {
            break;
        }
        else {
            std::cout << "[ERROR!] Comando invalido.\n";
        }
    }
  return 0;
}
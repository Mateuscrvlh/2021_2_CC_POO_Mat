#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

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

class Agenda{
    std::vector<Contact> contacts;

    int findPos(std::string nome) {
        for (int i = 0 ; i < contacts.size(); i++) {
            if(contacts[i].getName() == nome) {
                return i;
            }
        }
        return -1;
    }

public:
    Agenda() {}

    Contact* getContact(std::string name) {
        int index = findPos(name);
        if (index != -1) {
            return &contacts[index];
        }
        return nullptr;
    }

    void addContact(Contact contact) {
        this->contacts.push_back(contact);
        std::sort(contacts.begin(), contacts.end(), [](Contact contato1, Contact contato2) {
            if(contato1.getName() != contato2.getName()) {
                return contato1.getName() < contato2.getName();
            }
        });
    }

    void rmContact(std::string name) {
        int index = findPos(name);
        if (index != -1) {
            this->contacts.erase(this->contacts.begin() + index);
        }
    }

    std::vector<Contact> search(std::string pattern) {
        std::vector<Contact> result;
        for (auto& c : this->contacts) {
            std::stringstream ss;
            ss << c;
            std::string texto = ss.str();
            if (texto.find(pattern) != std::string::npos) {
                result.push_back(c);
            }
        }
        return result;
    }

    std::vector<Contact> getContact() {
        return this->contacts;
    }

    friend std::ostream& operator<<(std::ostream& os, Agenda& a) {
        for(int i = 0; i < (int) a.contacts.size(); i++) {
            os << a.contacts[i] << std::endl;
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
      std::string name, id, number, aux;
      ss >> name;

      Contact contato(name);
      while (ss >> aux) {
        for (int i{0}; i < (int)aux.length(); i++) {
          if (aux[i] == ':') {
            aux[i] = ' ';
          }
        }
        std::stringstream s2(aux);
        s2 >> id >> number;
        contato.addFone(Fone(id, number));
      }
      agenda.addContact(contato);
    }
    else if (cmd == "show") {
      std::cout << agenda << std::endl;
    }
    else if (cmd == "rmFone") {
      std::string name{};
      int indice{};
      ss >> name >> indice;

      Contact *contato = agenda.getContact(name);
      if (contato != nullptr) {
        contato->rmFone(indice);
      }
      else {
        std::cout << "[ERROR!] Contato nao encontrado.\n";
      }
    }
    else if (cmd == "rm") {
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
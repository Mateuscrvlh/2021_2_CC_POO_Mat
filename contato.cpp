#include <iostream>
#include <list>
#include <memory>
#include <vector>

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
        os << f.id << ":" << f.number << "]";
        return os;
    }

    std::string getId() {
        return this->id;
    }

    std::string getNumber() {
        return this->number;
    }
};

class Contato {
    std::string nome;
    std::list<Fone> fones;
public:
    Contato(std::string nome = "") : nome(nome) {} 

    void addFone(Fone fone) {
        fones.push_back(fone);
        std::cout << "fone adicionado com sucesso\n";
    }

    void rmFone(int cont = -1) {
        int cont2 = 0;
        for(auto it = fones.begin(); it != fones.end(); it++){
            if(cont2 == cont){
                fones.erase(it);
                std::cout << "fone removido\n";
                break;
            }
            cont2++;
        }

    }

    friend std::ostream& operator<<(std::ostream& os, const Contato& c) {
        int cont = 0;
        os << "- ";
        os << c.nome << " ";
        for(auto it = c.fones.begin(); it != c.fones.end(); it++) {
            std::cout << "[" << cont << ":" << *it;
            cont++;
        }
        os << "\n";
        return os;
    }

    std::string getNome(){
        return this->nome;
    }

    std::list<Fone> getFones(){
        return this->fones;
    }
};

int main(){
    Contato fone("Mateus");
    Fone telefone1("casa", "(85)987654321");
    if(telefone1.validate("(85)987654321")){
        fone.addFone(telefone1);
    }
    Fone telefone2("oi", "(85)987654322");
    if(telefone1.validate("(85)987654322")){
        fone.addFone(telefone2);
    }
    std::cout << fone;
    fone.rmFone(1);
    std::cout << fone;
}
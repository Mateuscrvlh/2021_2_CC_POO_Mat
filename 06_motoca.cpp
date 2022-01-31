#include <iostream>
#include <sstream>
#include <vector>

struct Pessoa {
    std::string nome;
    int idade;

    Pessoa(std::string nome = "", int idade = 0) {
        this->nome = nome;
        this->idade = idade;
    }

    Pessoa(int idade) : Pessoa("", idade) {
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
        os << "Nome: " << p.nome << " Idade: " << p.idade;
        return os;
    }
};


struct Motoca {
    Pessoa* pessoa {nullptr};
    int tempo {0};
    int potencia {1};
    Motoca(int pot): potencia {pot} {
    }


    bool inserirPessoa(Pessoa* p) {
        if (this->pessoa != nullptr) {
            std::cout << "Motoca cheia" << std::endl;
            return false;
        }
        this->pessoa = p;
        return true;
    }

    std::string grau() {
        return "Rand" + std::string(this->potencia, 'a') + 'n';
    }

    Pessoa * removerPessoa() {
        Pessoa * p = this->pessoa;
        this->pessoa = nullptr;
        return p;
    }

    void comprarTempo(int tempo) {
        this->tempo += tempo;
    }

    bool dirigir(int tempo) {
        if (this->pessoa == nullptr) {
            std::cout << "nao tem gente pra dirigir" << std::endl;
            return false;
        }
        if (tempo > this->tempo) {
            std::cout << "só conseguiu dirigir " << this->tempo << " minutos" << std::endl;
            this->tempo = 0;
            return true;
        }
        std::cout << "conseguiu dirigir " << this->tempo << " minutos" << std::endl;
        this->tempo -= tempo;
    }

    friend std::ostream& operator<<(std::ostream& os, const Motoca& m) {
        os << "T: " << m.tempo << " P: " << m.potencia;
        os << "[" << (m.pessoa == nullptr ? "vazio" : m.pessoa->nome) << "]";
        return os;
    }
};

int main() {
    Motoca motoca(1);
    while (true) {
        std::string line;
        std::string cmd;
        std::stringstream ss(line);

        std::cin >> cmd;

        std::getline(std::cin, line);
        
        ss << line;
        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int pot = 0;
            ss >> pot;
            motoca = Motoca(pot);
        } else if (cmd == "show") {
            std::cout << motoca << std::endl;
        } else if (cmd == "inserir") {
            std::string nome {};
            int idade {};
            ss >> nome >> idade;
            Pessoa* pessoa = new Pessoa(nome, idade);
            if(!motoca.inserirPessoa(pessoa))
                delete pessoa;
        } else if (cmd == "retirar") {
            Pessoa* pessoa = motoca.removerPessoa();
            if (pessoa != nullptr) {
                delete pessoa;
            }
        } else if (cmd == "grau") {
            std::cout << motoca.grau();
        } else {
            std::cout << "Comando nao existe" << std::endl;
        }
    }
}
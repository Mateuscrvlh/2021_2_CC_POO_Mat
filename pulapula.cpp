#include <iostream>
#include <list>
#include <memory>
#include <vector>

using namespace std;

class Kid{
public:
    int idade;
    string nome;

    Kid(int idade = 0, std::string nome = "") : idade(idade), nome(nome) {}

    friend ostream& operator<<(ostream& os, const Kid& k) {
        os << "Nome: " << k.nome << " Idade: " << k.idade << endl;
        return os;
    }
};

class Trampoline{
private:
    list<shared_ptr <Kid>> brincando;
    list<shared_ptr <Kid>> esperando;
public:
    Trampoline(int tam_fila) : esperando(tam_fila, nullptr) {}

    void chegar(const shared_ptr<Kid>& kid){
        this->esperando.push_front(kid);
    }

    bool entrar() {
        this->brincando.push_front(*this->esperando.begin());
        esperando.pop_front();
        cout << "Crianca entrou\n";
        return true;
    }

    bool sair(){
       this->esperando.push_front(*this->brincando.begin());
        brincando.pop_front();
        cout << "Crianca saiu\n";
        return true;
    }

    bool papai_chegou(const shared_ptr<Kid>& kid) {
        for (auto it = esperando.begin(); it != esperando.end(); it++){
            if(it->get()->nome == kid->nome){
                esperando.remove(*it);
                cout << "pai achou a crianca\n";
                return true;
            }
        }
        for (auto it = brincando.begin(); it != brincando.end(); it++){
            if(it->get()->nome == kid->nome){
                brincando.remove(*it);
                cout << "pai achou a crianca\n";
                return true;
            }
        }
        cout << "pai achou a nao crianca";
        return false;
    }

    friend ostream& operator<<(ostream& os, const Trampoline& t) {
        os << "Brincando: \n";
        for(auto brincando: t.brincando){
            if(brincando != nullptr){
                os << *brincando;
            }
        }
        os << "\n";
        os << "Esperando: \n";
        for(auto esperando: t.esperando){
            if(esperando != nullptr){
                os << *esperando;
            }
        }
        os << "\n";

        return os;
    }

};

int main(){
    Trampoline tramp(5);
    tramp.chegar(make_shared<Kid>(12, "Joao"));
    tramp.chegar(make_shared<Kid>(12, "Maria"));
    cout << tramp;

    tramp.entrar();
    tramp.entrar();
    cout << tramp;

    tramp.sair();
    cout << tramp;

    tramp.papai_chegou(make_shared<Kid>(12, "Joao"));
    cout << tramp;
}
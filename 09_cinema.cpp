#include <iostream>
#include <list>
#include <memory>
#include <vector>

using namespace std;

class Cliente{
public:
    string id;
    int fone;

    Cliente(string id = "", int fone = 0) : id(id), fone(fone) {}

    friend ostream& operator<<(ostream& os, const Cliente& c){
        os << c.id << ":" << c.fone;
        return os;
    }
};

class Cinema{
private:
    vector<shared_ptr <Cliente>> cadeiras;
public:
    Cinema(int qtd_cad) : cadeiras(qtd_cad, nullptr) {}

    bool reserva(const shared_ptr<Cliente>& cliente, int num_cad){
        for(size_t i = 0; i < cadeiras.size(); i++) {
            if(this->cadeiras[i] != nullptr && this->cadeiras[i]->id == cliente->id){
                cout << "so eh permitida uma reserva por pessoa neste estabelecimento" << endl;
                return false;
            }
        }
        if(this->cadeiras[num_cad] != nullptr){
            cout << "cadeira em uso" << endl;
            return false;
        }
        if(this->cadeiras[num_cad] == nullptr){
            this->cadeiras[num_cad] = cliente;
            cout << "reserva feita com sucesso" << endl;
            return true;
        }
        return false;
    }

    bool cancelar(const shared_ptr<Cliente>& cliente){
        for(size_t i = 0; i < cadeiras.size(); i++){
            if (this->cadeiras[i] != nullptr && this->cadeiras[i]->id == cliente->id){
                cadeiras[i] = nullptr;
                cout << "reserva cancelada com sucesso" << endl;
                return true;
            }
        }
        cout << "Ninguem com esse id tinha uma reserva" << endl;
        return false;
    }

    friend ostream& operator<<(ostream& os, const Cinema& c){
        os << "[ ";
        for(size_t i = 0; i < c.cadeiras.size(); i++){
            auto cadeiras = c.cadeiras[i];
            os << " ";
            if(cadeiras != nullptr){
                os << *cadeiras;
            } else {
                os << "-";
            }
            os << " ";
        }
        os << "]" << endl;
        return os;
    }
};

int main(){
    Cinema cinema(10);
    cout << cinema;

    cinema.reserva(make_shared<Cliente>("Joao", 1111), 7);
    cinema.reserva(make_shared<Cliente>("Joao", 1111), 1);
    cinema.reserva(make_shared<Cliente>("Maria", 2222), 6);
    cinema.reserva(make_shared<Cliente>("Cladinho", 3333), 6);
    cinema.reserva(make_shared<Cliente>("Manu", 4444), 4);
    cinema.reserva(make_shared<Cliente>("Teteu", 5555),5);
    cinema.reserva(make_shared<Cliente>("Rafael", 6666), 3);
    cinema.reserva(make_shared<Cliente>("Adam", 7777), 0);

    cout << cinema;

    cinema.cancelar(make_shared<Cliente>("Teteu", 5555));   

    cout << cinema; 
}
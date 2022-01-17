#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <stdexcept>

class Account {
protected: 
    int id;
    float balance {0.00};
    std::string clientId;
    std::string type{""}; //CC or CP
public:
    Account(int id = 0, std::string clientId ="") : id{id}, clientId{clientId} {};

    //abstract method
    virtual void monthlyUpdate() {}

    //saque
    void withdraw(float value) {
        if (value < balance) {
            throw std::runtime_error("Saldo insuficiente");
        } else {
            balance -= value;
        }
    };

    //deposito
    void deposit(float value) {
        balance += value;
    };

    //transferencia para outra conta
    void transfer(Account other, float value) {
        if(balance < value) {
            throw std::runtime_error("Saldo insuficiente");
        } else if(value <= 0) {
            throw std::runtime_error("Valor invalido");
        }
        other.balance += value;
        this->balance -= value;
    };

    friend std::ostream& operator<<(std::ostream& os, const Account& a) {
        os << a.id << ":" << a.clientId << ":" << a.balance << ":" << a.type;
        return os;
    }

    //GETS and SETS
    int getId() {
        return id;
    }

    float getBalance() const {
        return balance;
    }

    std::string getClientId() const{
        return clientId;
    }

    std::string getType() const{
        return type;
    }
};

class CheckingAccount : public Account {
public:
    //inicializa conta.type com "CC"
    CheckingAccount(int id = 0, std::string idClient = "") : Account{id, idClient} {
        type = "CC";
    }

    //retira 20 do saldo
    void monthlyUpdate() {
        if(this->balance - 20 < 0){
            balance = 0;
            throw std::runtime_error("Conta bloqueada");
        } else {
            balance -= 20;
        }
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int id, std::string idClient) : Account{id, idClient} {
        type = "CP";
    }

    //aumenta saldo em 1%
    void monthlyUpdate() {
        this->balance = this->balance + (balance * 0.01);
    }
};

class Client {
    std::vector<std::shared_ptr<Account>> accounts;
    std::string clientId;
    public:
    Client (std::string clientId = "", int id = 0): clientId{clientId} {
        this->addAccount( std::make_shared<CheckingAccount>( id, clientId ));
        this->addAccount( std::make_shared<SavingsAccount>( (id+1), clientId ));
    }

    //métodos
    void addAccount (std::shared_ptr<Account> account) {
        accounts.push_back(account);
    }

    friend std::ostream& operator<<(std::ostream& os, Client* client) {
        auto contas = client->getAccounts();
        os << client->clientId << " [" ;
        for (int i {0}; i < (int) contas.size(); i++) {
            if (i != (int) (contas.size() - 1))
                os << contas[i]->getId() << ", ";
            else 
                os << contas[i]->getId() << "]\n";
        }
        return os;
    }

    //gets e sets
    std::vector<std::shared_ptr<Account>> getAccounts () const {
        return accounts;
    }

    std::string getClient() const {
        return clientId;
    }

    void setAccount(std::vector<std::shared_ptr<Account>> accounts) {
        this->accounts = accounts;
    }

    void setClientId (std::string clientId) {
        this->clientId = clientId;
    }
};

class BankAgency {
private:
    std::map<int, std::shared_ptr<Account>> accounts;
    std::map<std::string, std::shared_ptr<Client>> clients;
    
    Account* getAccount(int id) {
        return this->accounts[id].get();
    }
    void existe (int conta) {
        if ((int) this->accounts.size() <= conta )
            throw std::runtime_error("conta nao encontrada");
    }
public: 
    BankAgency() {}

    void addClient (std::string clientId) {
        for (auto conta : clients) {
            if (conta.first == clientId)
                throw std::runtime_error("ja existe conta");
        }

        int size { (int) accounts.size()};

        auto client {std::make_shared<Client>(clientId, size)};
        clients.insert({clientId, client});
        
        auto contas = client->getAccounts();
        for (int i{0}; i < (int) contas.size(); i++) {
            accounts.insert({size, contas[i]});
            size++;
        }   
    }

    void deposit (int idConta, float value) {
        auto conta = getAccount(idConta);
        if ((int) this->accounts.size() <= idConta)
            throw std::runtime_error("conta nao encontrada");
        else
            conta->deposit(value);
    }

    void monthlyUpdate() {
        for (auto conta : accounts) {
            conta.second->monthlyUpdate();
        }
    }

    void transfer (int contaDe, int contaPara, float value) {
        existe(contaDe);
        existe(contaPara);
        auto conta = getAccount(contaDe);
        
        conta->transfer( *(this->accounts[contaPara]), value );
    }

    void withdraw(int idConta, float value) {
        existe(idConta);
        auto conta = getAccount(idConta);

        conta->withdraw(value);
    }
    
    friend std::ostream& operator<<(std::ostream& os, BankAgency& b) {
        int cont = 0;
        os << "Clients:\n";
        for (auto a : b.clients) {
            os << "- " << a.first << "[" << cont << (cont + 1) << "]\n";
            cont += 2;
        }
        os << "Accounts:\n";
        for (auto c : b.accounts) {
            os << c.second;
        }
        return os;
    }
};

int main () {
    BankAgency* banco = new BankAgency;
    while (true){
        std::string line, cmd;
        std::cin >> cmd;
        getline(std::cin, line);
        std::stringstream ss(line);

        try{
            if (cmd == "end")
                break;
            else if (cmd == "show")
                std::cout << banco;
            else if (cmd == "update")
                banco->monthlyUpdate();
            else if (cmd == "addCli") {
                std::string nome;
                ss >> nome;
                banco->addClient(nome);
            }
            else if (cmd == "saque") {
                int conta;
                float value;
                ss >> conta >> value;
                banco->withdraw(conta, value);
            }
            else if (cmd == "deposito") {
                int conta;
                float valor;
                ss >> conta >> valor;
                banco->deposit(conta, valor);
            }
            else if (cmd == "transf") {
                int envio, remetente;
                float value;
                ss >> envio >> remetente >> value;
                banco->transfer(envio, remetente, value);
            }
            else
                std::cout << "fail: comando invalido\n";
        } catch (std::runtime_error &e) {
            std::cout << "fail: " << e.what() << '\n';
        }
    }

    delete banco;

    return 0;
}
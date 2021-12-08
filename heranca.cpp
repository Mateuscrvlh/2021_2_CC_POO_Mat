#include <iostream>
#include <list>
#include <time.h>

class Junior {
    std::string name {" "};
    //se sabe programar o basico
    bool programs = false;
protected:
    std::string level {"Junior"};
public:
    Junior(std::string name) : name(name) { 
    }

    //khtp: knows how to program
    virtual bool khtp(bool resposta) {
        if (resposta == true) {
            programs = resposta;
            return true;
        } else {
            return false;
        }
    }

    virtual void doAProgram() {
        if (programs == true) {
            std::cout << "O Junior precisa da ajuda do Senior pra terminar o programa" << std::endl;
        } else {
            std::cout << "O Junior nao sabe nem pra onde vai" << std::endl;
        }
    }

    virtual void askSenior() {
        std::cout << "O Junior perguntou ao Senior como quebrava o loop de uma funcao" << std::endl;
    }

    virtual void answerDoubt() {
        std::cout << "O Junior nao sabe nem programar direito imagine tirar a duvida de alguem" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, Junior& j) {
        os << j.name << " eh um programador " << j.level;
        return os;
    }

    std::string getName(){
        return this->name;
    }

    bool getPrograms() {
        return this->programs;
    }
};

class Pleno : public Junior {
    //programa de forma avancada
    bool programsAdv = false;
protected:
    bool programs = true;
public:
    Pleno(std::string name) : Junior{name} {
        this->level = "Pleno";
    }

    virtual bool khtp(bool resposta) {
        if (resposta == true) {
            programsAdv = resposta;
            return true;
        } else {
            return false;
        }
    }

    virtual void doAProgram() {
        if (programsAdv == true) {
            std::cout << "O Pleno sabe a base e consegue completar o programa sem ajuda e rapidamente, mas nao sabe explicar" << std::endl;
        } else {
            std::cout << "O Pleno sabe a base e consegue completar o programa sem ajuda, mas lentamente" << std::endl;
        }
    }    

    virtual void askSenior() {
        std::cout << "O Pleno ta se achando e nao quer perguntar nada ao Senior" << std::endl;
    }

    virtual void answerDoubt() {
        std::cout << "O Pleno nao sabe responder perguntas, por isso nao eh Senior" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, Pleno& p) {
        Junior &junior = p;
        os << junior;
        return os;
    }

    bool getProgramsAdv() {
        return this->programsAdv;
    }
};

class Senior : public Pleno {
    std::list<Junior> programadores;
    bool explains = false;
protected:
    bool programs = true;
    bool programsAdv = true;
public:
    Senior(std::string name) : Pleno{name} {
        this->level = "Senior";
    }

    void listaDeProg(Junior junior) {
        programadores.push_back(junior);
    }

    //o time ta caro demais pra empresa, entao alguem sera cortado pela roda da demissao aleatoria
    void rodaDaDemissao(std::list<Junior> funcionarios) {
        int x = rand() % funcionarios.size();
        int cont = 0;
        for(auto it = funcionarios.begin(); it != funcionarios.end(); it++){
            if(cont == x){
                std::cout << *it << ", mas foi demitido";
                funcionarios.erase(it);
                break;
            }
            cont++;
        }
    }

    //knows how to explain
    virtual bool khte(bool resposta) {
        if (resposta == true) {
            explains = resposta;
            return true;
        } else {
            return false;
        }
    }

    virtual void doAProgram() {
        std::cout << "O Senior acha que ja passou dessa fase e repassa sua parte do programa pros Plenos e Junior" << std::endl;
    }    

    virtual void askSenior() {
        std::cout << "O Senior que responde as perguntas e nao faz elas" << std::endl;
    }

    virtual void answerDoubt() {
        if (explains == true) {
            std::cout << "O Senior tira todas as duvidas do Junior e as vezes do Pleno com maestria" << std::endl;
        } else {
            std::cout << "O Senior, entre varias aspas, na verdade eh filho do dono" << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Senior& s) {
        Pleno &pleno = s;
        os << pleno;
        return os;
    }

    bool getExplains() {
        return this->explains;
    }

    std::list<Junior> getProg(){
        return this->programadores;
    }
};

int main() {
    srand(time(NULL));

    Junior junior1 {"Pedro"};
    junior1.khtp(true);
    junior1.doAProgram();
    junior1.askSenior();
    junior1.answerDoubt();
    std::cout << junior1 << std::endl;

    Junior junior2 {"Isaac"};

    Pleno pleno1 {"Joao"};
    pleno1.khtp(true);
    pleno1.doAProgram();
    pleno1.askSenior();
    pleno1.answerDoubt();
    std::cout << pleno1 << std::endl;

    Pleno pleno2 {"Italo"};
    Junior &junior3 = pleno1;
    Junior &junior4 = pleno2;

    Senior senior {"Enzo"};
    senior.khte(false);
    senior.answerDoubt();
    senior.askSenior();
    senior.doAProgram();
    std::cout << senior << std::endl;

    senior.listaDeProg(junior1);
    senior.listaDeProg(junior2);
    senior.listaDeProg(junior3);
    senior.listaDeProg(junior4);
    
    senior.rodaDaDemissao(senior.getProg());
}
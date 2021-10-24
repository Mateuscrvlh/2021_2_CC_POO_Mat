#include <iostream>
#include <vector>

class Grafite{
    public: float calibre {0};
    public: std::string dureza {" "};
    public: int tamanho {0};

    public: Grafite(float calibre = 0.0, std::string dureza = "null", int tamanho = 0) :
        calibre {calibre}, dureza {dureza}, tamanho {tamanho} {
    }
    //funcao que eu nn sei oq eh
    //public: std::string toString(){
    //    return "Grafite" + this->calibre + this->dureza + this->tamanho;
    //};
    //funcao  que desgasta o grafite de acordo com 
    public: int desgastePorFolha() {
        if (dureza == "HB"){
            return 1;
        }
        if (dureza == "2B"){
            return 2;
        }
        if (dureza == "4B"){
            return 4;
        }
        if (dureza == "6B"){
            return 6;
        }   
        return 0;
    }
};

class Lapiseira {
    public: float calibre {0};
    public: Grafite grafite;

    public: Lapiseira(float calibre) :
        calibre {calibre} {
    }
    //funcao que eu nn sei oq eh
    //public: std::string toString();
    //funcao que insere o grafite de acordo com oq for chamado
    public: bool inserir(Grafite grafite) {
        if (this->grafite.dureza == "null") {
            if(this->calibre != grafite.calibre){
                std::cout << "Calibre imcompativel" << std::endl;
            } else {
                this->grafite = grafite;
            }
            return true;
        }
        return false;
    }
    //funcao que remove o grafite
    public: Grafite remover() {
        Grafite aux {this->grafite};
        this->grafite = *new Grafite();
        return aux;
    }
    //funcao que escreve e desgasta o grafite
    public: void write(int folhas) {
        int desgaste = this->grafite.desgastePorFolha();

        for (int i {0}; i != folhas; i++) {
            if(this->grafite.tamanho - desgaste > 0){
                this->grafite.tamanho -= desgaste;
            } else if(this->grafite.tamanho - desgaste <= 0){
                std::cout << "O grafite acabou" << std::endl;
                this->remover();
                break;
            }
        }
    }
};

int main(){
        Lapiseira lapiseira = *new Lapiseira(0.5f);
        //calibre: 0.5, grafite: null
        lapiseira.inserir(*new Grafite(0.7f, "2B", 50));
        //fail: calibre incompatível
        lapiseira.inserir(*new Grafite(0.5f, "2B", 50));
        //calibre: 0.5, grafite: [0.5:2B:50]

        //case inserindo e removendo
        lapiseira = *new Lapiseira(0.3f);
        lapiseira.inserir(*new Grafite(0.3f, "2B", 50));
        //calibre: 0.3, grafite: [0.3:2B:50]
        lapiseira.inserir(*new Grafite(0.3f, "4B", 70));
        //fail: ja existe grafite
        //calibre: 0.3, grafite: [0.3:2B:50]
        lapiseira.remover();
        lapiseira.inserir(*new Grafite(0.3f, "4B", 70));
        //calibre: 0.3, grafite: [0.3:4B:70]

        //case escrevendo 1
        lapiseira = *new Lapiseira(0.9f);
        lapiseira.inserir(*new Grafite(0.9f, "4B", 4));
        lapiseira.write(1);
        //warning: grafite acabou
        //calibre: 0.9, grafite: null
        lapiseira.inserir(*new Grafite(0.9f, "4B", 30));
        lapiseira.write(6);
        //calibre: 0.9, grafite: [0.9:4B:6]
        lapiseira.write(3);
        //fail: folhas escritas completas: 1
        //warning: grafite acabou
        //calibre: 0.9, grafite: null

        //case escrevendo 2
        lapiseira = *new Lapiseira(0.9f);
        lapiseira.inserir(*new Grafite(0.9f, "2B", 15));
        //calibre: 0.9, grafite: [0.9:2B:15]
        lapiseira.write(4);
        //calibre: 0.9, grafite: [0.9:2B:7]
        lapiseira.write(4);
        //fail: folhas escritas completas: 3
        //warning: grafite acabou
        //calibre: 0.9, grafite: null

}
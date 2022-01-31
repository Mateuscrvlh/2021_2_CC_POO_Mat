#include <iostream>
#include <vector>
#include <sstream>

class Grafite{
    public: float calibre {0};
    public: std::string dureza {" "};
    public: int tamanho {0};

    public: Grafite(float calibre = 0.0, std::string dureza = "null", int tamanho = 0) :
        calibre {calibre}, dureza {dureza}, tamanho {tamanho} {
    }

     friend std::ostream& operator<<(std::ostream& os, const Grafite& g) {
        os << "[" << g.calibre << ";" << g.dureza << ";" << g.tamanho << "]" << std::endl;
        return os;
    } 

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
    public: std::vector<Grafite> grafites;
    public: int capc_max {0};

    public: Lapiseira(float calibre) :
        calibre {calibre} {
    }

    friend std::ostream &operator<<(std::ostream &os, const Lapiseira *lapiseira)
    {
        os << "Calibre: " << lapiseira->calibre << std::endl;

        for ( int i { 0 }; i < (lapiseira->capc_max); i++) {
            if (lapiseira->grafites[i].dureza == "null") {
                os << "Grafite: " << lapiseira->grafites[i].dureza << "\n";
            } else {
                os << "Grafite: [" << lapiseira->grafites[i].calibre << ":" << lapiseira->grafites[i].dureza << ":" << lapiseira->grafites[i].tamanho << "]" << std::endl;
            }
        }
        return os;
    }

    public: bool inserir(Grafite& grafite) {
        for ( int i { 0 }; i < (this->capc_max); i++) {
            if (this->grafites[i].dureza == "null") {
                if ((float)this->calibre != grafite.calibre) {
                    std::cout << "calibre incompativel" << std::endl;
                } else {
                    this->grafites[i] = grafite;
                }
                return true;
            }
        }
        return false;
    }

    public: void remover(int qtd_a_remover) {
        std::vector<Grafite> aux;
        for ( int i { 0 }; i < qtd_a_remover; i++) 
                    this->grafites[i].dureza = "null";

        for (int i {0}; i < (this->capc_max) ; i++) {
            if (this->grafites[i].dureza != "null" )
                aux.push_back(this->grafites[i]);
        }
        
        for ( int i { 0 }; i < ((this->capc_max) - 1 - qtd_a_remover); i++) {
            aux.push_back( 0 );           
        }
        
        this->grafites = aux;
    }
    
    public: void write(int folhas) {
        int cont{0};
        for ( int i { 0 }; i < (this->capc_max); i++) {
            if (this->grafites[i].dureza != "null") {
                while (this->grafites[i].tamanho != 0 && folhas != 0){
                    int desgaste = this->grafites[i].desgastePorFolha();
                    if ((this->grafites[i].tamanho - desgaste) > 0) {
                        this->grafites[i].tamanho -= desgaste;
                        folhas--;
                        cont++;
                    } else if ((this->grafites[i].tamanho - desgaste) == 0) {
                        cont++;
                        this->grafites[i].tamanho -= desgaste;
                        folhas--;
                        this->remover(1);
                    } else{
                        this->remover(1);   
                    } 
                }
                if (folhas == 0){
                    std::cout << "folhas escritas completas: " << cont << std::endl;
                    std::cout << "grafite acabou" << std::endl;
                    break;
                }
            } else {
                std::cout << "folhas escritas completas: " << cont << std::endl;
                std::cout << "grafite acabou" << std::endl;
                break;
            }
        }
    }
};

int main()
{
    Lapiseira *lapiseira = new Lapiseira{0};

    while (true)
    {
        std::string cmd{""};
        std::string line{""};
        std::stringstream ss;

        std::cin >> cmd;

        getline(std::cin, line);

        ss << line;
        if (cmd == "init") {
            if (lapiseira->calibre == 0) {
            ss >> lapiseira->calibre;
            std::cout << "Quantos grafites a lapiseira suporta?\n";
            std::cin >> lapiseira->capc_max;
            for (int i {0}; i < (lapiseira->capc_max); i++)
                lapiseira->grafites.push_back(0);
            }
            else {
                std::cout << "lapiseira ja existe" << std::endl;
            }
        } else if (cmd == "show") {
            std::cout << (lapiseira);
        } else if (cmd == "inserir") {
            Grafite grafaux {};
            ss >> grafaux.calibre >> grafaux.dureza >> grafaux.tamanho;
            if (!(lapiseira->inserir(grafaux))) {
                std::cout << "lapiseira cheia" << std::endl;
            }
        } else if (cmd == "remover") {
            std::cout << "remover quantos grafites?" << std::endl;
            int aux {0};
            std::cin >> aux;
            if (aux > lapiseira->capc_max) {
                std::cout << "A capacidade maxima de grafites eh menor que a inserida" << std::endl;
            } else {
                lapiseira->remover(aux);
            }
        } else if (cmd == "write") {
            int aux {0};
            ss >> aux;
            lapiseira->write(aux);
        } else if (cmd == "end") {
            break;
        } else {
            std::cout << "comando invalido" << std::endl;
        }
    }
    return 0;
}
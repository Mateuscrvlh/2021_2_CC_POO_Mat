#include <iostream>
#include <vector>
#include <algorithm>

bool existe(int num_desej)
{
    std::vector<int> vet{-1, 97, 58, -17, 70};
    
    for (size_t i = 0; i < vet.size(); i++){
        if (vet[i] == num_desej){
            std::cout << "Numero existe: ";
            return true;
        }
    }
    std::cout << "Numero existe: ";
    return false;
}

void contar(int num_desej){
    int cont = 0;

    std::vector<int> vet{-1, 97, 58, -17, 70};
    
    for (size_t i = 0; i < vet.size(); i++){
        if (vet[i] == num_desej) cont++;
    }
    std::printf("O numero aparece %d vezes", cont);
}

int procurar_valor(int num_desej)
{
    std::vector<int> vet({-1, 97, 58, -17, 70});
    
    for (size_t i = 0; i < vet.size(); i++){
        if (vet[i] == num_desej){
            return i;
            break;
        }
    }
    std::printf ("Numero nao encontrado");
    return 0;
}

int procurar_valor_apos(int num_desej, int pos_ini)
{
    std::vector<int> vet({1, 1, 1, 1, 1});

    int cont = 0;
    
    for (size_t pos_ini; pos_ini < vet.size(); pos_ini++){
        if (vet[pos_ini] == num_desej) cont++;
    }
    return cont;
}

void procurar_menor(){
    std::vector<int> vet({-1, 97, 58, -17, 70});
    std::cout << "O valor minimo é: " << std::min({-1, 97, 58, -17, 70});
}

void procurar_maior(){
    std::vector<int> vet({-1, 97, 58, -17, 70});
    std::cout << "O valor maximo é: " << std::max({-1, 97, 58, -17, 70});
}

int procurar_menor_pos(){
    std::vector<int> vet({-1, 97, 58, -17, 70});

    for (size_t i; i < vet.size(); i++){
        if (vet[i] == std::min({-1, 97, 58, -17, 70})) return i;
    }
    return 0;
}

int procurar_menor_pos_apos(int pos_ini){
    std::vector<int> vet({-1, 97, 58, -17, 70});
    int menor = 0;

    for (int i = pos_ini; i < (int)vet.size(); i++){
        if (i == pos_ini){
            menor = vet[i];
        }
        if (menor > vet[i]) menor = vet[i];
    }
    return menor;
}

int procurar_melhor_se(){
    std::vector<int> vet({-1, 97, 58, -17, 70});
    int melhor = 0;

    for (size_t i = 0; i < vet.size(); i++){
        if (i == 0){
            melhor = vet[i];
        }
        if (melhor > vet[i] && vet[i] > 0) melhor = vet[i];
    }
    return melhor;
}

float calcular_stress_medio(){
    float soma = 0;
    float media;

    std::vector<int> vet({-1, 97, 58, -17, 70});

    for (size_t i = 0; i < vet.size(); i++){
        soma += abs(vet[i]);
    }
    media = soma / vet.size();
    return media;
}

void mais_homens_ou_mulheres(){
    int contador_m = 0;
    int contador_f = 0;

    std::vector<int> vet({-1, 97, 58, -17, 70});

    for (size_t i = 0; i < vet.size(); i++){
        if (vet[i] < 0) contador_f++;
        if (vet[i] > 0) contador_m++;
    }

    if(contador_f > contador_m) printf("A quantidade de mulheres eh maior");
    else printf("A quantidade de homens eh maior");
}

void qual_metade_eh_mais_estressada(){
    int soma1 = 0;
    int soma2 = 0;
    std::vector<int> vet({-1, 97, 58, 34, -17, 70});

    for (size_t i = 0; i < (vet.size())/2; i++){
        soma1 += abs(vet[i]);
    }

    for (size_t i = (vet.size())/2; i < (vet.size())/2; i++){
        soma2 += abs(vet[i]);
    }
    if (soma1 > soma2) printf("A primeira parte eh a mais estressada");
    else printf("A segunda parte eh a mais estressada");
}

void homens_sao_mais_estressados_que_mulheres(){
    int soma_f = 0;
    int soma_m = 0;
    std::vector<int> vet({-1, 97, 58, -17, 70});

    for (size_t i = 0; i < vet.size(); i++){
        if (vet[i] < 0) soma_f += abs(vet[i]);
        if (vet[i] > 0) soma_m += vet[i];
    }

    if (soma_m > soma_f) printf("Os homens sao mais estressados");
    else printf("As mulheres sao mais estressadas");
}

int main()
{
    int op = -1;
    int x = 0;
    int num_ini = 0;
    int num_desej = 0;

    std::cout << "O que deseja? 0- Sair\n 1-existe\n 2-contar\n 3-procurar_valor\n 4-procurar_valor_apos\n 5-procurar_menor\n 6-procurar_maior\n 7-procurar_menor_pos\n 8-procurar_menor_pos_apos\n 9-procurar_melhor_se\n 10-calcular_stress_medio 11-mais_homens_ou_mulheres\n 12-qual_metade_eh_mais_estressada\n 13- homens_sao_mais_estressados_que_mulheres\n" << "\n";
    std::cin >> op;

    while(op != 0){
        if (op == 0) break;
        if (op == 1){
            std::cout << "Digite o numero desejado: ";
            std::cin >> num_desej;
            std::cout << existe(x);
        }
        if (op == 2){
            std::cout << "Digite o numero desejado: ";
            std::cin >> num_desej;
            contar(x);
        }
        if (op == 3){
            std::cout << "Digite o numero desejado: ";
            std::cin >> num_desej;
            std::cout << procurar_valor(x);
        }
        if (op == 4){
            std::cout << "Digite o numero e a posicao desejados: ";
            std::cin >> num_desej;
            std::cin >> num_ini;
            std::cout << procurar_valor_apos(x, num_ini);
        }
        if (op == 5){
            procurar_menor();
        }
        if (op == 6){
            procurar_maior();
        }
        if (op == 7){
            std::cout << procurar_menor_pos();
        }
        if (op == 8){
            std::cout << "Digite a posicao desejada: ";
            std::cin >> num_ini;
            std::cout << procurar_menor_pos_apos(num_ini);
        }
        if (op == 9){
            std::cout << procurar_melhor_se();
        }
        if (op == 10){
            std::cout << calcular_stress_medio();
        }
        if (op == 11){
            mais_homens_ou_mulheres();
        }
        if (op == 12){
            qual_metade_eh_mais_estressada();
        }
        if (op == 13){
            homens_sao_mais_estressados_que_mulheres();
        }
    }
    
    return 0;
}
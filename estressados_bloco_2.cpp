#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<int> clonar(const std::vector<int>& v){
    std::vector<int> vet_dois;
    for ( size_t i { 0 }; i < v.size(); i++){
        vet_dois.push_back(v[i]);
    }
    return vet_dois;
}

std::vector<int> pegar_homens(const std::vector<int>& v){
    std::vector<int> vet_aux;
    for ( size_t i { 0 }; i < v.size(); i++){
        if ( v[i] > 0 ){
        vet_aux.push_back(v[i]);
        }
    }
    return vet_aux;
}

std::vector<int> pegar_calmos(const std::vector<int>& v){
    std::vector<int> vet_aux;
    for ( size_t i { 0 }; i < v.size(); i++){
        if ( abs(v[i]) < 10 ){
        vet_aux.push_back(v[i]);
        }
    }
    return vet_aux;
}

std::vector<int> pegar_mulheres_calmas(const std::vector<int>& v){
    std::vector<int> vet_aux;
    for ( size_t i { 0 }; i < v.size(); i++){
        if ( v[i] < 0 && abs(v[i]) < 10 ){
        vet_aux.push_back(v[i]);
        }
    }
    return vet_aux;
}

std::vector<int> inverter_com_copia(const std::vector<int>& v){
    std::vector<int> vet_aux;
    for ( size_t i { (v.size()) -1 }; i > 0; i--){
        vet_aux.push_back(v[i]);
    }
    return vet_aux;
}

void inverter_in_place(std::vector<int>& v){
    std::reverse( v.begin(), v.end() );
    
    for ( size_t i { 0 }; i < v.size(); i++){
        std::cout << v[i] << ' ';
    }
}

int sortear(const std::vector<int>& v){
    std::srand(std::time(0));
    int pos_rand { rand() % v.size() };
    int num_rand { v[pos_rand] };

    return num_rand;
}

void embaralhar(std::vector<int>& v){
    for ( size_t i { 0 }, f { (v.size()) - 1 }; i < v.size(); i++, f--){
        std::srand(std::time(0));
        int pos { rand() % v.size() };
        std::swap(v[i], v[pos]);
    }

    for ( size_t i { 0 }; i < v.size(); i++){
        std::cout << v[i] << ' ';
    }
}

void ordenar(std::vector<int>& v){
    int menor { 0 };
    int aux { 0 };

    for ( int i { 0 }; i < ((int) v.size()) - 1; i++ ){
        menor = i ;
        for ( int j { (i + 1) }; j < (int) v.size(); j++ ){
            if ( v[j] < v[menor] ) menor = j;
        }
        if ( i != menor ){
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }

    for ( int k { 0 }; k < (int) v.size(); k++){
        std::cout << v[k] << ' ';
    }
}

std::vector<int> exclusivos( const std::vector<int>& v ){
    std::vector<int> vet_aux;
    bool flag;
    for ( size_t i { 0 }; i < v.size(); i++){
        flag = false;
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if ( v[i] == v[j] ){
                flag = true;
                break;
            }
        }
        if ( flag == false ){
            vet_aux.push_back(v[i]);
        }
    }
    return vet_aux;
}

std::vector<int> diferentes( const std::vector<int>& v ){
    std::vector<int> vet_aux;
    bool flag;
    for ( size_t i { 0 }; i < v.size(); i++){
        flag = false;
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if ( abs( v[i] ) == abs ( v[j] ) ){
                flag = true;
                break;
            }
        }
        if ( flag == false ){
            vet_aux.push_back(abs( v[i] ) );
        }
    }
    return vet_aux;
}

std::vector<int> abandonados( const std::vector<int>& v ){
    std::vector<int> vet_aux;
    bool flag;
    for ( size_t i { 0 }; i < v.size(); i++){
        flag = false;
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if ( v[i] == v[j] ){
                flag = true;
                break;
            }
        }
        if ( flag == true ){
            vet_aux.push_back( v[i] );
        }
    }
    return vet_aux;
}

int main(){
    int op { 0 };
    std::vector<int> vet { -12, -11, -3, -2, -1, 1, 2, 4, 11, 12 };
    std::vector<int> vet_pra_ordenar { 3, 6, 7, 8, 2, 4, 9, 1, 5 };
    std::vector<int> vet_p_excl { -2, -2, -3 , -4, -2, -5, -5, 6, 6, 7 ,8};

    while(op != 13){
        std::cout << "Lista de funcoes:\n1- clone\n2- pegar_homens\n3- pegar_calmos\n4- pegar_mulheres_calmas\n5- inverter_com_copia\n6- inverter_in_place\n7- sortear\n8- embaralhar\n9- ordenar\n10- exclusivo\n11- diferentes\n12- abandonados\n";
        std::cout << "Digite a operacao desejada: ";
        std::cin >> op;
        if (op == 1){
            std::vector<int> vet_clone { clonar(vet) };
            for ( size_t i { 0 }; i < vet_clone.size(); i++){
                std::cout << vet_clone[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 2){
            std::vector<int> vet_homens { pegar_homens(vet) };
            for ( size_t i { 0 }; i < vet_homens.size(); i++){
                std::cout << vet_homens[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 3){
            std::vector<int> vet_calmos { pegar_calmos(vet) };
            for ( size_t i { 0 }; i < vet_calmos.size(); i++){
                std::cout << vet_calmos[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 4){
            std::vector<int> vet_mulheres_calmas { pegar_mulheres_calmas(vet) };
            for ( size_t i { 0 }; i < vet_mulheres_calmas.size(); i++){
                std::cout << vet_mulheres_calmas[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 5){
            std::vector<int> vet_invertido { inverter_com_copia(vet) };
            for ( size_t i { 0 }; i < vet_invertido.size(); i++){
                std::cout << vet_invertido[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 6){
            inverter_in_place(vet);

            std::cout << '\n';
        }
        if (op == 7){
            std::cout << "numero sorteado: " << sortear(vet);
            
            std::cout << '\n';
        }
        if (op == 8){
            embaralhar( vet );
            
            std::cout << '\n';
        }
        if (op == 9){
            ordenar( vet_pra_ordenar );
            
            std::cout << '\n';
        }
        if (op == 10){
            std::vector<int> vet_exclusivos { exclusivos( vet_p_excl ) };
            for ( size_t i { 0 }; i < vet_exclusivos.size(); i++){
                std::cout << vet_exclusivos[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 11){
            std::vector<int> vet_diferentes { diferentes( vet_p_excl ) };
            for ( size_t i { 0 }; i < vet_diferentes.size(); i++){
                std::cout << vet_diferentes[i] << ' ';
            }
            std::cout << '\n';
        }
        if (op == 12){
            std::vector<int> vet_abandonados { abandonados( vet_p_excl ) };
            for ( size_t i { 0 }; i < vet_abandonados.size(); i++){
                std::cout << vet_abandonados[i] << ' ';
            }
            std::cout << '\n';
        }
    }
    return 0;
}
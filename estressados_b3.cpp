#include <iostream>
#include <vector>

std::vector<int> sozinhos(const std::vector<int>& v){
    std::vector<int> vet_aux;
    int cont {0};
    for ( size_t i { 0 }; i < v.size(); i++){
        cont = 0;
        for (size_t j {0};j < v.size(); j++){
            if ( abs(v[i]) == abs(v[j]) ){
                cont++;
            }
        }
        if ( cont == 1 ){
            vet_aux.push_back( v[i] );
        }
    }
    return vet_aux;
}

std::vector<int> mais_ocorrencias(const std::vector<int>& v){
    std::vector<int> vet_aux;
    int cont {0};
    int maior {0};
    for ( size_t i { 0 }; i < v.size(); i++){
        cont = 0;
        for (size_t j {0};j < v.size(); j++){
            if ( abs(v[i]) == abs(v[j]) ){
                cont++;
            }
        }
        if ( cont > maior ){
            maior = i;
        }
    }
    vet_aux.push_back(abs(v[maior]));
    return vet_aux;
}

std::vector<int> recorrentes(std::vector<int>& v){
    std::vector<int> vet_aux;
    int cont {0};
    int cont_2 {0};
    int maior {0};

    for ( size_t i { 0 }; i < v.size(); i++){
        cont = 0;
        for (size_t j {i + 1};j < v.size(); j++){
            if ( abs(v[i]) == abs(v[j]) ){
                cont++;
            }
        }
        if ( cont > maior ){
            maior = cont;
        }
    }

    for ( size_t i { 0 }; i < v.size(); i++){
        cont_2 = 0;
        for (size_t j {i + 1};j < v.size(); j++){
            if ( abs(v[i]) == abs(v[j]) ){
                cont_2++;
            }
        }
        if ( cont_2 == maior ){
            vet_aux.push_back(abs(v[i]));
        }
    }

    return vet_aux;
}

int briga(const std::vector<int>& v){
    int cont {0};
    
    for ( size_t i { 1 }; i < v.size() - 1; i++) {
        if(abs(v[i]) > 50 && abs(v[(i - 1)]) > 30 && abs(v[(i + 1)]) > 30) {
            cont++;
        } 
    }
    return cont;
}

std::vector<int> apaziguado(const std::vector<int>& v){
    std::vector<int> vet_aux;
    
   for ( size_t i { 1 }; i < v.size() - 1; i++) {
        if(abs(v[i]) < 10 && abs(v[(i - 1)]) > 80) {
            vet_aux.push_back(i - 1);
        }
        if(abs(v[i]) < 10 && abs(v[(i + 1)]) > 80) {
            vet_aux.push_back(i + 1);
        }
    }

    return vet_aux;
}

int quantos_times(const std::vector<int>& v){
    int cont {0};
    for ( size_t i { 0 }; i < v.size(); i++){
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if (v[i] > 0){
                if(v[j] < 0){
                    i = j;
                    cont++;
                    break;
                }
            } else if (v[i] < 0){
                if(v[j] > 0) {
                    i = j;
                    cont++;
                    break;
                }
            }
        }
    }
    return cont;
}

std::vector<int> maior_time(const std::vector<int>& v){
    int cont {0};
    int fim_maior {0};
    int comeco_maior {0};
    int maior {0};
    int i2 {0};
    int j2 {0};

    std::vector<int> vet_aux;

    for ( size_t i { 0 }; i < v.size(); i++){
        cont = 0;
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if (v[i] > 0){
                cont++;
                if(v[j] < 0){
                    i2 = i;
                    j2 = j;
                    i = j;
                    break;
                }
            } else if (v[i] < 0){
                cont++;
                if(v[j] > 0) {
                    i2 = i;
                    j2 = j;
                    i = j;
                    break;
                }
            }
        }
        if(maior < cont){
            maior = cont;
            comeco_maior = i2;
            fim_maior = j2;
        }
    }
    for ( int i = comeco_maior; i < fim_maior; i++){
        vet_aux.push_back(v[i]);
    }
    return vet_aux;
}

std::vector<int> sem_time(const std::vector<int>& v){
    std::vector<int> vet_aux;
    for ( size_t i { 0 }; i < v.size(); i++){
        for ( size_t j { i + 1 }; j < v.size(); j++){
            if (v[i] > 0){
                if(v[j] < 0){
                    i = j;
                    vet_aux.push_back(v[j]);
                    break;
                }
            } else if (v[i] < 0){
                if(v[j] > 0) {
                    i = j;
                    vet_aux.push_back(v[j]);
                    break;
                }
            }
        }
    }
    return vet_aux;
}

std::vector<int> casais(std::vector<int>& v){
    std::vector<int> vet_aux;

    for ( size_t i { 0 }; i < v.size(); i++) {
        for ( size_t j {0};j < v.size(); j++) {
            if ( v[i] == -(v[j]) && v[i] != 0){
                vet_aux.push_back(v[i]);
                vet_aux.push_back(v[j]);
                v[i] = 0;
                v[j] = 0;
                break;
            }
        }
    }  
    return vet_aux;  
}

std::vector<int> remove(std::vector<int>& v){
    int num_a_rem {0};
    int k {0};
    std::cout << "insira o num que quer remover: ";
    std::cin >> num_a_rem;

    for ( size_t i = 0; i < v.size(); i++){
        if ( v[i] == num_a_rem ){
            k = i;
            break;
        }
    }

    for ( size_t j = k + 1; j < v.size(); j++){
        v[j-1] = v[j];
    }

    v.pop_back();
    return v;
}

std::vector<int> inserir(std::vector<int>& v){
    int num_a_ins {0};
    int pos_a_ins {0};
    std::cout << "insira o num que quer inserir e sua posicao: ";
    std::cin >> num_a_ins;
    std::cin >> pos_a_ins;

    for ( size_t j = v.size(); j > pos_a_ins; j--){
        v[j] = v[j-1];
    }
    v[pos_a_ins] = num_a_ins;

    v.pop_back();
    return v;
}

int main(){
    int op {0};
    std::vector<int> vet {1, 1, 3, 4, 3, -1, -3, -3};
    std::vector<int> vet_recor {1, 3, 4, 5, -1, -5, -5, 3, -3};
    std::vector<int> vet_briguentos {51, -31, 54, 37, -58, -32, -35, 60};
    std::vector<int> vet_apaz {82, -7, 54, -90, 6, 9, 89, -11};
    std::vector<int> vet_times {1, 2, 3, 4, 5, 6, -1, 7, 8 , 9, 10, 11, 12 ,13, -2};
    std::vector<int> vet_2 {1, 2, 3, 4, 5, 6, 7, 8, 9};

    while(op != 12){
        std::cout << "Lista de funcoes:\n1- sozinhos\n2- mais_ocorrencias\n3- recorrentes\n4- briga\n5- apaziguados\n6-quantos_times\n7- maior_time\n8- sem_time\n9- casais\n10- remove\n11- inserir\n12- encerrar programa\n";
        std::cout << "Digite a operacao desejada: ";
        std::cin >> op;

        if(op == 1){
            std::vector<int> vet_sozinhos { sozinhos( vet ) };
            for ( size_t i { 0 }; i < vet_sozinhos.size(); i++){
                std::cout << vet_sozinhos[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 2){
            std::vector<int> vet_ocorrencias { mais_ocorrencias( vet ) };
            for ( size_t i { 0 }; i < vet_ocorrencias.size(); i++){
                std::cout << vet_ocorrencias[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 3){
            std::vector<int> vet_recorrentes { recorrentes( vet_recor ) };
            for ( size_t i { 0 }; i < vet_recorrentes.size(); i++){
                std::cout << vet_recorrentes[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 4){
            std::cout << "numero de brigas: " << briga( vet_briguentos );
            
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 5){
            std::vector<int> vet_ap { apaziguado( vet_apaz ) };
            for ( size_t i { 0 }; i < vet_ap.size(); i++){
                std::cout << vet_ap[i] << ' ';
            }

            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 6){
            std::cout << "numero de times: " << quantos_times( vet_times );
            
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 7){
            std::vector<int> vet_maior_t { maior_time( vet_times ) };
            for ( size_t i { 0 }; i < vet_maior_t.size(); i++){
                std::cout << vet_maior_t[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 8){
            std::vector<int> vet_sozinhos { sem_time( vet_times ) };
            for ( size_t i { 0 }; i < vet_sozinhos.size(); i++){
                std::cout << vet_sozinhos[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 9){
            std::vector<int> vet_casais { casais( vet ) };
            for ( size_t i { 0 }; i < vet_casais.size(); i++){
                std::cout << vet_casais[i] << ' ';
            }
            std::cout << '\n';
            std::cout << '\n';
        }
        if(op == 10){
            std::cout << '[';

            for ( size_t i { 0 }; i < vet_2.size(); i++){
                std::cout << vet_2[i] << ' ';
            }

            std::cout << ']' << std::endl;

            std::vector<int> vet_remove { remove( vet_2 ) };

            std::cout << '[';

            for ( size_t i { 0 }; i < vet_remove.size(); i++){
                std::cout << vet_remove[i] << ' ';
            }

            std::cout << ']' << std::endl;
            std::cout << '\n';
        }
        if(op == 11){
            std::cout << '[';

            for ( size_t i { 0 }; i < vet_2.size(); i++){
                std::cout << vet_2[i] << ' ';
            }

            std::cout << ']' << std::endl;

            std::vector<int> vet_insere { inserir( vet_2 ) };

            std::cout << '[';

            for ( size_t i { 0 }; i < vet_insere.size(); i++){
                std::cout << vet_insere[i] << ' ';
            }

            std::cout << ']' << std::endl;
            std::cout << '\n';
        }
    }
    return 0;
}
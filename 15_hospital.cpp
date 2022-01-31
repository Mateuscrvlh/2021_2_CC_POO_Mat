#include <iostream>
#include <map>
#include <vector>
#include <sstream>

class Paciente;
class Medico {
    std::string id;
    std::string classe;
    std::map<std::string, Paciente*> pacientes;
public:
    Medico(std::string id, std::string classe) : id(id), classe(classe) {}
    std::string getId() {
        return this->id;
    }

    void addPaciente(Paciente* paciente);
    
    void removerPaciente(std::string idPaciente);

    std::vector<Paciente> getPacientes() {
        std::vector<Paciente> gPacientes;
        for (auto it : pacientes) {
            gPacientes.push_back(*it.second);
        }
        return gPacientes;
    }

    std::string getClasse() {
        return this->classe;
    }

    friend std::ostream& operator<<(std::ostream& os, Medico& m) {
        os << "Med: " << m.id << ":" << m.classe << " Pacs: [";
        int cont = 0;
        for (auto it : m.pacientes) {
            cont++;
            os << it.first;
            if(cont != (int) m.pacientes.size()) {
                os << ",";
            }
        }
        os << "]";
        return os;
    }
};

class Paciente {
    std::string Id;
    std::string diagnostico;
    std::map<std::string, Medico*> medicos;
public:
    Paciente(std::string Id, std::string diagnostico) : Id(Id), diagnostico(diagnostico) {}
    std::string getId() {
        return this->Id;
    }

    void addMedico(Medico* medico);
    
    void removerMedico(std::string idMedico);
    
    std::vector<Medico> getMedicos() {
        std::vector<Medico> gMedicos;
        for (auto it : medicos) {
            gMedicos.push_back(*it.second);
        }
        return gMedicos;
    }

    std::string getDiagnostico() {
        return diagnostico;
    }

    friend std::ostream& operator<<(std::ostream& os, Paciente& p) {
        os << "Pac: " << p.Id << ":" << p.diagnostico << " Meds: [";
        int cont = 0;
        for (auto it : p.medicos) {
            cont++;
            os << it.first;
            if(cont != (int) p.medicos.size()) {
                os << ",";
            }
        }
        os << "]";
        return os;
    }
};

void Medico::addPaciente(Paciente* paciente) {
    auto key = pacientes.find(paciente->getId());
    if (key == pacientes.end()) {
        this->pacientes[paciente->getId()] = paciente;
    }
}

void Medico::removerPaciente(std::string idPaciente) {
    auto key = pacientes.find(idPaciente);  
    if (key != pacientes.end()) {
        pacientes.erase(key);
    }
}

void Paciente::addMedico(Medico* medico) {
    auto key = medicos.find(medico->getId());
        if (key == medicos.end()) {
        this->medicos[medico->getId()] = medico;
    }
}

void Paciente::removerMedico(std::string idMedico) {
    auto key = medicos.find(idMedico);  
        if (key != medicos.end()) {
        medicos.erase(key);
    }
}

class Hospital {
    std::map<std::string, Paciente*> pacientes;
    std::map<std::string, Medico*> medicos;
public: 
    Hospital() {}

    void addPaciente(Paciente* paciente) {
        auto key = pacientes.find(paciente->getId());
        if (key == pacientes.end()) {
            this->pacientes[paciente->getId()] = paciente;
        }
    }

    void addMedico(Medico* medico) {
        auto key = medicos.find(medico->getId());
        if (key == medicos.end()) {
            this->medicos[medico->getId()] = medico;
        }
    }

    void removerPaciente(std::string idPaciente) {
        auto key = pacientes.find(idPaciente);  
        if (key != pacientes.end()) {
            pacientes.erase(key);
        }
    }

    void removerMedico(std::string idMedico) {
        auto key = medicos.find(idMedico);  
        if (key != medicos.end()) {
            medicos.erase(key);
        }
    }

    void vincular(std::string nomeMedico, std::string nomePaciente) {
        this->medicos[nomeMedico]->addPaciente(this->pacientes[nomePaciente]);
        this->pacientes[nomePaciente]->addMedico(this->medicos[nomeMedico]);
    }

    friend std::ostream& operator<<(std::ostream& os, Hospital& h) {
        os << "Medicos:\n";
        for (auto it : h.medicos) {
            os << *it.second << std::endl;
        }
        os << "\nPacientes:\n";
        for (auto it : h.pacientes) {
            os << *it.second << std::endl;
        }
        return os;
    }
};

int main() {
    Hospital hospital;

    while(true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "addPac") {
            std::string id;
            std::string diagnostico;
            ss >> id >> diagnostico;
            hospital.addPaciente(new Paciente(id, diagnostico));
        } else if (cmd == "remPac") {
            std::string id;
            ss >> id;
            hospital.removerPaciente(id);
        } else if (cmd == "addMed") {
            std::string id;
            std::string classe;
            ss >> id >> classe;
            hospital.addMedico(new Medico(id, classe));
        } else if (cmd == "remMed") {
            std::string id;
            ss >> id;
            hospital.removerMedico(id);
        } else if (cmd == "vincular") {
            std::string nomeMedico;
            std::string nomePaciente;
            ss >> nomeMedico >> nomePaciente;
            hospital.vincular(nomeMedico, nomePaciente);
        } else if (cmd == "show") {
            std::cout << hospital;
        } else {
            std::cout << "fail: comando invalido" << std::endl;
        }

    }
}
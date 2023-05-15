#include "Repository_Contract.h"

#include <utility>

Repository_Contract::Repository_Contract() {
    contract = new std::vector<Disciplina>;
}

std::vector<Disciplina> *Repository_Contract::get_contract() {
    return contract;
}

void Repository_Contract::delete_contract() {
    contract->clear();

}

Repository_Contract::~Repository_Contract() {
    delete contract;
}

void Repository_Contract::add_contract(const Disciplina& disciplina) {
    for(const Disciplina& d: *contract){
        if (d.getDenumire() == disciplina.getDenumire() &&
            d.getCadruDidactic() == disciplina.getCadruDidactic() &&
            d.getTip() == disciplina.getTip()) {
            throw ContractException("Disciplina existenta!\n");
        }
    }
    contract->push_back(disciplina);
}

void Repository_Contract::save_contract(const string &nume) {
    std::ofstream f(nume);

    for(const Disciplina& disciplina: *contract){
        f << disciplina.getDenumire() << " " << disciplina.getTip() \
        << " " << disciplina.getCadruDidactic() << " " << disciplina.getNrOre() << "\n";
    }

    f.close();
}

void Repository_Contract::remove(const Disciplina& disciplina) {
    int poz = 0;
    for(const Disciplina& d: *contract){
        if (d.getDenumire() == disciplina.getDenumire() &&
            d.getCadruDidactic() == disciplina.getCadruDidactic() &&
            d.getTip() == disciplina.getTip() && d.getNrOre() == disciplina.getNrOre()) {
            break;
        }
        poz = poz + 1;
    }
    if(poz == contract->size()){
        throw ContractException("Disciplina nu exista!\n");
    }
    contract->erase(contract->begin() + poz);
}

ContractException::ContractException(string m): msg{std::move(m)} {}

void tests_contract(){
    Repository_Contract repo;
    assert(repo.get_contract()->empty());
    repo.add_contract(Disciplina("A", "Laborator", "D", 2));
    repo.add_contract(Disciplina("A", "Curs", "C", 4));
    assert(repo.get_contract()->size() == 2);
    repo.remove(Disciplina("A", "Curs", "C", 4));
    assert(repo.get_contract()->size() == 1);
    repo.add_contract(Disciplina("A", "Curs", "C", 4));
    repo.delete_contract();
    assert(repo.get_contract()->empty());
    repo.save_contract("test1");
}
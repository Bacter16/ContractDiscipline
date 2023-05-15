#include "Service_Contract.h"

Service_Contract::Service_Contract(Repository_Contract *rep): repo{rep}{}

void Service_Contract::add_contract_service(const string& denumire, const string& tip, const string& cadru, int ore) {
    Disciplina d(denumire,tip,cadru,ore);
    repo->add_contract(d);
    undoActions.push_back(new UndoAddContract{*repo, d});
}

void Service_Contract::delete_contract_service() {
    std::vector<Disciplina> *dis;
    dis = new std::vector<Disciplina>;
    for(const Disciplina& d: *repo->get_contract())
        dis->push_back(d);
    repo->delete_contract();
    undoActions.push_back(new UndoDeleteContract{*repo, *dis});
}

std::vector<Disciplina> *Service_Contract::get_contract_service() {
    return repo->get_contract();
}

void Service_Contract::save_contract_service(const string& nume) {
    repo->save_contract(nume);
}

void Service_Contract::random_generator(int n, std::vector<Disciplina> *discipline) {
    int counter = 0;
    if( n <= discipline->size() - repo->get_contract()->size()) {
        while (counter != n) {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(0, int(discipline->size()) - 1);
            try {
                repo->add_contract((*discipline)[distr(gen)]);
                Disciplina d((*discipline)[distr(gen)].getDenumire(), (*discipline)[distr(gen)].getTip(),
                             (*discipline)[distr(gen)].getCadruDidactic(), (*discipline)[distr(gen)].getNrOre());
                undoActions.push_back(new UndoAddContract{*repo, d});
                counter++;
            } catch (ContractException &) {}
        }
    }
    else{
        throw ServiceContractException("Numar maxim de discipline!");
    }
}

void Service_Contract::undo_service() {
    if (undoActions.empty()) {
        throw ServiceContractException("Nu mai exista operatii undo!\n");
    }
    UndoActionContract* act = undoActions.back();
    act->doUndo();
    undoActions.pop_back();
    delete act;
}

std::vector<int> Service_Contract::raports_service() {
    int c = 0,s = 0,l = 0;
    for(const Disciplina& d:*repo->get_contract()){
        if(d.getTip() == "Curs")
            c++;
        else if(d.getTip() == "Semiar")
            s++;
        else if(d.getTip() == "Laborator")
            l++;
    }
    std::vector<int> v = {c,s,l};
    return v;
}

UndoAddContract::UndoAddContract(Repository_Contract &r, const Disciplina &dis):repo{ r }, d{ dis } {}

void UndoAddContract::doUndo() {
    repo.remove(d);
}

UndoDeleteContract::UndoDeleteContract(Repository_Contract &r,const std::vector<Disciplina>& d):repo{r},discipline{d}{}

void UndoDeleteContract::doUndo() {
    for(const auto& d:discipline)
        repo.add_contract(d);
}

ServiceContractException::ServiceContractException(string m):msg{std::move(m)} {}

#include "Service_Discipline.h"
#include <utility>

Service::Service(Repository *rep): repo{rep}{}

void Service::add_service(string denumire, string tip, string cadru, int ore) {
    Disciplina d(std::move(denumire), std::move(tip), std::move(cadru), ore);
    Validare v(d);
    if(v.validare_disciplina() == 0){
        repo->add(d);
        undoActions.push_back(new UndoAdd{*repo, d});
    }
}

std::vector<Disciplina>* Service::getAllService() {
    return repo->getAll();
}

void Service::remove_service(const string& denumire, const string& tip, const string& cadru, int ore) {
    Disciplina dis(denumire, tip, cadru, ore);
    repo->remove(dis);
    undoActions.push_back(new UndoDelete{*repo, dis});
}

void Service::modify_denumire_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_denumire) {
    int poz = 0;
    Disciplina d1,d2;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == denumire &&
            d.getCadruDidactic() == cadru &&
            d.getTip() == tip && d.getNrOre() == ore) {
            d2 = Disciplina(denumire, tip, cadru, ore);
            d1 = Disciplina(new_denumire, tip, cadru, ore);
            break;
        }
        poz = poz + 1;
    }
    if(poz == repo->getAll()->size()){
        throw ServiceException("Disciplina nu exista!\n");
    }
    else{
        repo->modify_denumire(poz, new_denumire);
        undoActions.push_back(new UndoModify{*repo, d1, d2});
    }
}

void Service::modify_tip_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_tip) {
    int poz = 0;
    Disciplina d1, d2;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == denumire &&
            d.getCadruDidactic() == cadru &&
            d.getTip() == tip && d.getNrOre() == ore) {
            d2 = Disciplina(denumire, tip, cadru, ore);
            d1 = Disciplina(denumire, new_tip, cadru, ore);
            break;
        }
        poz = poz + 1;
    }
    if(poz == repo->getAll()->size()){
        throw ServiceException("Disciplina nu exista!\n");
    }
    else{
        repo->modify_tip(poz, new_tip);
        undoActions.push_back(new UndoModify{*repo, d1, d2});
    }
}

void Service::modify_cadru_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_cadru) {
    int poz = 0;
    Disciplina d1,d2;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == denumire &&
            d.getCadruDidactic() == cadru &&
            d.getTip() == tip && d.getNrOre() == ore) {
            d2 = Disciplina(denumire, tip, cadru, ore);
            d1 = Disciplina(denumire, tip, new_cadru, ore);
            break;
        }
        poz = poz + 1;
    }
    if(poz == repo->getAll()->size()){
        throw ServiceException("Disciplina nu exista!\n");
    }
    else{
        repo->modify_cadru(poz, new_cadru);
        undoActions.push_back(new UndoModify{*repo, d1, d2});
    }
}

void Service::modify_ore_service(const string& denumire, const string& tip, const string& cadru, int ore, int new_ore) {
    int poz = 0;
    Disciplina d1,d2;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == denumire &&
            d.getCadruDidactic() == cadru &&
            d.getTip() == tip && d.getNrOre() == ore) {
            d2 = Disciplina(denumire, tip, cadru, ore);
            d1 = Disciplina(denumire, tip, cadru, new_ore);
            break;
        }
        poz = poz + 1;
    }
    if(poz == repo->getAll()->size()){
        throw ServiceException("Disciplina nu exista!\n");
    }
    else{
        repo->modify_ore(poz, new_ore);
        undoActions.push_back(new UndoModify{*repo, d1, d2});
    }
}

void Service::modifyDisciplina(int index, const string& new_denumire, const string& new_tip, const string& new_cadru, int new_ore) {

    std::vector<Disciplina> *discipline = repo->getAll();
    Disciplina d1 = discipline->at(index);
    Disciplina d2(new_denumire, new_tip, new_cadru, new_ore);
    if(index >= repo->getAll()->size() || index < 0){
        throw ServiceException("Disciplina nu exista!\n");
    }
    else{
        repo->modifyOverAll(index, new_denumire, new_tip, new_cadru,new_ore);
        undoActions.push_back(new UndoModify{*repo, d1, d2});
    }
}

Disciplina Service::cautare_service(const string& denumire, const string& tip, const string& cadru, int ore){
    int poz = 0;
    std::vector<Disciplina> *discipline= repo->getAll();
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == denumire &&
            d.getCadruDidactic() == cadru &&
            d.getTip() == tip && d.getNrOre() == ore) {
            return d;
        }
        poz = poz + 1;
    }
    throw ServiceException("Disciplina nu exista!\n");

}

std::vector<Disciplina> Service::filtrare_discipline_service_nr_ore(int nr_ore) {
    std::vector<Disciplina> vd;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(Disciplina &d: *discipline){
        if(d.getNrOre() == nr_ore){
            vd.push_back(d);
        }
    }
    return vd;
}

std::vector<Disciplina> Service::filtrare_discipline_service_cadru_didactic(const string& cadru) {
    std::vector<Disciplina> vd;
    std::vector<Disciplina> *discipline = repo->getAll();
    for(Disciplina &d: *discipline){
        if(d.getCadruDidactic() == cadru){
            vd.push_back(d);
        }
    }
    return vd;
}

bool cmpDenumire(const Disciplina& d1, const Disciplina& d2) {
    return d1.getDenumire() < d2.getDenumire();
}

bool cmpNrOre(const Disciplina& d1, const Disciplina& d2) {
    return d1.getNrOre() < d2.getNrOre();
}

bool cmpCadruSiTip(const Disciplina& d1, const Disciplina& d2) {
    if(d1.getTip() == d2.getTip())
        return d1.getCadruDidactic() < d2.getCadruDidactic();
    return d1.getTip() < d2.getTip();
}

void Service::discipline_sortate_dupa_denumire() {
    generalSort(cmpDenumire);
}

void Service::discipline_sortate_dupa_nr_ore() {
    generalSort(cmpNrOre);
}

void Service::discipline_sortate_dupa_cadru_tip() {
    generalSort(cmpCadruSiTip);
}

void Service::generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
    std::vector<Disciplina> *discipline = repo->getAll();
    std::sort(discipline->begin(), discipline->end(), maiMicF);
}

ServiceException::ServiceException(string m):msg{std::move(m)} {}

void Service::random_generator(int n) {
    int counter = 0;
    std::vector<Disciplina> *dis;
    dis = new std::vector<Disciplina>;
    while(n != counter){
        Disciplina d(random_nume(), random_tip(), random_nume(), 2);
        try{
            Validare v(d);
            repo->add(d);
            dis->push_back(d);
            counter++;
        }catch (ValidareException&){}
    }
    undoActions.push_back(new UndoRandom(*repo, *dis));
}

string Service::random_nume() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(3, 8);
    return randomName(distr(gen));
}

string Service::random_tip() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 2);
    return tip_posibil[distr(gen)];
}

string Service::randomName(int length){

    char consonents[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
    char vowels[] = {'a','e','i','o','u','y'};

    string name;

    int random = rand() % 2;
    int count = 0;

    for(int i = 0; i < length; i++) {
        if(i == 0){
            if(random < 2 && count < 2) {
                name = name + consonents[rand() % 19];
                name[0] = toupper(name[0]);
                count++;
            }
            else {
                name = name + vowels[rand() % 5];
                name[0] = toupper(name[0]);
                count = 0;
            }

            random = rand() % 2;
        }
        else{
            if(random < 2 && count < 2) {
                name = name + consonents[rand() % 19];
                count++;
            }
            else {
                name = name + vowels[rand() % 5];
                count = 0;
            }

            random = rand() % 2;
        }
    }
    return name;
}

void Service::undo_service() {
    if (undoActions.empty()) {
        throw ServiceException("Nu mai exista operatii undo!\n");
    }
    UndoAction* act = undoActions.back();
    act->doUndo();
    undoActions.pop_back();
    delete act;
}

UndoAdd::UndoAdd(Repository &r, const Disciplina &dis):repo{ r }, d{ dis } {}

void UndoAdd::doUndo() {
    repo.remove(d);
}

UndoDelete::UndoDelete(Repository &r, const Disciplina &dis):repo{ r }, d{ dis } {}

void UndoDelete::doUndo() {
    repo.add(d);
}

UndoModify::UndoModify(Repository &r, const Disciplina &d1,  const Disciplina &d2):repo{r},d1{d1},d2{d2}{}

void UndoModify::doUndo() {
    repo.remove(d1);
    repo.add(d2);
}

UndoRandom::UndoRandom(Repository &r, const vector<Disciplina> &d): repo{r},discipline{d}{}

void UndoRandom::doUndo() {
    for(Disciplina d:discipline){
        repo.remove(d);
    }
}


void testsService(){
    Repository rep;
    Service serv{&rep};
    try{
        serv.undo_service();
    }catch (ServiceException& exception){
        assert(strcmp(exception.what(),"Nu mai exista operatii undo!\n") == 0);
    }
    serv.add_service("A", "Laborator", "A", 2);

    std::vector<Disciplina> *discipline = serv.getAllService();
    assert(discipline->size() == 1);
    serv.modify_denumire_service("A", "Laborator", "A", 2, "OOP");
    serv.modify_tip_service("OOP", "Laborator", "A", 2, "Seminar");
    serv.modify_cadru_service("OOP", "Seminar", "A", 2, "Gabi");
    serv.modify_ore_service("OOP", "Seminar", "Gabi", 2, 4);
    discipline = serv.getAllService();
    auto ivd = discipline->begin();
    Disciplina d = *ivd;
    assert(d.getDenumire() == "OOP");
    assert(d.getTip() == "Seminar");
    assert(d.getCadruDidactic() == "Gabi");
    assert(d.getNrOre() == 4);
    try {
        serv.modify_denumire_service("A", "Laborator", "A", 2, "OOP");
    }catch (ServiceException& exception){
        assert(true);
    }
    try {
        serv.modify_tip_service("OOP", "Laborator", "A", 2, "Seminar");
    }catch (ServiceException& exception){
        assert(true);
    }
    try {
        serv.modify_cadru_service("OOP", "Seminar", "A", 2, "Gabi");
    }catch (ServiceException& exception){
        assert(true);
    }
    try {
        serv.modify_ore_service("OOP", "Seminar", "Gabi", 2, 4);
    }catch (ServiceException& exception){
        assert(true);
    }
    try {
        serv.remove_service("A", "Seminar", "Gabi", 4);
    }catch (RepoException& exception){
        assert(strcmp(exception.what(), "Disciplina nu exista!\n") == 0);
        assert(true);
    }

    serv.remove_service("OOP", "Seminar", "Gabi", 4);
    discipline = serv.getAllService();
    assert(discipline->empty());
    serv.add_service("A", "Laborator", "C", 2);
    serv.add_service("B", "Seminar", "C", 4);
    serv.add_service("C", "Laborator", "C", 2);
    serv.add_service("D", "Seminar", "A", 4);
    serv.add_service("E", "Laborator", "A", 2);
    std::vector discipline1 = serv.filtrare_discipline_service_cadru_didactic("C");
    assert(discipline1.size() == 3);
    discipline1 = serv.filtrare_discipline_service_nr_ore(2);
    assert(discipline1.size() == 3);
    serv.discipline_sortate_dupa_cadru_tip();
    ivd = discipline->begin();
    d = *ivd;
    assert(d.getTip() == "Laborator");
    serv.discipline_sortate_dupa_nr_ore();
    ivd = discipline->begin();
    d = *ivd;
    assert(d.getNrOre() == 2);
    serv.discipline_sortate_dupa_denumire();
    ivd = discipline->begin();
    d = *ivd;
    assert(d.getDenumire() == "A");
    serv.cautare_service("A", "Laborator", "C", 2);
    try{
        serv.cautare_service("A", "Seminar", "C", 2);
    }catch (ServiceException& exception){
        assert(true);
    }
    serv.remove_service("A", "Laborator", "C", 2);
    serv.remove_service("B", "Seminar", "C", 4);
    serv.remove_service("C", "Laborator", "C", 2);
    serv.remove_service("D", "Seminar", "A", 4);
    serv.remove_service("E", "Laborator", "A", 2);
    assert(serv.getAllService()->empty());
    serv.random_generator(10);
    assert(serv.getAllService()->size() == 10);
    serv.undo_service();
    assert(serv.getAllService()->empty());
    serv.add_service("A", "Laborator", "C", 2);
    assert(serv.getAllService()->size() == 1);
    serv.modify_denumire_service("A", "Laborator", "C", 2, "C");
    assert((*serv.getAllService())[0].getDenumire() == "C");
    serv.remove_service("C", "Laborator", "C", 2);
    assert(serv.getAllService()->empty());
    serv.undo_service();
    assert(serv.getAllService()->size() == 1);
    serv.undo_service();
    assert((*serv.getAllService())[0].getDenumire() == "A");
    serv.undo_service();
    assert(serv.getAllService()->empty());
}

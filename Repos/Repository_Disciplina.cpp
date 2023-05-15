#include "Repository_Disciplina.h"

Repository::Repository() {
    discipline = new std::vector<Disciplina>;
    read();
}

void Repository::add(Disciplina &disciplina) {
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == disciplina.getDenumire() &&
            d.getCadruDidactic() == disciplina.getCadruDidactic() &&
            d.getTip() == disciplina.getTip()) {
            throw RepoException("Disciplina existenta!\n");
        }
    }
    discipline->push_back(disciplina);
    overwrite();
}

std::vector<Disciplina>* Repository::getAll() {
    return discipline;
}

void Repository::remove(Disciplina& disciplina) {
    int poz = 0;
    for(const Disciplina& d: *discipline){
        if (d.getDenumire() == disciplina.getDenumire() &&
            d.getCadruDidactic() == disciplina.getCadruDidactic() &&
            d.getTip() == disciplina.getTip() && d.getNrOre() == disciplina.getNrOre()) {
            break;
        }
        poz = poz + 1;
    }
    if(poz == discipline->size()){
        throw RepoException("Disciplina nu exista!\n");
    }
    discipline->erase(discipline->begin() + poz);
    overwrite();
}

void Repository::modify_denumire(int poz, const string& new_denumire) {
    if(poz >= discipline->size() || poz < 0)
        throw RepoException("Index invalid!\n");
    int k = 0;
    for(Disciplina& d: *discipline){
        if(poz == k) {
            d.set_denumire(new_denumire);
            d.set_cadru(d.getCadruDidactic());
            d.set_tip(d.getTip());
            d.set_ora(d.getNrOre());
            break;
        }
        k++;
    }
    overwrite();
}

void Repository::modify_tip(int poz, const string& new_tip) {
    if(poz > discipline->size() || poz < 0)
        throw RepoException("Index invalid!\n");
    int k = 0;
    for(Disciplina& d: *discipline){
        if(poz == k) {
            d.set_denumire(d.getDenumire());
            d.set_cadru(d.getCadruDidactic());
            d.set_tip(new_tip);
            d.set_ora(d.getNrOre());
            break;
        }
        k++;
    }
    overwrite();
}

void Repository::modify_cadru(int poz, const string& new_cadru) {
    if(poz > discipline->size() || poz < 0)
        throw RepoException("Index invalid!\n");
    int k = 0;
    for(Disciplina& d: *discipline){
        if(poz == k) {
            d.set_denumire(d.getDenumire());
            d.set_cadru(new_cadru);
            d.set_tip(d.getTip());
            d.set_ora(d.getNrOre());
            break;
        }
        k++;
    }
    overwrite();
}

void Repository::modify_ore(int poz, int new_ore) {
    if(poz > discipline->size() || poz < 0)
        throw RepoException("Index invalid!\n");
    int k = 0;
    for(Disciplina& d: *discipline){
        if(poz == k) {
            d.set_denumire(d.getDenumire());
            d.set_cadru(d.getCadruDidactic());
            d.set_tip(d.getTip());
            d.set_ora(new_ore);
            break;
        }
        k++;
    }
    overwrite();
}

void Repository::modifyOverAll(int poz,  const string& new_denumire, const string& new_tip, const string& new_cadru, int new_ore) {
    if(poz >= discipline->size() || poz < 0)
        throw RepoException("Index invalid!\n");
    int k = 0;
    for(Disciplina& d: *discipline){
        if(poz == k) {
            d.set_denumire(new_denumire);
            d.set_cadru(new_cadru);
            d.set_tip(new_tip);
            d.set_ora(new_ore);
            break;
        }
        k++;
    }
    overwrite();
}

Repository::~Repository() {
    delete discipline;
}

void Repository::read() {
    std::ifstream f("discipline");
    string d,c,t;
    int o;
    while(f >> d && f >> t && f >> c && f >> o){
        Disciplina disciplina(d,t,c,o);
        add(disciplina);
    }
    f.close();
}


void Repository::overwrite() {
    std::ofstream f("discipline");

    for(const Disciplina& disciplina: *discipline){
        f << disciplina.getDenumire() << " " << disciplina.getTip() \
        << " " << disciplina.getCadruDidactic() << " " << disciplina.getNrOre() << "\n";
    }

    f.close();
}


RepoException::RepoException(string m):msg{std::move(m)}{}


void testRepo() {
    Repository repo;
    Disciplina d1{"A", "Laborator", "D", 2};
    Disciplina d2{"A", "Seminar", "C", 4};
    repo.add(d1);
    repo.add(d2);
    std::vector<Disciplina> *discipline = repo.getAll();
    assert(discipline->size() == 2);
    Disciplina x = (*discipline)[0];
    assert(x.getNrOre() == 2);

    try{
        repo.modify_denumire(2, "OOP");
    }catch (RepoException& exceptie){
        assert(true);
    }

    repo.modify_denumire(1, "OOP");
    repo.modify_tip(1, "Seminar");
    repo.modify_cadru(1, "Gabi Mircea");
    repo.modify_ore(1, 2);

    x = (*discipline)[1];

    assert(x.getDenumire() == "OOP");
    assert(x.getTip() == "Seminar");
    assert(x.getCadruDidactic() == "Gabi Mircea");
    assert(x.getNrOre() == 2);

    repo.remove((*discipline)[0]);
    assert(!discipline->empty());
    repo.remove((*discipline)[1]);
    discipline = repo.getAll();
    assert(discipline->empty());
}

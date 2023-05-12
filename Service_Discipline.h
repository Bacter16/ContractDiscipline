#pragma once
#include "Repository_Disciplina.h"
#include "Validare.h"
#include <cstring>
#include <vector>
#include <cassert>
#include <random>
#include <utility>

using std::vector;
using std::string;

class UndoAction {
public:
    virtual void doUndo() = 0;
    virtual ~UndoAction()= default;
};

class UndoAdd: public UndoAction{
    Disciplina d;
    Repository &repo;
public:

    UndoAdd(Repository &r,const Disciplina &dis);

    void doUndo() override;

};

class UndoDelete: public UndoAction{
    Disciplina d;
    Repository &repo;
public:

    UndoDelete(Repository &r,const Disciplina &dis);

    void doUndo() override;

};

class UndoModify: public UndoAction{
    Disciplina d1,d2;
    Repository &repo;
public:

    UndoModify(Repository &r,const Disciplina &d1,const Disciplina &d2);

    void doUndo() override;

};

class UndoRandom: public UndoAction{
    std::vector<Disciplina> discipline;
    Repository &repo;
public:

    UndoRandom(Repository &r,const std::vector<Disciplina>& d);

    void doUndo() override;

};

class Service {
private:

    Repository *repo;
    std::vector<UndoAction*> undoActions;

    void generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&));

    string tip_posibil[3] = {"Curs", "Seminar", "Laborator"};

    string random_tip();

    static string random_nume();

    static string randomName(int length);

public:
    explicit Service(Repository *rep);

    void add_service(string denumire, string tip, string cadru, int ore);

    std::vector<Disciplina>* getAllService();

    void remove_service(const string& denumire, const string& tip, const string& cadru, int ore);

    void modify_denumire_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_denumire);

    void modify_tip_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_tip);

    void modify_cadru_service(const string& denumire, const string& tip, const string& cadru, int ore, const string& new_cadru);

    void modify_ore_service(const string& denumire, const string& tip, const string& cadru, int ore, int new_ore);

    Disciplina cautare_service(const string& denumire, const string& tip, const string& cadru, int ore);

    std::vector<Disciplina> filtrare_discipline_service_nr_ore(int nre_ore);

    std::vector<Disciplina> filtrare_discipline_service_cadru_didactic(const string& cadru);

    void discipline_sortate_dupa_denumire();

    void discipline_sortate_dupa_cadru_tip();

    void discipline_sortate_dupa_nr_ore();

    void random_generator(int n);

    void undo_service();

    void modifyDisciplina(int index, const string &new_denumire,const string &new_tip, const string &new_cadru, int new_ore);

    int rapoarteCursuri();

    int rapoarteSeminare();

    int rapoarteLaboratoare();

};

class ServiceException : public std::exception{
private:
    string msg;
public:
    explicit ServiceException(string m);

    [[nodiscard]] const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

//void testsService();
